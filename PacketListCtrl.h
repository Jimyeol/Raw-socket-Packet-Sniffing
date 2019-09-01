#pragma once


# define IP_HEADER               0x0800
# define ARP_HEADER               0x0806
# define REVERSE_ARP_HEADER      0x0835

# define SYN                     0x02
# define PUSH                     0x08
# define ACK                     0x10
# define SYN_ACK                  0x12
# define PUSH_ACK               0x18
# define FIN_ACK                  0x11

typedef struct mac_address
{
   u_char byte1;
   u_char byte2;
   u_char byte3;
   u_char byte4;
   u_char byte5;
   u_char byte6;
};

struct ether_header
{
   struct mac_address   ether_dhost;
   struct mac_address   ether_shost;
   u_short              ether_type;
};
struct ip_address
{
   u_char      byte1;
   u_char      byte2;
   u_char      byte3;
   u_char      byte4;
};

struct ip_header
{
   u_char         ip_leng:4;            
   u_char         ip_version:4;
   u_char         typeOfService;
   u_short        totalLen;
   u_short        identification;
   u_short        flags_fo;            //  flags(3비트) + fragment offset(13비트) 
   u_char         ttl;
   u_char         proto;
   u_short        crc;
   ip_address     saddr;
   ip_address     daddr;
   u_int          op_pad;
};

struct tcp_header
{
   u_short      sport;         // Source port
   u_short      dport;         // Destination port
   u_int         seqnum;         // Sequence Number
   u_int         acknum;         // Acknowledgement number
   byte         th_off;         // Header length
   u_char         flags;         // packet flags
   u_short      win;            // Window size
   u_short      crc;            // Header Checksum
   u_short      urgptr;         // Urgent pointer
   u_int         op_pad[10];   // option & padding
};

struct udp_header
{
   u_short      sport;         // Source port
   u_short      dport;         // Destination port
   u_short      len;            // Datagram length
   u_short      crc;            // Checksum
};

struct dns_header {
	WORD Xid;
	WORD flags;
	u_short questions;
	u_short answerRRs;
	u_short authorityRRs;
	u_short additionalRRs;
};


#pragma pack(push, 1)

struct ptcp_header
{
   ip_address      saddr;
   ip_address      daddr;
   u_char          reser;
   u_char          proto;
   u_short         tcp_seg;      // TCP header + data
   tcp_header      tcph;
};
#pragma pack(pop)


// CPacketListCtrl
#define ID_PACKET_LISTCTRL 0x10


struct http_header_request {
	u_char method[3];
};

struct http_header_response {
	u_char version[8];
};


class CPacketListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CPacketListCtrl)

public:
	CPacketListCtrl();
	virtual ~CPacketListCtrl();
	afx_msg void CPacketListCtrl::OnLvnItemChanged(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	DECLARE_MESSAGE_MAP()

public:
	CWnd* m_pParentWindow;
	CWnd* m_pLstWindow;
	struct ether_header* m_ehEth;

public:
	BOOL CreateListCtrl(CWnd* pParentWindow);
	VOID AddList(LONG tv_sec, INT nLen, u_char *btPacket);
};


