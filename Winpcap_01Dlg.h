
// Winpcap_01Dlg.h : ��� ����
//

#include <pcap.h>
#include "afxwin.h"
#include "Head.h"
#include "PacketListCtrl.h"
#include "DlgRan.h"



#pragma comment(lib, "wpcap.lib")


#pragma once


// CWinpcap_01Dlg ��ȭ ����
class CWinpcap_01Dlg : public CDialog
{
// �����Դϴ�.
public:
	CWinpcap_01Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WINPCAP_01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()




public:
	pcap_if_t *m_DeviceList;
	CListBox m_ctrlLstDevice;
	CWinThread *m_PacketThread;
	CDlgRan dlgRan;

public:
	afx_msg void OnBnClickedBtnSel();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCapture();
	afx_msg void OnBnClickedCaptureStop();
};
