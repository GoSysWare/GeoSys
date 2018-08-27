
#ifndef  GEOSYS_DB_VBUS_H__
#define  GEOSYS_DB_VBUS_H__


#include"geoConfig.h"

#include "geoBasicType.h"
#include "geoGUID.h"


#define RTK_BROADCAST_ADDR	"*"

#include <pshpack1.h>

typedef struct	__tag_GEO_HOST {
	char	Data[rtkm_node_key_length];
} GEO_Host;


typedef GEO_Host * PGEO_Host;
typedef const GEO_Host * PCGEO_Host;

typedef geoUInt16 VBUS_ID;
typedef geoUInt16 VBUS_PORT;

#define BUSID_NONE			0
#define BUSID_ALARM			5		/* alarm raising */
#define BUSID_RTDB			6		/* read/write data */	 
#define BUSID_SYSTEM		4		/* system command */	
#define BUSID_OPERATION		2		/* write device */
#define BUSID_CONFIG		1		/* online configuration */
#define BUSID_HISLOG		7
#define BUSID_EVENTLOG		8

#define BUSID_USER			64	   /* user defined bus id */

#define PORT_NONE				((VBUS_PORT)0)
#define PORT_ALL				((VBUS_PORT)-1)
#define PORT_ALL_SERVER			((VBUS_PORT)1)
#define PORT_ALL_CLIENT			((VBUS_PORT)2)
#define PORT_ALL_SLAVE			((VBUS_PORT)3)
#define PORT_ALL_NODE			((VBUS_PORT)4)

typedef struct	__tag_RTK_ADDR {
	GEO_Host		host;
	geoUInt16		port;
} GEO_Addr;

typedef struct __tag_RTK_PACKET {
	// header begins
	geoUInt32		version;		// 0x0,  RTK_VERSION
									// for reliable communication between different
									// versions of RTK interfaces on the network
	GEO_Addr 		src, dest;		// 0x4, sender & receiver in rtk-addr form
	GeoGUID			guid;			// 0x28, uniquely identifies a transaction	  
	geoUInt16		frgmt_id;		// 0x38, together with Guid and grpid, uniquely identifies a packet
	geoUInt16		total_frag;		// 0x3a, number of total segments
	geoUInt32		offset;			// 0x3c, data offset of this fragment into the big packet
	geoUInt32		data_size;		// 0x40, data size of this fragment
	geoUInt32		packet_type;	// 0x44, flags and type
	geoUInt16		grp_id;			// 0x48, group id
									// header ends
	char	 data[1];				// 0x4a, effective load
} GEO_Packet, *PGEO_Packet;
typedef const GEO_Packet * PCGEO_Packet;

#include<poppack.h>

#endif