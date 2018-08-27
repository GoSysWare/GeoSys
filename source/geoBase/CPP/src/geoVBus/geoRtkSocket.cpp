
#include "preCompile.h"
#include "rtkUdpSocket.h"




CRtkUdpSocket::CRtkUdpSocket()
{	
	head = 0;
	in_packets = out_packets = duplicated_packets = 0;
	in_bytes = out_bytes = 0;
	total_delay=0;
	memset(cached_packet_ids, -1, sizeof(cached_packet_ids));
	memset(cached_packet_times,0,sizeof cached_packet_times);
	ACE_NEW_NORETURN (recv_msg_buff, ACE_Message_Block (VBUS_MAX_PACKET_SIZE));
}

CRtkUdpSocket::~CRtkUdpSocket()
{
	if (recv_msg_buff)
	{
		recv_msg_buff->release();
	}
	


}

nicInt32 CRtkUdpSocket::OnReceive()
{
	int i;
	int  idx;
	int res = recv_msg_buff->length();
	
	if(res < (sizeof(nicRtkPacket) - 1)) {
		return 0;
	}
	nicRtkPacket * p=(nicRtkPacket*)recv_msg_buff->rd_ptr();

	if(!WillingToAccept(p)){
		return 0;
	}
	in_packets++;
	in_bytes += res;

	if(res < sizeof(nicRtkPacket)-1){
		return 0;
	}

	//检查是否是双网中的重复帧
	nicPacketID pid;
	pid.guid = p->guid;
	pid.src = p->src;
	pid.grp_id = p->grp_id;
	pid.frgmt_id = p->frgmt_id;
	for(i=0; i<cached_packets; i++){
		idx = head-1+i;
		if(idx<0) {
			idx += cached_packets;
		}
		if(idx >= cached_packets) {
			idx -= cached_packets;
		}
		if(!memcmp(&cached_packet_ids[idx], &pid, sizeof(pid))){
			break;
		}
	}
	if(i < cached_packets){
		nicRtkTime t1;
		nicInt64 delay = 0;
		nicRtkTime_Mark(&t1);
		delay = nicRtkTime_Diff(&cached_packet_times[idx],&t1);
#ifdef _DEBUG
		//char guid_name[128];
		//p->guid.to_string(guid_name);	       
		//ACE_DEBUG((LM_DEBUG,ACE_TEXT(
		//	"Packet duplicated, ID : %s:%d/%d/%d, Src=%s:%d delayed by %d ms\n"),
		//	guid_name, 
		//	p->grp_id,
		//	p->frgmt_id, 
		//	p->total_frag, 
		//	p->src.host.Data, 
		//	p->src.port, 
		//	delay
		//	));
#endif
		duplicated_packets++;
		total_delay+=delay;
		return 0;
	}
	cached_packet_ids[head] = pid;
	nicRtkTime_Mark(&cached_packet_times[head]); 
	head++;
	if(head == cached_packets) 
		head=0;

	OnPacket((nicRtkPacket*)recv_msg_buff->rd_ptr(), res);

	return res;
}

nicInt32 CRtkUdpSocket::OnReceive(int nErrorCode)
{
	if(nErrorCode) {
		ACE_ERROR((LM_ERROR,ACE_TEXT("%D,[%P|%t],%M,%N,%l Error %d occured in net-module chnl-%d.\n"),nErrorCode,RemotePort()));
		return 0;
	}
	int i;
	int  idx;
	int res = ReceiveFrom(buffer, sizeof(buffer), peerAddress);
	if(res < (sizeof(nicRtkPacket) - 1)) {
		return 0;
	}
	nicRtkPacket * p=(nicRtkPacket*)buffer;

	if(!WillingToAccept(p)){
		return 0;
	}

	in_packets++;
	in_bytes += res;

	if(res < sizeof(nicRtkPacket)-1){
		return 0;
	}

	//检查是否是双网中的重复帧
	nicPacketID pid;
	pid.guid = p->guid;
	pid.src = p->src;
	pid.grp_id = p->grp_id;
	pid.frgmt_id = p->frgmt_id;
	for(i=0; i<cached_packets; i++){
		idx = head-1+i;
		if(idx<0) {
			idx += cached_packets;
		}
		if(idx >= cached_packets) {
			idx -= cached_packets;
		}
		if(!memcmp(&cached_packet_ids[idx], &pid, sizeof(pid))){
			break;
		}
	}
	if(i < cached_packets){
		nicRtkTime t1;
		nicInt64 delay = 0;
		nicRtkTime_Mark(&t1);
		delay = nicRtkTime_Diff(&cached_packet_times[idx],&t1);
#ifdef _DEBUG
		//char guid_name[128];
		//p->guid.to_string(guid_name);	       
		//ACE_DEBUG((LM_DEBUG,ACE_TEXT(
		//	"Packet duplicated, ID : %s:%d/%d/%d, Src=%s:%d delayed by %d ms\n"),
		//	guid_name, 
		//	p->grp_id,
		//	p->frgmt_id, 
		//	p->total_frag, 
		//	p->src.host.Data, 
		//	p->src.port, 
		//	delay
		//	));
#endif
		duplicated_packets++;
		total_delay+=delay;
		return 0;
	}
	cached_packet_ids[head] = pid;
	nicRtkTime_Mark(&cached_packet_times[head]); 
	head++;
	if(head == cached_packets) 
		head=0;

	OnPacket((nicRtkPacket*)buffer, res);

	return res;
}
nicUInt16 CRtkUdpSocket::RemotePort()
{
	return peerAddress.get_port_number();
}
