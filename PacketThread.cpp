// PacketThread.cpp : ���� �����Դϴ�.
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
	SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("����!!"));
	return TRUE;
}

int CPacketThread::ExitInstance()
{
	SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("��~~"));
	return CWinThread::ExitInstance();
}

int CPacketThread::Run()
{

	TCHAR		szMsg[512]	= {0};
	CHAR		szErrBuf[PCAP_ERRBUF_SIZE]	= {0};

	USES_CONVERSION;

	// -- ����̽� �̸��� ������
	

	GetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_DEVICE, szMsg, 512);


	
	// -- ����̽� ����
	m_AdHandle = pcap_open_live(W2CA(szMsg), 65536, 65536, 1, szErrBuf);
	if (m_AdHandle == NULL) {
		wsprintf(szMsg, TEXT("[Error] ����̽� ���¿� �����߽��ϴ�.\n\n%s"), A2CW(szErrBuf));
		MessageBox(AfxGetMainWnd()->m_hWnd, szMsg, TITLE, MB_ICONERROR);
		return 0;
	}


	SetDlgItemText(AfxGetMainWnd()->m_hWnd, IDC_STATE, TEXT("��Ŷ ������ ���� ����"));
	pcap_loop(m_AdHandle, 0, Packet_Handler, NULL);


	pcap_close(m_AdHandle);
	m_AdHandle = NULL;


	return CWinThread::Run();
}


void CPacketThread::Packet_Handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{

	//ip_header* ih;                           // ip header
	//ih = (ip_header*)(pkt_data + 14);            // 14 �� �̴��� ����� ���̴�.

	g_ctrlLstPacket.AddList(header->ts.tv_sec, header->len, (u_char*)pkt_data);
}

BEGIN_MESSAGE_MAP(CPacketThread, CWinThread)
END_MESSAGE_MAP()


// CPacketThread �޽��� ó�����Դϴ�.
