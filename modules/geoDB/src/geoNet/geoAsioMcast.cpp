
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
	//���ipΪ�գ���������IP,������ΪADDR_ANY
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

	//����󶨶˿�
	this->open(mGroupPort);

	//�˿ڸ�������
	asio::socket_base::reuse_address reuse_option(true);
	mSocket.set_option(reuse_option);

	//����󶨶˿�
	this->bind(mGroupPort);

	//���öಥ��ַ
	//ѡ�񱾵�IP����ಥ��
	address_v4 multicast_address = address_v4::from_string(ip);
	if (!multicast_address.is_multicast())
		return  -1;
	address_v4 network_interface = address_v4::any();
	multicast::join_group join_option(multicast_address,network_interface);
	mSocket.set_option(join_option);

	//����TTL
	asio::ip::multicast::hops ttl_option(mGroupTTL);
	mSocket.set_option(ttl_option);

	//���ûػ�
	//�ػ��Ƕಥ��ʱ���Լ�Ҳ�����յ�
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

	//lambda���ʽ�������ص�����
	mSocket.async_receive_from(
		asio::buffer(mDataBuff, sizeof(mDataBuff)), mSenderEndpoint,
		[this](std::error_code ec, std::size_t bytes_recvd)
	{
		//�ɹ�������������ݴ���
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
	//�˴�����ֵ������Ǹ��ϲ�Ӧ�õ�Ԥ���ӿڣ�
	//�ϲ���Ƴ����������onData�ķ���ֵ���Ƶײ�Ĵ�����
	ret = onData(mDataBuff, recvlen);
	switch (ret)
	{
		//=0 �ɹ�����,�����
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
//�������ش˺�����buff��Ҫ�ͷ�
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