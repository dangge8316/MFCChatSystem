
// MFCChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

// CMFCChatClientDlg 对话框
class CMFCChatClientDlg : public CDialogEx
{
// 构造
public:
	CMFCChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATCLIENT_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedClearmsgBtn();
	afx_msg void OnBnClickedConnectBtn();  //标记
	afx_msg void OnBnClickedDisconnectBtn();
	CMySocket* m_client;
	CListBox m_list;
	CEdit m_input;
	afx_msg void OnBnClickedSendBtn();
	CString CutShowString(CString strMsg);
	afx_msg void OnBnClickedSavenameBtn();
	afx_msg void OnBnClickedAutosendCheck();
	CComboBox m_CWordColorCombo;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
