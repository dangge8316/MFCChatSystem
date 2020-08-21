#include "pch.h"
#include "CChatSocket.h"

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	//1.接收数据到szRecvBuf
	TRACE("[Chat Server]Server OnRecive...");
	CMFCCHATServerDlg* dlg = (CMFCCHATServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecveBuf[200] = { 0 };
	Receive(szRecveBuf, 200, 0);
	TRACE("[Chat Server]Server Receive=%s", szRecveBuf);
	//2.显示szRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecveBuf);
	CString strShow = _T("客户端:");
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
