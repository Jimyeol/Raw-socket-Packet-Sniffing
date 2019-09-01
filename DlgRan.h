#pragma once
#include "afxwin.h"

#include <pcap.h>
#include "Head.h"
#include "PacketListCtrl.h"


#pragma comment(lib, "wpcap.lib")


// CDlgRan ��ȭ �����Դϴ�.

class CDlgRan : public CDialog
{
	DECLARE_DYNAMIC(CDlgRan)

public:
	CDlgRan(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgRan();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_RAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ctrlLstDevice;
	afx_msg void OnLbnSelchangeLstDevice();
	virtual BOOL OnInitDialog();

	pcap_if_t *m_DeviceList;
	afx_msg void OnBnClickedBtnSel();
	afx_msg void OnBnClickedOk();
};
