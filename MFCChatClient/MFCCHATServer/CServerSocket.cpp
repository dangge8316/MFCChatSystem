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
	dlg->m_chat = new CChatSocket;
	//��ʼ��������
	Accept(*(dlg->m_chat));
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("�ͻ������ӳɹ�...");
	dlg->m_list.AddString(str);
	dlg->m_list.UpdateData(FALSE);
	CAsyncSocket::OnAccept(nErrorCode);

}
