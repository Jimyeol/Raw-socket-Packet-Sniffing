// DlgRan.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Winpcap_01.h"
#include "DlgRan.h"
#include "afxdialogex.h"


// CDlgRan 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgRan, CDialog)

CDlgRan::CDlgRan(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRan::IDD, pParent)
{

}

CDlgRan::~CDlgRan()
{
}

void CDlgRan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_DEVICE, m_ctrlLstDevice);
}


BEGIN_MESSAGE_MAP(CDlgRan, CDialog)
	ON_LBN_SELCHANGE(IDC_LST_DEVICE, &CDlgRan::OnLbnSelchangeLstDevice)
	ON_BN_CLICKED(IDC_BTN_SEL, &CDlgRan::OnBnClickedBtnSel)
	ON_BN_CLICKED(IDOK, &CDlgRan::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgRan 메시지 처리기입니다.


void CDlgRan::OnLbnSelchangeLstDevice()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	INT i = 0, nSel;
	pcap_if_t	*DeviceList;

	USES_CONVERSION;

	// -- 선택한 리스트 가져옴
	nSel = m_ctrlLstDevice.GetCurSel();
	if (nSel == -1) {
		MessageBox(TEXT("디바이스를 선택해주세요."), TITLE, MB_ICONEXCLAMATION);
		return;
	}

	DeviceList = m_DeviceList;

	// -- 선택한 셀의 디바이스 이름을 가져옴
	while (nSel != i) {
		DeviceList = DeviceList->next;
		i++;
	}

	// -- IDC_DEVICE에 디바이스 이름을 넣음
	SetDlgItemText(IDC_DEVICE, A2CW(DeviceList->name));

}


BOOL CDlgRan::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	pcap_if_t	*DeviceList					= NULL;
	TCHAR		szMsg[512]	= {0};
	CHAR		szErrBuf[PCAP_ERRBUF_SIZE]	= {0};

	USES_CONVERSION;

	// -- 네트워크 디바이스 목록을 가져옴
	if (pcap_findalldevs(&m_DeviceList, szErrBuf) == -1) {
		wsprintf(szMsg, TEXT("[Error] 네트워크 디바이스 목록을 얻지 못했습니다.\n\n%s"), A2CW(szErrBuf));
		MessageBox(szMsg, TITLE, MB_ICONERROR);
		return FALSE;
	}

	if (m_DeviceList == NULL) {
		MessageBox(TEXT("디바이스 목록이 없습니다."), TITLE, MB_ICONEXCLAMATION);
		return FALSE;
	}

	// -- 디바이스 목록을 리스트에 추가함
	DeviceList = m_DeviceList;
	while (DeviceList != NULL) {
		wsprintf(szMsg, TEXT("%s - %s"), A2CW(DeviceList->name), A2CW(DeviceList->description));
		m_ctrlLstDevice.AddString(szMsg);
		DeviceList = DeviceList->next;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgRan::OnBnClickedBtnSel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
}


void CDlgRan::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	USES_CONVERSION;

	SetDlgItemText(IDC_DEVICE, A2CW(m_DeviceList->name));

	CDialog::OnOK();
}
