// yhcxpDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "SerialPort.h"

// CyhcxpDlg �Ի���
class CyhcxpDlg : public CDialogEx
{
// ����
public:
	CyhcxpDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YHCXP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnReceiveStr(WPARAM str, LPARAM commInfo);
	DECLARE_MESSAGE_MAP()
public:
	CSerialPort m_Serialport;
	int BaudRate[12] = { 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 56000, 57600, 115200 };
	//��������
	CComboBox m_port;
	//������
	CComboBox m_baudrate;
	// �򿪹رմ���
	CButton m_openclose;
	// �������ı�
	CEdit m_sendedit;
	afx_msg void OnBnClickedOpenclose();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedDeteccom();
	afx_msg void OnBnClickedTextclc();
	CEdit m_receive;
	afx_msg void OnBnClickedRecclc();
};
