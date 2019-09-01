#pragma once
#include "afxwin.h"

#include <pcap.h>
#include "Head.h"
#include "PacketListCtrl.h"


#pragma comment(lib, "wpcap.lib")


// CDlgRan 대화 상자입니다.

class CDlgRan : public CDialog
{
	DECLARE_DYNAMIC(CDlgRan)

public:
	CDlgRan(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgRan();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_RAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrlLstDevice;
	afx_msg void OnLbnSelchangeLstDevice();
	virtual BOOL OnInitDialog();

	pcap_if_t *m_DeviceList;
	afx_msg void OnBnClickedBtnSel();
	afx_msg void OnBnClickedOk();
};
