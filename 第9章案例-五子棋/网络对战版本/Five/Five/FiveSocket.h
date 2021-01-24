// CFiveSocket ∂®“Â
#pragma once
class CFiveSocket : public CAsyncSocket
{

public:
	CFiveSocket();
	virtual ~CFiveSocket();

protected:
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


