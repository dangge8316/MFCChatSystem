
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
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


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORYMSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCChatClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCChatClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCChatClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCChatClientDlg::OnBnClickedSavenameBtn)
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("6000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));
	//从配置文件中获取昵称
	WCHAR wszName[MAX_PATH] = { 0 };
	WCHAR strPath[MAX_PATH] = { 0 };
	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);
	TRACE("[Chat Client]strPath=%ls", strPath);
	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"), _T("NAME"), NULL,wszName,MAX_PATH,strFilePath);
	if (dwNum > 0)
	{
		TRACE("[Chat Client]wszName=%ls", wszName);
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);
	}
	else
	{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"客户端", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT, L"客户端");
		UpdateData(FALSE);
	}
// 	TRACE("[Chat Client]wszName=%ls", wszName);
// 	SetDlgItemText(IDC_NAME_EDIT, wszName);
// 	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatClientDlg::OnPaint()
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
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCChatClientDlg::OnBnClickedClearmsgBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}

//定义一个显示信息的成员函数
CString CMFCChatClientDlg::CutShowString(CString strMsg)
{
	//格式:时间+昵称+消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");
	CString strShow;
	strShow = strTime + _T(" ") + strShow;
	//strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

void CMFCChatClientDlg::OnBnClickedConnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//把IP和端口号拿到
	TRACE("[Chat Client]Connect Button");
	CString csPort, csIp;
	//从控件里获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(csPort);
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(csIp);
	
	//cstring 转char* 使用USES_CONVERSION
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(csPort);
	LPCSTR szIP = (LPCSTR)T2A(csIp);
	TRACE("[Chat Client]szPort=%s,szIp=%s", szPort, szIP);
	UINT uPort = _ttoi(csPort);

	//连接时new一个CMySocket对象去连接
	m_client = new CMySocket;
	//创建一个套接字 容错
	if (!m_client->Create())
	{
		TRACE("[Chat Client]m_client Create error %d", GetLastError());
		return;
	}
	else
	{
		TRACE("[Chat Client]m_client Create Success...");
	}
	//连接
	if (m_client->Connect(csIp, uPort) != SOCKET_ERROR)
	{
		TRACE("[Chat Client]m_client Connect errorCode=%d", GetLastError());
		return;
	}
}


void CMFCChatClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCChatClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);
	CString strname;
	GetDlgItemText(IDC_NAME_EDIT, strname);
	strTmpMsg = strname + _T(": ") + strTmpMsg;
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);
	//2.发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);
	//3.显示到列表框里
	CString strShow;
	//CString strInfo = _T("我: ");
	CString strMsg = _T("");
	strShow = CutShowString(strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));

}


void CMFCChatClientDlg::OnBnClickedSavenameBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存昵称
// 	WritePrivateProfileStringW(
// 		_In_opt_ LPCWSTR lpAppName, //项名
// 		_In_opt_ LPCWSTR lpKeyName, //键名
// 		_In_opt_ LPCWSTR lpString,  //内容
// 		_In_opt_ LPCWSTR lpFileName //路径
// 	);
	CString strName;
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength()<=0)
	{
		MessageBox(L"昵称不能为空");
		return;
	}
	if (IDOK == AfxMessageBox(_T("确定要修改昵称吗?"), MB_OKCANCEL))
	{
		
		WCHAR strPath[MAX_PATH] = { 0 };
		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);
		TRACE("[Chat Client]strPath=%ls", strPath);
		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);
		//从控件中读取文本(昵称)
		GetDlgItemText(IDC_NAME_EDIT, strName);
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}	
}
