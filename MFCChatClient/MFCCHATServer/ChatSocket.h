#pragma once
#include <afxsock.h>
#include "MFCCHATServer.h"
#include "MFCCHATServerDlg.h"

class ChatSocket :
    public CAsyncSocket
{
public:
    ChatSocket();
    virtual ~ChatSocket();
    virtual void OnReceive(int nEerrorCode);
};

