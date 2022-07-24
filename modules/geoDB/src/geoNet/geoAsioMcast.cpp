
#ifndef LIB_NET_EXPORTS
#define LIB_NET_EXPORTS
#endif // !LIB_NET_EXPORTS

#include "preCompile.h"
#include "GeoAsioMcast.h"


GeoAsioMcast::GeoAsioMcast(asio::io_service&  io_service):
	mService(&io_service),
	mSocket(io_service)
{

}
GeoAsioMcast::~GeoAsioMcast()
{

}
int GeoAsioMcast::open(unsigned short port)
{
	mSocket.open(asio::ip::udp::v4());
	return 0;
}
int GeoAsioMcast::bind( unsigned short port, string ip)
{
	//如果ip为空，则是任意IP,被设置为ADDR_ANY
	if (ip.empty())
	{
		mSocket.bind(asio::ip::udp::endpoint(udp::v4(), port));
	}
	else
	{
		address_v4  addr = address_v4::from_string(ip);
		mSocket.bind(asio::ip::udp::endpoint(addr, port));
	}
	return 0;
}



int GeoAsioMcast::joinGroup(string  ip, unsigned short port, int nTTL, bool isLoopback)
{
	mGroupIP = ip;
	mGroupPort = port;
	mGroupTTL = nTTL;
	mIsGroupLoopback = isLoopback;
	mIsMulticast = true;

	//打开与绑定端口
	this->open(mGroupPort);

	//端口复用设置
	asio::socket_base::reuse_address reuse_option(true);
	mSocket.set_option(reuse_option);

	//打开与绑定端口
	this->bind(mGroupPort);

	//设置多播地址
	//选择本地IP加入多播组
	address_v4 multicast_address = address_v4::from_string(ip);
	if (!multicast_address.is_multicast())
		return  -1;
	address_v4 network_interface = address_v4::any();
	multicast::join_group join_option(multicast_address,network_interface);
	mSocket.set_option(join_option);

	//设置TTL
	asio::ip::multicast::hops ttl_option(mGroupTTL);
	mSocket.set_option(ttl_option);

	//设置回环
	//回环是多播的时候自己也可以收到
	asio::ip::multicast::enable_loopback loopbak_option(mIsGroupLoopback);
	mSocket.set_option(loopbak_option);

	return 0;
}

int GeoAsioMcast::leaveGroup()
{
	mIsMulticast = false;
	address_v4 multicast_address = address_v4::from_string(mGroupIP);
	address_v4 network_interface = address_v4::any();
	multicast::leave_group leave_option(multicast_address, network_interface);
	mSocket.set_option(leave_option);

	this->close();
	return 0;
}
int GeoAsioMcast::initRecvFrom()
{
	memset(mDataBuff, 0, sizeof(mDataBuff));

	//lambda表达式做匿名回调函数
	mSocket.async_receive_from(
		asio::buffer(mDataBuff, sizeof(mDataBuff)), mSenderEndpoint,
		[this](std::error_code ec, std::size_t bytes_recvd)
	{
		//成功接收则进行数据处理
		if (!ec && bytes_recvd > 0)
		{
			onRecieveFrom(bytes_recvd);
		}
		else
		{
			//do_receive();
		}
	});
	return 0;
}

int GeoAsioMcast::onRecieveFrom(int recvlen)
{
	int ret = -1;
	//此处返回值的设计是给上层应用的预留接口，
	//上层控制程序可以利用onData的返回值控制底层的处理流
	ret = onData(mDataBuff, recvlen);
	switch (ret)
	{
		//=0 成功接收,会继续
	case 0:
		initRecvFrom();
		break;
	case 1:
		break;
	case -1:
	default:

		break;

	}
	return 0;
}
//子类重载此函数，buff不要释放
int GeoAsioMcast::onData(void * buff, int len)
{
	return 0;

}
int GeoAsioMcast::sendTo(void * buff, int len)
{
	asio::ip::address addr = address_v4::from_string(mGroupIP);
	udp::endpoint sender_endpoint_(addr, mGroupPort);
	mSocket.async_send_to(
		asio::buffer(buff, len), sender_endpoint_,
		[this](std::error_code /*ec*/, std::size_t /*bytes_sent*/)
	{
		printf("send callback\n");
	});
	return 0;

}
int GeoAsioMcast::close()
{
	mSocket.close();
	return 0;
}