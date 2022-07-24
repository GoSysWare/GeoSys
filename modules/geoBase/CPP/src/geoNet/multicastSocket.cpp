
#include "nicPreComp.h"
#include "preCompile.h"
#include "multicastSocket.h"



CMulticastSocket::CMulticastSocket()
:m_group_port(0),
m_group_loopback(0),
m_group_ttl(0),
m_joined_addr_num(0)
{
	memset(m_group_ip,0,sizeof(m_group_ip));
	memset(m_joined_addr,0,sizeof(ACE_INET_Addr)*MAX_INTERFACE_NUM);
	memset(m_strIPAddr,0,sizeof(m_strIPAddr));
}
CMulticastSocket::~CMulticastSocket()
{
	Close();

}

nicInt32 CMulticastSocket::Close()
{
	LeaveGroup();
	return close();

}
//这个接口是给UDP单播用,作为服务端需要绑定一个端口用来接收数据，
//而UDP的发送地址和端口直接在sendto函数中
nicInt32 CMulticastSocket::Create(nicInt32 port)
{
	ACE_INET_Addr udp_addr(port);
	return ACE_SOCK_Dgram::open(udp_addr);
}

//加入多播组时需指定了多播地址和端口号，端口号不让jion内部自动分配处理
nicInt32 CMulticastSocket::JoinGroup(nicStr strMultiGroupIP,nicInt32 nPort, nicInt32 nTTL,bool bLooBack)
{
	nicInt32 nRet = nicRET_Fail;
	strncpy(this->m_group_ip, strMultiGroupIP, sizeof(m_group_ip));
	m_group_ip[sizeof(m_group_ip) - 1] = 0;
	this->m_group_port=nPort;
	this->m_group_ttl=nTTL;
	this->m_group_loopback=bLooBack;
	ACE_INET_Addr macst_addr(m_group_port,m_group_ip);
	ACE_INET_Addr *if_addrs = 0;
	size_t if_cnt;
	//设置不加入多播组的网卡
	nicChar	disabled[256];
	memset(disabled,0,sizeof(disabled));
	char configFile[256];
	strcpy(configFile,get_config_file());
	int pos = strlen(configFile);
	while( (--pos) >=0 && !(configFile[pos] == '/' || configFile[pos]=='\\') );
	if(pos>0)
	{
		configFile[pos+1]=0;
		strcat(configFile,"NicNet.ini");
		GetPrivateProfileString(
			"vbus",
			"disabled",
			"",
			disabled,
			sizeof(disabled),
			configFile
			);	
	}

	if (ACE::get_ip_interfaces (if_cnt, if_addrs) != 0)
		return -1;
	if (if_cnt < 2)
	{
		//无网卡，或者网卡无IP地址时，只有127.0.0.1
		return nicRET_Fail;
	}
	else
	{
		while (if_cnt > 0)
		{
			--if_cnt;
			//去掉回环地址
			if (if_addrs[if_cnt].is_loopback ())
				continue;
			//得到本地IP
			char addr_buf[INET6_ADDRSTRLEN];
			if_addrs[if_cnt].get_host_addr (addr_buf, INET6_ADDRSTRLEN);
			//过滤不想加入多播组的IP
			if(strstr(disabled, addr_buf)) continue;
			/*******/
			//开始绑定到多播组中
			const char * strIp = if_addrs[if_cnt].get_host_addr();
			nRet = ACE_SOCK_Dgram_Mcast::join(macst_addr,1,strIp);
			if(nRet == 0 && m_joined_addr_num<MAX_INTERFACE_NUM)
			{//记录成功加入的IP地址,最多记录 MAX_INTERFACE_NUM 个
				m_joined_addr[m_joined_addr_num++].set_address(strIp,0);
				if(strlen(m_strIPAddr) + strlen(strIp) < SIZE_LENGTH_128-1)
				{
					strcat(m_strIPAddr,if_addrs[if_cnt].get_host_addr());
					strcat(m_strIPAddr,"/");
				}
			}
		}
	}
	//set TTL
	this->ACE_SOCK::set_option(IPPROTO_IP,IP_MULTICAST_TTL,(void *)&nTTL,sizeof(nTTL));


	delete [] if_addrs;
	return nRet>= 0 ? nicRET_OK:nicRET_Fail;
}
nicInt32 CMulticastSocket::LeaveGroup()
{
	ACE_INET_Addr macst_addr(m_group_port,m_group_ip);
	//同样要处理相应所有的多播组IP
	// 也可以指定IP离开多播组，此处把所有的IP地址都剥离多播组
	return ACE_SOCK_Dgram_Mcast::leave(macst_addr);
}
nicVoid CMulticastSocket::RejoinGroup()
{
	LeaveGroup();
	JoinGroup(
		m_group_ip, 
		m_group_port, 
		m_group_ttl,
		m_group_loopback? true : false
		);
}

nicInt32 CMulticastSocket::ReceiveFrom(nicVoid * buf, nicInt32 len, ACE_INET_Addr & addr)
{
	return ACE_SOCK_Dgram_Mcast::recv(buf,len,addr);
}
//UDP会在接收时得到远方的IP地址和端口号,addr需要预分配空间
//保留string型的IP地址，和 int型的port接口是因为此后打包，拆包要用这些信息，方便结构体处理，
//所以提供ACE_INET_Addr和结构化两类接口
nicInt32 CMulticastSocket::ReceiveFrom(nicVoid * buf,nicInt32 len,nicChar * addr,nicInt32 & port)
{
	ACE_INET_Addr _addr;
	int nRet = SOCKET_ERROR ;

	*addr = 0;
	port = 0;
	nRet = ReceiveFrom(buf, len, _addr);
	if(nRet){
		strcpy(addr,_addr.get_host_addr());
		port=_addr.get_port_number();
	}
	if (nRet == SOCKET_ERROR)
	{
		ACE_DEBUG((LM_DEBUG,ACE_TEXT(
			"%D,[%P|%t],%M,%N,%l ReceiveFrom failed\n")));
		return 0;
	}
	return nRet;

}
//UDP单播用
nicInt32 CMulticastSocket::SendTo(nicVoid *buf,nicInt32 len,nicChar * addr,nicInt32 port)
{
	ACE_INET_Addr _addr;
	_addr.set(port,addr);
	//如果地址为255.255.255.255
	if (_addr.is_any())
	{
		return -1;
	}
	return SendTo(buf,len,_addr);

}
//UDP多播用。多播的发送目标地址已经在join过程中封装起来，无需填写
nicInt32 CMulticastSocket::SendTo(nicVoid *buf, nicInt32 len)
{
	nicUInt8 uSendRecord=0;
	int if_no=0;
	int nSend=0,nMaxSend=0;
	for(if_no=0;if_no<m_joined_addr_num;if_no++)
	{
		this->ACE_SOCK::set_option(IPPROTO_IP,IP_MULTICAST_IF,(void *)&m_joined_addr[if_no],sizeof(ACE_INET_Addr));
		nSend = ACE_SOCK_Dgram_Mcast::send(buf,len,0);
		if(nSend<=0)
		{//用一个bit记录对应的网卡发送结果，根据返回值，就可断定发送失败的网卡
			uSendRecord = uSendRecord & (1<<if_no);
			const char* sIp = m_joined_addr[if_no].get_host_addr();
			ACE_INET_Addr macst_addr(m_group_port,m_group_ip);
			ACE_SOCK_Dgram_Mcast::leave(macst_addr,sIp);
			ACE_SOCK_Dgram_Mcast::join(macst_addr,1,sIp);
		}
		else
		{
			if(nMaxSend==0)
				nMaxSend=nSend;
		}
	}

	return nSend;//-uSendRecord;

}
//UDP单播用
nicInt32 CMulticastSocket::SendTo(nicVoid *buf, nicInt32 len, ACE_INET_Addr &addr)
{
	return ACE_SOCK_Dgram::send(buf,
		len,
		addr,
		0
		);

}
nicInt32 CMulticastSocket::OnReceive(int nErrorCode)
{
	if(nErrorCode) {
		return 0;
	}
	char src[128];
	int port;
	char data[VBUS_MAX_PACKET_SIZE+1];
	memset(data,0,sizeof(data));
	int res=ReceiveFrom(data,sizeof(data),src,port);
	if(res){
		OnData(data,res,port,src);
	}
	return res;
}
//这是给挂载总线上接收到数据直接处理过程，默认为什么都不处理
nicInt32 CMulticastSocket::OnData(void * buf,int len,int port,char * src_addr)
{
	return len;
}