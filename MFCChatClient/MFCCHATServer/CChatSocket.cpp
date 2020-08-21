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
	//1.�������ݵ�szRecvBuf
	TRACE("[Chat Server]Server OnRecive...");
	CMFCCHATServerDlg* dlg = (CMFCCHATServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecveBuf[200] = { 0 };
	Receive(szRecveBuf, 200, 0);
	TRACE("[Chat Server]Server Receive=%s", szRecveBuf);
	//2.��ʾszRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecveBuf);
	CString strShow = _T("�ͻ���:");
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X");
	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
