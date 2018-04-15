// yhcxpDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "SerialPort.h"

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
	int BaudRate[12] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200 };
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
};
