// yhcxpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yhcxp.h"
#include "yhcxpDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CyhcxpDlg �Ի���



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


// CyhcxpDlg ��Ϣ�������

BOOL CyhcxpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CString temp;
	//��ӱ����ʵ�ֵ���ռ�
	for (int i = 0; i < sizeof(BaudRate) / sizeof(int); i++)
	{
		temp.Format(_T("%d"), BaudRate[i]);
		m_baudrate.AddString((LPCTSTR)temp);
	}
	temp.Format(_T("%d"), 9600);
	m_baudrate.SetCurSel(m_baudrate.FindString(0, temp));
	//ɨ�贮��
	m_Serialport.Hkey2ComboBox(m_port);
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T(""));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CyhcxpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CyhcxpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CyhcxpDlg::OnReceiveStr(WPARAM str, LPARAM commInfo)
{
	struct serialPortInfo
	{
		UINT portNr;//���ں�
		DWORD bytesRead;//��ȡ���ֽ���
	}*pCommInfo;
	pCommInfo = (serialPortInfo*)commInfo;

	/////////////����HEX����Щ//////////////
	int rec1;
	char* rec2 = (char*)str;
	rec1 = *rec2;
	CString str1((char*)str);
	str1.Format(_T("%x"), rec1);//��Ϊ%d����ת��Ϊʮ���ƺ���ʾ

	////////////////////////////////////////

	///////////�����ı������//////////////
	/*CString str1((char*)str);*/
	/////////////////////////////////////


	//char* m_str = (char*)str;
	//TCHAR* dest = NULL;
	//dest = new TCHAR[sizeof(TCHAR) * pCommInfo->bytesRead];
	//wmemcpy(dest, (TCHAR*)str, sizeof(TCHAR)* pCommInfo->bytesRead+1);

	//////��ȡָ�����ڵ�����
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
		AfxMessageBox(_T("���ݳ��ȴ���"));
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
	if (temp == _T("�رմ���"))
	{
		GetDlgItem(IDC_COM)->EnableWindow(true);
		GetDlgItem(IDC_BAUD)->EnableWindow(true);
		m_Serialport.ClosePort();
		m_openclose.SetWindowText(_T("�򿪴���"));
		GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("�����ѹر�"));
	}
	else if (m_port.GetCount() > 0)
	{
		if (m_Serialport.InitPort(this->GetSafeHwnd(),com_no, baudrate))//�򿪴���
		{
			temp.Format(_T("���� %d �Ѵ򿪣��趨�ô��ڵĲ�����Ϊ %d\n "), com_no, baudrate);
			GetDlgItem(IDC_COMSTATU)->SetWindowTextW(temp);
			m_Serialport.StartMonitoring();
			GetDlgItem(IDC_COM)->EnableWindow(false);
			GetDlgItem(IDC_BAUD)->EnableWindow(false);
			m_openclose.SetWindowText(_T("�رմ���"));
		}
		else
			AfxMessageBox(_T("�����ѱ�ռ��"));
	}
	else
		AfxMessageBox(_T("û�м�⵽�ô���"));
	UpdateData(false);
}


void CyhcxpDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TEXT)->SetFocus();
	CString temp;
	UpdateData(true);//���ؼ���ֵ��ֵ����Ա����
	m_openclose.GetWindowText(temp);
	if (temp == "�򿪴���")///û�д򿪴���
	{
		AfxMessageBox(_T("���ȴ򿪴���"));
		return;
	}

	/////////////�����ı��������///////////////////
	//��ñ༭�����ݲ�תL�� ��Ϊchar*
	//m_sendedit.GetWindowTextW(temp);
	//int len = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	//char *ptxtTemp = new char[len + 1];
	//WideCharToMultiByte(CP_ACP, 0, temp, -1, ptxtTemp, len, NULL, NULL);
	//m_Serialport.WriteToPort(ptxtTemp, (strlen(ptxtTemp)));//�˴���Ϊ������+1����Ϊ������+1
	//OutputDebugStringA(ptxtTemp);
	//delete[] ptxtTemp;
	////////////////////////////////////////////

	//////////////����HEX����Σ�һ��ֻ�ܷ�һ����//////////////////////
	//��ñ༭�����ݲ�תL�� ��Ϊchar*
	m_sendedit.GetWindowTextW(temp);
	int TextToSend;
	//TextToSend= _ttoi(temp);//����ת��Ϊʮ����
	swscanf_s(temp, _T("%x"), &TextToSend);//����ת��Ϊʮ�����ƣ��������ʱ��תΪCC��...����c���Ա�ʾΪ_stscanf(str,_T("%x"),&i);
	char ptxtTemp = TextToSend;
	m_Serialport.WriteToPort(&ptxtTemp, sizeof(ptxtTemp));
	///////////////////////////////////////////////

	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("�ı��ѷ���"));
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
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("������ɨ��"));
}


void CyhcxpDlg::OnBnClickedTextclc()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TEXT)->SetWindowText(_T(""));
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("�����������"));
}


void CyhcxpDlg::OnBnClickedRecclc()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TXTRECE)->SetWindowText(_T(""));
	GetDlgItem(IDC_COMSTATU)->SetWindowTextW(_T("�����������"));
}
