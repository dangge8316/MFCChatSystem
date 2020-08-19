#include "pch.h"
#include "CServerSocket.h"
#include "MFCCHATServer.h"
#include "MFCCHATServerDlg.h"

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}

void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("[Chat Server]Onaccept...");
	CMFCCHATServerDlg* dlg = (CMFCCHATServerDlg*)AfxGetApp()->GetMainWnd();
}
