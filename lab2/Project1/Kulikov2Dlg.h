
// Kulikov2Dlg.h : ���� ���������
//

#pragma once
#include "afxeditbrowsectrl.h"


// ���������� ���� CKulikov2Dlg
class CKulikov2Dlg : public CDialogEx
{
	// ��������
public:
	CKulikov2Dlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KULIKOV2_DIALOG };
#endif
protected:

	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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
