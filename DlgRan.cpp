// DlgRan.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Winpcap_01.h"
#include "DlgRan.h"
#include "afxdialogex.h"


// CDlgRan ��ȭ �����Դϴ�.

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


// CDlgRan �޽��� ó�����Դϴ�.


void CDlgRan::OnLbnSelchangeLstDevice()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	INT i = 0, nSel;
	pcap_if_t	*DeviceList;

	USES_CONVERSION;

	// -- ������ ����Ʈ ������
	nSel = m_ctrlLstDevice.GetCurSel();
	if (nSel == -1) {
		MessageBox(TEXT("����̽��� �������ּ���."), TITLE, MB_ICONEXCLAMATION);
		return;
	}

	DeviceList = m_DeviceList;

	// -- ������ ���� ����̽� �̸��� ������
	while (nSel != i) {
		DeviceList = DeviceList->next;
		i++;
	}

	// -- IDC_DEVICE�� ����̽� �̸��� ����
	SetDlgItemText(IDC_DEVICE, A2CW(DeviceList->name));

}


BOOL CDlgRan::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	pcap_if_t	*DeviceList					= NULL;
	TCHAR		szMsg[512]	= {0};
	CHAR		szErrBuf[PCAP_ERRBUF_SIZE]	= {0};

	USES_CONVERSION;

	// -- ��Ʈ��ũ ����̽� ����� ������
	if (pcap_findalldevs(&m_DeviceList, szErrBuf) == -1) {
		wsprintf(szMsg, TEXT("[Error] ��Ʈ��ũ ����̽� ����� ���� ���߽��ϴ�.\n\n%s"), A2CW(szErrBuf));
		MessageBox(szMsg, TITLE, MB_ICONERROR);
		return FALSE;
	}

	if (m_DeviceList == NULL) {
		MessageBox(TEXT("����̽� ����� �����ϴ�."), TITLE, MB_ICONEXCLAMATION);
		return FALSE;
	}

	// -- ����̽� ����� ����Ʈ�� �߰���
	DeviceList = m_DeviceList;
	while (DeviceList != NULL) {
		wsprintf(szMsg, TEXT("%s - %s"), A2CW(DeviceList->name), A2CW(DeviceList->description));
		m_ctrlLstDevice.AddString(szMsg);
		DeviceList = DeviceList->next;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CDlgRan::OnBnClickedBtnSel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
}


void CDlgRan::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	USES_CONVERSION;

	SetDlgItemText(IDC_DEVICE, A2CW(m_DeviceList->name));

	CDialog::OnOK();
}
