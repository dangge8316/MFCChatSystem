#pragma once
#include <afxsock.h>

class CMySocket :
    public CAsyncSocket
{
public:
    CMySocket();
    virtual ~CMySocket();
    void virtual OnConnect(int nErrorCode);
    void virtual OnReceive(int nErrorCode);
};

