
// MFCCHATServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCCHATServer.h"
#include "MFCCHATServerDlg.h"
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


// CMFCCHATServerDlg 对话框



CMFCCHATServerDlg::CMFCCHATServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCHATServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CMFCCHATServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_PORT_EDIT, &CMFCCHATServerDlg::OnEnChangePortEdit)
	ON_BN_CLICKED(IDC_START_BTN, &CMFCCHATServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCCHATServerDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCCHATServerDlg 消息处理程序

BOOL CMFCCHATServerDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCHATServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCCHATServerDlg::OnPaint()
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
HCURSOR CMFCCHATServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCHATServerDlg::OnEnChangePortEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//定义一个显示信息的成员函数
CString CMFCCHATServerDlg::CutShowString(CString strInfo, CString strMsg)
{
	//格式:时间+昵称+消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X");
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}

void CMFCCHATServerDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("[Chat Client]Start Server");
	//从控件里获取内容
	CString csPort;
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(csPort);
	//cstring 转char* 使用USES_CONVERSION
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(csPort);
	TRACE("[Chat Server]szPort=%s", szPort);
	UINT uPort;
	uPort = _ttoi(csPort);
	//启动时,new一个seversocket
	//创建一个服务器socket对象
	m_server = new CServerSocket;
	//创建套接字
	if (!m_server->Create(uPort))
	{
		TRACE("[Chat Server]m_server Create errorCode =%d", GetLastError());
		return;
	}
	else
	{
		TRACE("[Chat Server]m_server Create Success...");
	}
	//监听端口,等待连接
	if (!m_server->Listen())
	{
		TRACE("[Chat Server]m_server Listen errorCode=%d", GetLastError());
		return;
	}

	/*CString str;
	m_time = CTime::GetCurrentTime();
	str = m_time.Format("%X");
	str += _T("建立服务...");*/

	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("建立服务...");
	strShow = CutShowString(strInfo, strMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
}


void CMFCCHATServerDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowTextW(strTmpMsg);
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);
	//2.发送给客户端
	m_chat->Send(szSendBuf, SERVER_MAX_BUF, 0);
	//3.显示到列表框里
	CString strShow;
	CString strInfo = _T("服务端: ");
	//CString strMsg = _T("建立服务...");
	strShow = CutShowString(strInfo, strTmpMsg);

	m_list.AddString(strShow);
	UpdateData(FALSE);
	//清空编辑框
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}
