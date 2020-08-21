#include "pch.h"
#include "CMySocket.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"

CMySocket::CMySocket()
{

}

CMySocket::~CMySocket()
{

}

void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("[Chat Client]OnConnect...");
	//��ȡ������
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("���ӷ������ɹ�:");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("[Chat Client]OnReceive...");
}
