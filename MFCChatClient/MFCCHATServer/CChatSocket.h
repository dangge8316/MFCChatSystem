#pragma once
#include <afxsock.h>
#include "MFCCHATServer.h"
#include "MFCCHATServerDlg.h"

class CChatSocket :
    public CAsyncSocket
{
public:
    CChatSocket();
    virtual ~CChatSocket();
    virtual void OnReceive(int nErrorCode);
};

