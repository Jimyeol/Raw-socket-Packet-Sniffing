#pragma once

#include <pcap.h>
#include "afxwin.h"
#include "Head.h"
#include "PacketListCtrl.h"
#include "DlgRan.h"


#pragma comment(lib, "wpcap.lib")

// CPacketThread

class CPacketThread : public CWinThread
{
	DECLARE_DYNCREATE(CPacketThread)

protected:
	CPacketThread();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPacketThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	static void Packet_Handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data);

public:
	pcap_t *m_AdHandle;
	CDlgRan dlgRan;

protected:
	DECLARE_MESSAGE_MAP()
};


