
// Winpcap_01Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Winpcap_01.h"
#include "Winpcap_01Dlg.h"
#include "PacketThread.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CWinpcap_01Dlg ��ȭ ����




CWinpcap_01Dlg::CWinpcap_01Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinpcap_01Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DeviceList = NULL;
	m_PacketThread = NULL;
}

void CWinpcap_01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LST_DEVICE, m_ctrlLstDevice);
}

BEGIN_MESSAGE_MAP(CWinpcap_01Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BTN_SEL, &CWinpcap_01Dlg::OnBnClickedBtnSel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CAPTURE, &CWinpcap_01Dlg::OnBnClickedCapture)
	ON_BN_CLICKED(IDC_CAPTURE_STOP, &CWinpcap_01Dlg::OnBnClickedCaptureStop)
	ON_NOTIFY(LVN_ITEMCHANGED, ID_PACKET_LISTCTRL, &CPacketListCtrl::OnLvnItemChanged)
END_MESSAGE_MAP()


// CWinpcap_01Dlg �޽��� ó����

BOOL CWinpcap_01Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);


	g_ctrlLstPacket.CreateListCtrl(this);
	CheckDlgButton(IDC_CHK_SCROLL, 1);


	if( dlgRan.DoModal() == IDOK)
	{

	}

	//pcap_if_t	*DeviceList					= NULL;
	//TCHAR		szMsg[512]	= {0};
	//CHAR		szErrBuf[PCAP_ERRBUF_SIZE]	= {0};

	//USES_CONVERSION;

	//// -- ��Ʈ��ũ ����̽� ����� ������
	//if (pcap_findalldevs(&m_DeviceList, szErrBuf) == -1) {
	//	wsprintf(szMsg, TEXT("[Error] ��Ʈ��ũ ����̽� ����� ���� ���߽��ϴ�.\n\n%s"), A2CW(szErrBuf));
	//	MessageBox(szMsg, TITLE, MB_ICONERROR);
	//	return FALSE;
	//}

	//if (m_DeviceList == NULL) {
	//	MessageBox(TEXT("����̽� ����� �����ϴ�."), TITLE, MB_ICONEXCLAMATION);
	//	return FALSE;
	//}

	//// -- ����̽� ����� ����Ʈ�� �߰���
	//DeviceList = m_DeviceList;
	//while (DeviceList != NULL) {
	//	wsprintf(szMsg, TEXT("%s - %s"), A2CW(DeviceList->name), A2CW(DeviceList->description));
	//	m_ctrlLstDevice.AddString(szMsg);
	//	DeviceList = DeviceList->next;
	//}

	return TRUE;
}

void CWinpcap_01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CWinpcap_01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CWinpcap_01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWinpcap_01Dlg::OnBnClickedBtnSel()
{
	//INT i = 0, nSel;
	//pcap_if_t	*DeviceList;

	//CDlgRan dlgRan;
	
	//// -- ������ ����Ʈ ������
	//nSel = m_ctrlLstDevice.GetCurSel();
	//if (nSel == -1) {
	//	MessageBox(TEXT("����̽��� �������ּ���."), TITLE, MB_ICONEXCLAMATION);
	//	return;
	//}

	//DeviceList = m_DeviceList;

	//// -- ������ ���� ����̽� �̸��� ������
	//while (nSel != i) {
	//	DeviceList = DeviceList->next;
	//	i++;
	//}

	// -- IDC_DEVICE�� ����̽� �̸��� ����
	
}

void CWinpcap_01Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	OnBnClickedCaptureStop();

	if (m_DeviceList != NULL) pcap_freealldevs(m_DeviceList);


	INT i;
	for (i=0; i<g_nPacket; i++) {
		if (g_pPacket[i] != NULL) delete [] g_pPacket[i];
	}
	g_nPacket = 0;
}

void CWinpcap_01Dlg::OnBnClickedCapture()
{
	USES_CONVERSION;

	SetDlgItemText(IDC_DEVICE, A2CW(dlgRan.m_DeviceList->name));

	OnBnClickedCaptureStop();

	// -- CPacketThread ������ ����
	m_PacketThread = (CPacketThread*)AfxBeginThread(RUNTIME_CLASS(CPacketThread)); 
}


void CWinpcap_01Dlg::OnBnClickedCaptureStop()
{
	DWORD dwExitCode;

	// -- �����尡 �������̸� ���� ����
	if (m_PacketThread != NULL) {
		GetExitCodeThread(m_PacketThread->m_hThread, &dwExitCode);
		if (dwExitCode == STILL_ACTIVE) {
			m_PacketThread->SuspendThread();
			m_PacketThread->ExitInstance();
			delete m_PacketThread;
		}
		m_PacketThread = NULL;
	}

	INT i;
	for (i=0; i<g_nPacket; i++) {
		if (g_pPacket[i] != NULL) delete [] g_pPacket[i];
	}
	g_pPacket[0] = NULL;
	g_nPacketLen[0] = 0;
	g_nPacket = 0;
	g_ctrlLstPacket.DeleteAllItems();
}

