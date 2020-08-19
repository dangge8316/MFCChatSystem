#pragma once
#include <afxsock.h>

class CServerSocket :
    public CAsyncSocket
{
public:
    CServerSocket();
    virtual ~CServerSocket();
    virtual void OnAccept(int nErrorCode);

};

