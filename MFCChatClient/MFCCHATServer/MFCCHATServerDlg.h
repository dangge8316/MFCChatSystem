
// MFCCHATServerDlg.h: 头文件
//

#pragma once
#include "CServerSocket.h"
#include "CChatSocket.h"

// CMFCCHATServerDlg 对话框
class CMFCCHATServerDlg : public CDialogEx
{
// 构造
public:
	CMFCCHATServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
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
	afx_msg void OnEnChangePortEdit();
	afx_msg void OnBnClickedStartBtn();
	CListBox m_list;
	CServerSocket* m_server;
	CChatSocket* m_chat;
	CTime m_time;	
};
