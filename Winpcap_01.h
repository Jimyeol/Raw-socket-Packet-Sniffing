
// Winpcap_01.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CWinpcap_01App:
// �� Ŭ������ ������ ���ؼ��� Winpcap_01.cpp�� �����Ͻʽÿ�.
//

class CWinpcap_01App : public CWinAppEx
{
public:
	CWinpcap_01App();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CWinpcap_01App theApp;