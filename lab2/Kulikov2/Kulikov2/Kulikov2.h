
// Kulikov2.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CKulikov2App:
// О реализации данного класса см. Kulikov2.cpp
//

class CKulikov2App : public CWinApp
{
public:
	CKulikov2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CKulikov2App theApp;