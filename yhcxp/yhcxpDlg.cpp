// yhcxpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "yhcxp.h"
#include "yhcxpDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CyhcxpDlg 对话框



CyhcxpDlg::CyhcxpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_YHCXP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CyhcxpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COM, m_port);
	DDX_Control(pDX, IDC_BAUD, m_baudrate);
	DDX_Control(pDX, IDC_OPENCLOSE, m_openclose);
	DDX_Control(pDX, IDC_TEXT, m_sendedit);
	DDX_Control(pDX, IDC_TXTRECE, m_receive);
}

BEGIN_MESSAGE_MAP(CyhcxpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(Wm_SerialPort_RXSTR, &CyhcxpDlg::OnReceiveStr)
	ON_BN_CLICKED(IDC_OPENCLOSE, &CyhcxpDlg::OnBnClickedOpenclose)
	ON_BN_CLICKED(IDC_SEND, &CyhcxpDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_EXIT, &CyhcxpDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_DETECCOM, &CyhcxpDlg::OnBnClickedDeteccom)
	ON_BN_CLICKED(IDC_TEXTCLC, &CyhcxpDlg::OnBnClickedTextclc)
	ON_BN_CLICKED(IDC_RECCLC, &CyhcxpDlg::OnBnClickedRecclc)
END_MESSAGE_MAP()


// CyhcxpDlg 消息处理程序

BOOL CyhcxpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString temp;
	//添加比特率的值到空间
	for (int i = 0; i < sizeof(BaudRate) / sizeof(int); i++)
	{
		temp.Format(_T("%d"), BaudRate[i]);
		m_baudrate.AddString((LPCTSTR)temp);
	}
	temp.Format(_T("%d"), 9600);
	m_baudrate.SetCurSel(m_baudrate.FindString(0, temp));
	//扫描串口
	m_Serialport.Hkey2ComboBox(m_port);
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T(""));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CyhcxpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CyhcxpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CyhcxpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CyhcxpDlg::OnReceiveStr(WPARAM str, LPARAM commInfo)
{
	struct serialPortInfo
	{
		UINT portNr;//串口号
		DWORD bytesRead;//读取的字节数
	}*pCommInfo;
	pCommInfo = (serialPortInfo*)commInfo;

	/////////////接收HEX用这些//////////////
	int rec1;
	char* rec2 = (char*)str;
	rec1 = *rec2;
	CString str1((char*)str);
	str1.Format(_T("%x"), rec1);//若为%d则是转化为十进制后显示

	////////////////////////////////////////

	///////////接收文本用这句//////////////
	/*CString str1((char*)str);*/
	/////////////////////////////////////


	//char* m_str = (char*)str;
	//TCHAR* dest = NULL;
	//dest = new TCHAR[sizeof(TCHAR) * pCommInfo->bytesRead];
	//wmemcpy(dest, (TCHAR*)str, sizeof(TCHAR)* pCommInfo->bytesRead+1);

	//////获取指定串口的数据
	//if (pCommInfo->portNr == 2)
	//{
	int len = _tcslen(str1.GetBuffer(0));
	OutputDebugString(str1);
	//if (len == pCommInfo->bytesRead)
	//{
		m_receive.SetSel(-1, -1);
		m_receive.ReplaceSel(str1);

		m_receive.SetSel(-1, -1);
		m_receive.ReplaceSel(_T(" "));
		
	/*}
	else
	{
		AfxMessageBox(_T("数据长度错误"));
	}*/
	//}
	return TRUE;
}

void CyhcxpDlg::OnBnClickedOpenclose()
{
	// TODO: Add your control notification handler code here
	CString temp;
	int com_no, baudrate;
	UpdateData(true);
	m_port.GetWindowText(temp);
	temp.Delete(0, 3);
	com_no = _tstoi(temp);
	m_baudrate.GetWindowText(temp);
	baudrate = _tstoi(temp);
	m_openclose.GetWindowText(temp);
	if (temp == _T("关闭串口"))
	{
		GetDlgItem(IDC_COM)->EnableWindow(true);
		GetDlgItem(IDC_BAUD)->EnableWindow(true);
		m_Serialport.ClosePort();
		m_openclose.SetWindowText(_T("打开串口"));
		GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("串口已关闭"));
	}
	else if (m_port.GetCount() > 0)
	{
		if (m_Serialport.InitPort(this->GetSafeHwnd(),com_no, baudrate))//打开串口
		{
			temp.Format(_T("串口 %d 已打开，设定该串口的波特率为 %d\n "), com_no, baudrate);
			GetDlgItem(IDC_COMSTATU)->SetWindowTextW(temp);
			m_Serialport.StartMonitoring();
			GetDlgItem(IDC_COM)->EnableWindow(false);
			GetDlgItem(IDC_BAUD)->EnableWindow(false);
			m_openclose.SetWindowText(_T("关闭串口"));
		}
		else
			AfxMessageBox(_T("串口已被占用"));
	}
	else
		AfxMessageBox(_T("没有检测到该串口"));
	UpdateData(false);
}


void CyhcxpDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TEXT)->SetFocus();
	CString temp;
	UpdateData(true);//将控件的值赋值给成员变量
	m_openclose.GetWindowText(temp);
	if (temp == "打开串口")///没有打开串口
	{
		AfxMessageBox(_T("请先打开串口"));
		return;
	}

	/////////////若发文本则用这段///////////////////
	//获得编辑框内容并转L“ ”为char*
	//m_sendedit.GetWindowTextW(temp);
	//int len = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	//char *ptxtTemp = new char[len + 1];
	//WideCharToMultiByte(CP_ACP, 0, temp, -1, ptxtTemp, len, NULL, NULL);
	//m_Serialport.WriteToPort(ptxtTemp, (strlen(ptxtTemp)));//此处若为汉字则+1，若为整数则不+1
	//OutputDebugStringA(ptxtTemp);
	//delete[] ptxtTemp;
	////////////////////////////////////////////

	//////////////若发HEX用这段（一次只能发一个）//////////////////////
	//获得编辑框内容并转L“ ”为char*
	m_sendedit.GetWindowTextW(temp);
	int TextToSend;
	//TextToSend= _ttoi(temp);//若被转的为十进制
	swscanf_s(temp, _T("%x"), &TextToSend);//若被转的为十六进制（输入错误时会转为CC）...若用c语言表示为_stscanf(str,_T("%x"),&i);
	char ptxtTemp = TextToSend;
	m_Serialport.WriteToPort(&ptxtTemp, sizeof(ptxtTemp));
	///////////////////////////////////////////////

	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("文本已发送"));
	UpdateData(false);
}


void CyhcxpDlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	m_Serialport.ClosePort();
	CDialogEx::OnCancel();
}




void CyhcxpDlg::OnBnClickedDeteccom()
{
	// TODO: Add your control notification handler code here
	m_Serialport.Hkey2ComboBox(m_port);
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("串口已扫描"));
}


void CyhcxpDlg::OnBnClickedTextclc()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TEXT)->SetWindowText(_T(""));
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("发送区已清空"));
}


void CyhcxpDlg::OnBnClickedRecclc()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TXTRECE)->SetWindowText(_T(""));
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("接收区已清空"));
}
