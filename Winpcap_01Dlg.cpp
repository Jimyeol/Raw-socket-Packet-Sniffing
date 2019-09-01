
// Winpcap_01Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Winpcap_01.h"
#include "Winpcap_01Dlg.h"
#include "PacketThread.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CWinpcap_01Dlg 대화 상자




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


// CWinpcap_01Dlg 메시지 처리기

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

	//// -- 네트워크 디바이스 목록을 가져옴
	//if (pcap_findalldevs(&m_DeviceList, szErrBuf) == -1) {
	//	wsprintf(szMsg, TEXT("[Error] 네트워크 디바이스 목록을 얻지 못했습니다.\n\n%s"), A2CW(szErrBuf));
	//	MessageBox(szMsg, TITLE, MB_ICONERROR);
	//	return FALSE;
	//}

	//if (m_DeviceList == NULL) {
	//	MessageBox(TEXT("디바이스 목록이 없습니다."), TITLE, MB_ICONEXCLAMATION);
	//	return FALSE;
	//}

	//// -- 디바이스 목록을 리스트에 추가함
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWinpcap_01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWinpcap_01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWinpcap_01Dlg::OnBnClickedBtnSel()
{
	//INT i = 0, nSel;
	//pcap_if_t	*DeviceList;

	//CDlgRan dlgRan;
	
	//// -- 선택한 리스트 가져옴
	//nSel = m_ctrlLstDevice.GetCurSel();
	//if (nSel == -1) {
	//	MessageBox(TEXT("디바이스를 선택해주세요."), TITLE, MB_ICONEXCLAMATION);
	//	return;
	//}

	//DeviceList = m_DeviceList;

	//// -- 선택한 셀의 디바이스 이름을 가져옴
	//while (nSel != i) {
	//	DeviceList = DeviceList->next;
	//	i++;
	//}

	// -- IDC_DEVICE에 디바이스 이름을 넣음
	
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

	// -- CPacketThread 쓰레드 실행
	m_PacketThread = (CPacketThread*)AfxBeginThread(RUNTIME_CLASS(CPacketThread)); 
}


void CWinpcap_01Dlg::OnBnClickedCaptureStop()
{
	DWORD dwExitCode;

	// -- 쓰레드가 실행중이면 강제 종료
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

