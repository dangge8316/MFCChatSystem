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
	/*CString str;
	dlg->m_time = CTime::GetCurrentTime();
	str = dlg->m_time.Format("%X");
	str += _T("���ӷ������ɹ�:");*/
	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("���ӷ������ɹ�:");
	strShow = dlg->CutShowString(strMsg);
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("[Chat Client]OnReceive...");
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecveBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecveBuf, SEND_MAX_BUF, 0);
	TRACE("[Chat Client]Client Receive=%s", szRecveBuf);
	//2.��ʾszRecvBuf���б��
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecveBuf);

	CString strShow;
	CString strInfo = _T("�����: ");
	strShow = dlg->CutShowString(strRecvMsg);

	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
