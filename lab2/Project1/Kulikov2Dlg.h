
// Kulikov2Dlg.h : файл заголовка
//

#pragma once
#include "afxeditbrowsectrl.h"


// диалоговое окно CKulikov2Dlg
class CKulikov2Dlg : public CDialogEx
{
	// Создание
public:
	CKulikov2Dlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KULIKOV2_DIALOG };
#endif
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CMFCEditBrowseCtrl browse1;
	CMFCEditBrowseCtrl browse2;
	CString edit1;
	CString edit2;
	CString edit3;
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnEnChangeMfceditbrowse2();
	CString edit5;
	CString edit4;
	afx_msg void OnBnClickedButton2();
	CString edit6;
	afx_msg void OnBnClickedButton3();
};
