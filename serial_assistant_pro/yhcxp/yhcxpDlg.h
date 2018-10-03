// yhcxpDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "SerialPort.h"
#include<vector>

// CyhcxpDlg 对话框
class CyhcxpDlg : public CDialogEx
{
// 构造
public:
	CyhcxpDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YHCXP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnReceiveStr(WPARAM str, LPARAM commInfo);
	DECLARE_MESSAGE_MAP()
public:
	CSerialPort m_Serialport;
	std::vector <int> BaudRate;
	std::vector <int> Databits;
	std::vector <char*> stopbits;
	std::vector <char*> parity;
	//串口设置
	CComboBox m_port;
	//比特率
	CComboBox m_baudrate;
	// 打开关闭串口
	CButton m_openclose;
	// 待发送文本
	CEdit m_sendedit;
	afx_msg void OnBnClickedOpenclose();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedDeteccom();
	afx_msg void OnBnClickedTextclc();
	CEdit m_receive;
	afx_msg void OnBnClickedRecclc();
	// 数据位
	CComboBox m_databits;
	// 停止位
	CComboBox m_stopbits;
	// 奇偶位
	CComboBox m_parity;
	void CComboBoxInti();//初始化combobox控件
	bool send_model;//发送模式标志
	bool receive_model;//接收模式标志
	afx_msg void OnBnClickedSendhex();
	afx_msg void OnBnClickedSendchar();
	afx_msg void OnBnClickedReceivehex();
	afx_msg void OnBnClickedReceivechar();
	UINT sendcount;
	UINT receivecount;
	// 发送次数
	CStatic m_SendCount;
	// 接收次数
	CStatic m_ReceiveCount;
	afx_msg void OnBnClickedClearcount();
};
