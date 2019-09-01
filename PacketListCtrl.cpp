// PacketListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Winpcap_01.h"
#include "PacketListCtrl.h"
#include "Head.h"


// CPacketListCtrl

IMPLEMENT_DYNAMIC(CPacketListCtrl, CListCtrl)

	CPacketListCtrl::CPacketListCtrl()
{

}

CPacketListCtrl::~CPacketListCtrl()
{
}


BEGIN_MESSAGE_MAP(CPacketListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CPacketListCtrl 메시지 처리기입니다.



BOOL CPacketListCtrl::CreateListCtrl(CWnd* pParentWindow)
{
	m_pParentWindow = pParentWindow;

	// -- 리스트 컨트롤 생성과 스타일 변경
	if (!Create(WS_CHILD | WS_BORDER | WS_VISIBLE, CRect(13, 13, 900, 300), pParentWindow, ID_PACKET_LISTCTRL)) return FALSE;
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	ModifyStyle(NULL, LVS_SHOWSELALWAYS);
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	// -- 컬럼헤더 추가
	InsertColumn(0, TEXT("ID"), LVCFMT_LEFT, 50);
	InsertColumn(1, TEXT("Time"), LVCFMT_LEFT, 100);
	InsertColumn(2, TEXT("Len"), LVCFMT_LEFT, 50);
	InsertColumn(3, TEXT("DestinationMacAddress"), LVCFMT_LEFT, 250);
	InsertColumn(4, TEXT("SourceMacAddress"), LVCFMT_LEFT, 250);
	InsertColumn(5, TEXT("Protocol"), LVCFMT_LEFT, 100);

	return TRUE;
}

VOID CPacketListCtrl::AddList(LONG tv_sec, INT nLen, u_char *btPacket)
{

	CHAR szcBuf[20];
	TCHAR szBuf[256];
	INT nItemCount;
	tm lTime;
	time_t Timet;



	CRect rt;
	CSize cSz;

	USES_CONVERSION;




	nItemCount = GetItemCount();

	// -- 개수 확인
	if (nItemCount >= PACKET_SIZE) {
		::SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("리스트가 너무 많습니다."));
		return;
	}

	// -- 항목 추가
	wsprintf(szBuf, TEXT("%d"), nItemCount+1);
	InsertItem(nItemCount, szBuf);

	Timet = tv_sec;
	localtime_s(&lTime, &Timet);
	strftime(szcBuf, sizeof(szcBuf), "%H:%M:%S", &lTime);
	SetItem(nItemCount, 1, LVIF_TEXT, A2CW(szcBuf), 0, 0, 0, 0);

	wsprintf(szBuf, TEXT("%d"), nLen);
	SetItem(nItemCount, 2, LVIF_TEXT, szBuf, 0, 0, 0, 0);



	////이더넷 맥어드레스 데스티네이션
	struct ether_header* eth;                  // ethernet header
	eth = (struct ether_header*) btPacket;
	UINT ptype = ntohs(eth->ether_type);

	ip_header* ih;                           // ip header
	ih = (ip_header*)(btPacket + 14);            // 14 는 이더넷 헤더의 길이다.

	if(  eth->ether_dhost.byte1 + eth->ether_dhost.byte2 + eth->ether_dhost.byte3
		+ eth->ether_dhost.byte4 + eth->ether_dhost.byte5 + eth->ether_dhost.byte6 == 1530)
	{
		wsprintf(szBuf, TEXT("Broad Cast"));

	}
	else
	{
		wsprintf(szBuf, TEXT("%02x:%02x:%02x:%02x:%02x:%02x"),
			eth->ether_dhost.byte1,   eth->ether_dhost.byte2,
			eth->ether_dhost.byte3,   eth->ether_dhost.byte4,
			eth->ether_dhost.byte5,   eth->ether_dhost.byte6);
	}
	SetItem(nItemCount, 3, LVIF_TEXT, szBuf, 0, 0, 0, 0);

	//이더넷 맥어드레스 소스
	wsprintf(szBuf, TEXT("%02x:%02x:%02x:%02x:%02x:%02x"),
		eth->ether_shost.byte1,   eth->ether_shost.byte2,
		eth->ether_shost.byte3,   eth->ether_shost.byte4,
		eth->ether_shost.byte5,   eth->ether_shost.byte6);
	SetItem(nItemCount, 4, LVIF_TEXT, szBuf, 0, 0, 0, 0);

	//프로토콜
	if( ptype == ARP_HEADER)
	{
		wsprintf(szBuf, TEXT("ARP"));
	}
	else if( ih->proto == 0x1 )
	{
		wsprintf(szBuf, TEXT("ICMP"));
	}
	else if( ih->proto == 0x6 )
	{
		tcp_header* th;
		th = (tcp_header*) ((u_char*)ih + (ih->ip_leng) * 4);
		if(ntohs(th->dport)==80 || ntohs(th->sport)==80)
			wsprintf(szBuf, TEXT("HTTP"));
		else
			wsprintf(szBuf, TEXT("TCP"));

	}
	else if( ih->proto == 0x11 )
	{
		udp_header* uh;
		uh = (udp_header*) ((u_char*)ih + (ih->ip_leng) * 4);
		if(ntohs(uh->dport)==53 || ntohs(uh->sport)==53)
			wsprintf(szBuf, TEXT("DNS"));
		else
			wsprintf(szBuf, TEXT("UDP"));
	}

	SetItem(nItemCount, 5, LVIF_TEXT, szBuf, 0, 0, 0, 0);


	//여기다가 TYPE추가

	// -- 패킷 복사함
	g_pPacket[g_nPacket] = new u_char[nLen];
	CopyMemory(g_pPacket[g_nPacket], btPacket, nLen);
	g_nPacketLen[g_nPacket] = nLen;
	g_nPacket++;


	// -- 스크룰을 아래로
	if (::IsDlgButtonChecked(AfxGetMainWnd()->m_hWnd, IDC_CHK_SCROLL) == 1) { 
		GetItemRect(0, &rt, LVIR_BOUNDS);
		cSz.SetSize(0, rt.Height()*nItemCount);
		Scroll(cSz);
	}
}


void CPacketListCtrl::OnLvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	if (pNMLV && (pNMLV->uNewState == (UINT)(LVIS_FOCUSED | LVIS_SELECTED))) {
		int nAt = pNMLV->iItem;
		TCHAR *szPacket;
		INT i, nPos = 0;


		szPacket = new TCHAR[g_nPacketLen[nAt]*1000];
		szPacket[0] = NULL;



		struct ether_header* eth;                  // ethernet header
		eth = (struct ether_header*) g_pPacket[nAt];
		UINT ptype = ntohs(eth->ether_type);

		ip_header* ih;                           // ip header
		ih = (ip_header*)(g_pPacket[nAt] + 14);            // 14 는 이더넷 헤더의 길이다.


		wsprintf(szPacket, TEXT("----- ETHERNET HEADER ------ \r\n"));


		wsprintf(szPacket, TEXT("%s Destination Mac Address : %02x:%02x:%02x:%02x:%02x:%02x \r\n"), szPacket,
			eth->ether_dhost.byte1,   eth->ether_dhost.byte2,
			eth->ether_dhost.byte3,   eth->ether_dhost.byte4,
			eth->ether_dhost.byte5,   eth->ether_dhost.byte6);
		wsprintf(szPacket, TEXT("%s Source Mac Address  : %02x:%02x:%02x:%02x:%02x:%02x\r\n"),
			szPacket,
			eth->ether_shost.byte1,   eth->ether_shost.byte2,
			eth->ether_shost.byte3,   eth->ether_shost.byte4,
			eth->ether_shost.byte5,   eth->ether_shost.byte6);

		if ( ntohs(eth->ether_type) == IP_HEADER )
		{
			wsprintf(szPacket, TEXT("%s ----- IP HEADER ------ \r\n"), 
				szPacket);
			wsprintf(szPacket, TEXT("%s ip version is %d \r\n"), szPacket, ih->ip_version);

			wsprintf(szPacket, TEXT("%s ip length is %d byte \r\n"),szPacket, (ih->ip_leng) * 4);

			wsprintf(szPacket, TEXT("%s Destination IP Address  : %d.%d.%d.%d \r\n"),
				szPacket, ih->daddr.byte1, ih->daddr.byte2, ih->daddr.byte3, ih->daddr.byte4); 
			wsprintf(szPacket, TEXT("%s Source IP Address  : %d.%d.%d.%d \r\n"),
				szPacket, ih->saddr.byte1, ih->saddr.byte2, ih->saddr.byte3, ih->saddr.byte4); 

			wsprintf(szPacket, TEXT("%s Identification  : 0x%X \r\n"),
				szPacket, ntohs(ih->identification)); 
			wsprintf(szPacket, TEXT("%s Flags  : %d \r\n"),
				szPacket, ih->flags_fo); 
			wsprintf(szPacket, TEXT("%s Time to Live  : %d \r\n"), szPacket, ih->ttl); 
			

			if ( ih->proto == 0x6 )
			{
				tcp_header* th;
				th = (tcp_header*) ((u_char*)ih + (ih->ip_leng) * 4);

				wsprintf(szPacket, TEXT("%s ----- TCP HEADER ------ \r\n"), 
					szPacket);
				wsprintf(szPacket, TEXT("%s Destination port number : %d \r\n"), 
					szPacket, ntohs(th->dport));
				wsprintf(szPacket, TEXT("%s Source port number : %d \r\n"), 
					szPacket, ntohs(th->sport));  
				wsprintf(szPacket, TEXT("%s Tcp checksum : %#04x \r\n"), 
					szPacket,  htons(th->crc)); 
				wsprintf(szPacket, TEXT("%s Window Size : %d \r\n"), 
					szPacket,  ntohs(th->win)); 
				wsprintf(szPacket, TEXT("%s Header length : %d byte \r\n"), 
					szPacket,  (th->th_off)/(byte)4); 
				wsprintf(szPacket, TEXT("%s Urgent pointer : %d \r\n"), 
					szPacket,  ntohs(th->urgptr)); 


				////_tprintf(_T("calc tcp checksum : %#04x\n"), tcp_checksum_calc(pkt_data, th, ih));

				switch( th->flags )
				{
				case SYN:
					wsprintf(szPacket, TEXT("%s Flags : SYN \r\n"), szPacket);
					break;
				case PUSH:
					wsprintf(szPacket, TEXT("%s Flags : PUSH \r\n"), szPacket);
					break;
				case ACK:
					wsprintf(szPacket, TEXT("%s Flags : ACK \r\n"), szPacket);
					break;
				case SYN_ACK:
					wsprintf(szPacket, TEXT("%s Flags : SYN_ACK \r\n"), szPacket);
					break;
				case PUSH_ACK:
					wsprintf(szPacket, TEXT("%s Flags : PUSH_ACK \r\n"), szPacket);
					break;
				case FIN_ACK:
					wsprintf(szPacket, TEXT("%s Flags : FIN_ACK \r\n"), szPacket);
					break;
				default:
					wsprintf(szPacket, TEXT("%s Flags (Unknown) : %04x \r\n"), szPacket
						, th->flags);
					break;
				}

				if( ntohs(th->dport)==80 && th->flags == PUSH_ACK)
				{
					http_header_request* hth_rq;

					hth_rq = (http_header_request*) ((u_char*)th + (th->th_off)/4);

					wsprintf(szPacket, TEXT("%s ----- HTTP HEADER ------ Request\r\n"), 
						szPacket);
					wsprintf(szPacket, TEXT("%s %c %c %c \r\n"), 
						szPacket, hth_rq->method[0], 
						hth_rq->method[1], hth_rq->method[2]);
				}
				else if( ntohs(th->sport)==80 && th->flags == PUSH_ACK)
				{
					http_header_response* hth_rp;

					hth_rp = (http_header_response*) ((u_char*)th + (th->th_off)/4);

					wsprintf(szPacket, TEXT("%s ----- HTTP HEADER ------ Response\r\n"), 
						szPacket);
					wsprintf(szPacket, TEXT("%s %c %c %c %c %c %c %c %c \r\n"), 
						szPacket, hth_rp->version[0], 
						hth_rp->version[1], hth_rp->version[2], hth_rp->version[3], 
						hth_rp->version[4], hth_rp->version[5], hth_rp->version[6],
						hth_rp->version[7]);

					
				}
			}
			else if ( ih->proto == 0x11 )
			{
				udp_header* uh;
				uh = (udp_header*) ((u_char*)ih + (ih->ip_leng) * 4);

				wsprintf(szPacket, TEXT("%s ----- UDP HEADER ------ \r\n"), 
					szPacket);
				wsprintf(szPacket, TEXT("%s Destination port number : %d \r\n"), 
					szPacket, ntohs(uh->dport));
				wsprintf(szPacket, TEXT("%s Source port number : %d \r\n"), 
					szPacket, ntohs(uh->sport));  
				wsprintf(szPacket, TEXT("%s Lenght : %d \r\n"), 
					szPacket, ntohs(uh->len));
				wsprintf(szPacket, TEXT("%s Checksum : %02x \r\n"), 
					szPacket, htons(uh->crc));  
				if( ntohs(uh->sport) == 53 )		//리스폰스 
				{
					dns_header* dh;
					dh = (dns_header*) ((u_char*)uh + sizeof(udp_header));
					wsprintf(szPacket, TEXT("%s ----- DNS HEADER ------(RESPONSE) \r\n"), 
						szPacket);

					wsprintf(szPacket, TEXT("%s Transaction ID : 0x%02x \r\n"), 
						szPacket, htons(dh->Xid));
					wsprintf(szPacket, TEXT("%s Flags : 0x%02x \r\n"), szPacket, htons(dh->flags));
					wsprintf(szPacket, TEXT("%s questions : %d \r\n"), szPacket, ntohs(dh->questions));
					wsprintf(szPacket, TEXT("%s Answer RRs : %d \r\n"), szPacket, ntohs(dh->answerRRs));
					wsprintf(szPacket, TEXT("%s Authority RRs : %d \r\n"), szPacket, ntohs(dh->authorityRRs));
					wsprintf(szPacket, TEXT("%s Additional RRs : %d \r\n"), szPacket, ntohs(dh->additionalRRs));

				}
				if(ntohs(uh->dport)==53){		//쿼리
					dns_header* dh;
					dh = (dns_header*) ((u_char*)uh + sizeof(udp_header));

					wsprintf(szPacket, TEXT("%s ----- DNS HEADER ------(Query) \r\n"), 
						szPacket);
					wsprintf(szPacket, TEXT("%s Transaction ID : 0x%02x \r\n"), 
						szPacket, htons(dh->Xid));
					wsprintf(szPacket, TEXT("%s Flags : 0x0%02x \r\n"), szPacket, htons(dh->flags));
					wsprintf(szPacket, TEXT("%s questions : %d \r\n"), szPacket, ntohs(dh->questions));
					wsprintf(szPacket, TEXT("%s Answer RRs : %d \r\n"), szPacket, ntohs(dh->answerRRs));
					wsprintf(szPacket, TEXT("%s Authority RRs : %d \r\n"), szPacket, ntohs(dh->authorityRRs));
					wsprintf(szPacket, TEXT("%s Additional RRs : %d \r\n"), szPacket, ntohs(dh->additionalRRs));

			
				}
			}
		}

		wsprintf(szPacket, TEXT("%s \r\n\r\n -----------HexView----------\r\n"), szPacket);

		for (i=0; i<g_nPacketLen[nAt]; i++) {
			wsprintf(szPacket, TEXT("%s %02X"), szPacket, g_pPacket[nAt][i]);
			if (((i+1) % 20) == 0) {
				wsprintf(szPacket, TEXT("%s\r\n"), szPacket);
			}
		}

		SetDlgItemText(IDC_EDIT_PACKET, szPacket);

		delete []szPacket;
	}


	*pResult = 0;
}
