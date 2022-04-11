
// KulikovDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Kulikov2.h"
#include <vector>
#include <algorithm>
#include "Kulikov2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

														// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CKulikovDlg



CKulikov2Dlg::CKulikov2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_KULIKOV2_DIALOG, pParent)
	, edit1(_T(""))
	, edit2(_T(""))
	, edit3(_T(""))
	, edit5(_T(""))
	, edit4(_T(""))
	, edit6(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKulikov2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, browse1);
	DDX_Text(pDX, IDC_EDIT1, edit1);
	DDX_Control(pDX, IDC_MFCEDITBROWSE2, browse2);
	DDX_Text(pDX, IDC_EDIT2, edit2);
	DDX_Text(pDX, IDC_EDIT3, edit3);
	DDX_Text(pDX, IDC_EDIT4, edit5);
	DDX_Text(pDX, IDC_EDIT5, edit4);
	DDX_Text(pDX, IDC_EDIT6, edit6);
}

BEGIN_MESSAGE_MAP(CKulikov2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CKulikov2Dlg::OnEnChangeMfceditbrowse1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &CKulikov2Dlg::OnEnChangeMfceditbrowse2)
	ON_BN_CLICKED(IDC_BUTTON1, &CKulikov2Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CKulikov2Dlg::OnEnChangeMfceditbrowse1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE2, &CKulikov2Dlg::OnEnChangeMfceditbrowse2)
	ON_BN_CLICKED(IDC_BUTTON2, &CKulikov2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CKulikov2Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// обработчики сообщений CKulikovDlg

BOOL CKulikov2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

									// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CKulikov2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CKulikov2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CKulikov2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString ReadFile(CString filename) {
	CFile f;
	CString text = _T("");
	f.Open(filename, CFile::modeRead);
	int count = f.GetLength();
	unsigned char* data = new unsigned char[count];
	f.Read(data, count);
	for (int i = 0; i < count; i++)
		text += (unsigned char)data[i];
	f.Close();
	delete[] data;
	return text;
}


struct NewData {
	unsigned char ch;
	int k = 0;
};

NewData* FreqAnalyze(CString text) {

	NewData* data = new NewData[256];
	//for (int j = 0; j < 2; j++)
	//{
	for (int i = 0; i < text.GetLength(); i++)
	{
		unsigned char ch;
		ch = text[i];
		data[ch].k++;
		data[ch].ch = ch;
	}
	//}
	return data;
}

void sort(NewData* data) {
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256 - i; j++)
			if (data[j].k < data[j + 1].k) {
				NewData nd;
				nd = data[j];
				data[j] = data[j + 1];
				data[j + 1] = nd;
			}
}

void CKulikov2Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if (edit2.GetLength() == 0 && edit3.GetLength() == 0)
		::MessageBox(NULL, _T("Вы не загрузили файлы"), _T("Message"), MB_ICONASTERISK | MB_ICONINFORMATION);
	else
		if (edit2.GetLength() == 0)
			::MessageBox(NULL, _T("Отсутствует эталонный текст"), _T("Message"), MB_ICONASTERISK | MB_ICONINFORMATION);
		else
			if (edit1.GetLength() == 0)
				::MessageBox(NULL, _T("Отсутствует закодированный текст"), _T("Message"), MB_ICONASTERISK | MB_ICONINFORMATION);
			else
			{
				NewData* encrypt = FreqAnalyze(edit1);
				NewData* etalon = FreqAnalyze(edit2);
				sort(encrypt);
				sort(etalon);
				edit3 = _T("");
				for (int i = 0; i < edit1.GetLength(); i++)
					for (int j = 0; j < 256; j++) {
						if ((unsigned char)edit1[i] == encrypt[j].ch) {
							edit3 += etalon[j].ch;
						}
					}
				etalon = encrypt = NULL;
				delete[] etalon;
				delete[] encrypt;
			}
	UpdateData(FALSE);
}

void CKulikov2Dlg::OnEnChangeMfceditbrowse1()
{
	CString path; // local variable
	edit1 = "";
	browse1.GetWindowText(path);
	edit1 = ReadFile(path);
	UpdateData(FALSE);
}

void CKulikov2Dlg::OnEnChangeMfceditbrowse2()
{
	CString path; // local variable
	edit2 = "";
	browse2.GetWindowText(path);
	edit2 = ReadFile(path);
	UpdateData(FALSE);

}






void CKulikov2Dlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	edit3.Replace(edit4[0], edit5[0]);
	::MessageBox(NULL, _T("Замена произведена!"), _T("Message"), MB_ICONASTERISK | MB_ICONINFORMATION);

	UpdateData(FALSE);
	// TODO: добавьте свой код обработчика уведомлений
}


void CKulikov2Dlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	CFile f;
	f.Open(edit6, CFile::modeCreate | CFile::modeWrite);

	if (edit3.GetLength() == 0) {
		::MessageBox(NULL, _T("Отсутствует текст который требуется сохранить!"), _T("Error"), MB_ICONEXCLAMATION | MB_ICONWARNING);
		return;
	}

	unsigned char* output = new unsigned char[edit3.GetLength()];
	for (int i = 0; i < edit3.GetLength(); i++)  output[i] = edit3[i];
	f.Write(output, edit3.GetLength());
	::MessageBox(NULL, _T("Сохранение завершено"), _T("Message"), MB_ICONASTERISK | MB_ICONINFORMATION);


	delete[] output;
	// TODO: добавьте свой код обработчика уведомлений
}
