
// Kulikov2.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CKulikov2App:
// � ���������� ������� ������ ��. Kulikov2.cpp
//

class CKulikov2App : public CWinApp
{
public:
	CKulikov2App();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CKulikov2App theApp;