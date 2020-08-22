#include "pch.h"
#include "ChatSocket.h"

ChatSocket::ChatSocket()
{
}

ChatSocket::~ChatSocket()
{
}

void ChatSocket::OnReceive(int nErrorCode)
{
	//1.�������ݵ�szRecvBuf
	TRACE("[Chat Server]Server OnRecive...");
	CMFCCHATServerDlg* dlg = (CMFCCHATServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecveBuf[SERVER_MAX_BUF] = { 0 };
	Receive(szRecveBuf, SERVER_MAX_BUF, 0);
	TRACE("[Chat Server]Server Receive=%s", szRecveBuf);
	//2.��ʾszRecvBuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecveBuf);

	CString strShow;
	CString strInfo = _T("�ͻ���: ");
	//CString strMsg = _T("");
	strShow = dlg->CutShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}