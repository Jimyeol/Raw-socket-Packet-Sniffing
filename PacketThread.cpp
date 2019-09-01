// PacketThread.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Winpcap_01.h"
#include "PacketThread.h"



// CPacketThread

IMPLEMENT_DYNCREATE(CPacketThread, CWinThread)

CPacketThread::CPacketThread()
{
	m_AdHandle = NULL;
}

CPacketThread::~CPacketThread()
{

	if (m_AdHandle != NULL) pcap_close(m_AdHandle);
}

BOOL CPacketThread::InitInstance()
{
	SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("시작!!"));
	return TRUE;
}

int CPacketThread::ExitInstance()
{
	SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("끝~~"));
	return CWinThread::ExitInstance();
}

int CPacketThread::Run()
{

	TCHAR		szMsg[512]	= {0};
	CHAR		szErrBuf[PCAP_ERRBUF_SIZE]	= {0};

	USES_CONVERSION;

	// -- 디바이스 이름을 가져옴
	

	GetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_DEVICE, szMsg, 512);


	
	// -- 디바이스 오픈
	m_AdHandle = pcap_open_live(W2CA(szMsg), 65536, 65536, 1, szErrBuf);
	if (m_AdHandle == NULL) {
		wsprintf(szMsg, TEXT("[Error] 디바이스 오픈에 실패했습니다.\n\n%s"), A2CW(szErrBuf));
		MessageBox(AfxGetMainWnd()->m_hWnd, szMsg, TITLE, MB_ICONERROR);
		return 0;
	}


	SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("패킷 쓰레드 루프 시작"));
	pcap_loop(m_AdHandle, 0, Packet_Handler, NULL);


	pcap_close(m_AdHandle);
	m_AdHandle = NULL;


	return CWinThread::Run();
}


void CPacketThread::Packet_Handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{

	//ip_header* ih;                           // ip header
	//ih = (ip_header*)(pkt_data + 14);            // 14 는 이더넷 헤더의 길이다.

	g_ctrlLstPacket.AddList(header->ts.tv_sec, header->len, (u_char*)pkt_data);
}

BEGIN_MESSAGE_MAP(CPacketThread, CWinThread)
END_MESSAGE_MAP()


// CPacketThread 메시지 처리기입니다.
