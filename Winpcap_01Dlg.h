
// Winpcap_01Dlg.h : 헤더 파일
//

#include <pcap.h>
#include "afxwin.h"
#include "Head.h"
#include "PacketListCtrl.h"
#include "DlgRan.h"



#pragma comment(lib, "wpcap.lib")


#pragma once


// CWinpcap_01Dlg 대화 상자
class CWinpcap_01Dlg : public CDialog
{
// 생성입니다.
public:
	CWinpcap_01Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WINPCAP_01_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
