#include "pch.h"
#include "CServerSocket.h"
#include "MFCCHATServer.h"
#include "MFCCHATServerDlg.h"
#include "ChatSocket.h"

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
	dlg->m_chat = new ChatSocket;
	//��ʼ��������
	Accept(*(dlg->m_chat));

	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("�ͻ������ӳɹ�...");
	strShow = dlg->CutShowString(strMsg);

	dlg->m_list.AddString(strShow);
	dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);

}
