#define VanCore_EXPORT	__declspec(dllexport)
#include "TCPSocket.h"
#include "Log.h"

namespace Van
{
	bool	TCPSocket::m_bInit=false;
	bool TCPSocket::Init(byte chHVersion,byte chLVersion)
	{
		if(m_bInit)
		{
			return m_bInit;
		}
		WSADATA		wsaData;
		if(0==WSAStartup(MAKEWORD(chHVersion,chLVersion),&wsaData))
		{
			m_bInit=true;
		}
		else
		{
			Log::ErrLog.Print("WSAStartup fail!");
			return false;
		}
		if(HIBYTE(wsaData.wVersion)!=chHVersion||
			LOBYTE(wsaData.wVersion)!=chLVersion)
		{
			WSACleanup();
			Log::ErrLog.Print("WSAStartup fail!==>WSACleanup();");
			return false;
		}
		return true;
	}

	bool TCPSocket::CleanUp()
	{
		m_bInit=false;
		return m_bInit;
	}

	TCPSocket::TCPSocket():m_Socket(0),
		m_PeerAddr(0),m_BufferSize(MAX_SOCKET_BUFFER_SIZE)
	{
		
	}

	TCPSocket::~TCPSocket()
	{
		if(m_Socket!=INVALID_SOCKET)
		{
			closesocket(m_Socket);
		}
	}

	bool TCPSocket::Init(int nAF,int nType,int nProtocol)
	{
		m_Socket=socket(nAF,nType,nProtocol);
		if (INVALID_SOCKET==m_Socket)
		{
			return false;
		}
		return true;
	}

	string TCPSocket::GetTargetIPByName(const char *pName)
	{
		HOSTENT *hst=gethostbyname(pName);
		in_addr inaddr;
		memcpy((char*)(&inaddr),hst->h_addr_list[0],hst->h_length); 
		return inet_ntoa(inaddr);
	}

	bool TCPSocket::Connect(const char *pPeerIP,unsigned short dwPort)
	{
		SOCKADDR_IN		s_addr_in;
		s_addr_in.sin_family=AF_INET;
		s_addr_in.sin_port=htons(dwPort);
		s_addr_in.sin_addr.s_addr=inet_addr(pPeerIP);
		if (connect(m_Socket,(SOCKADDR*)&s_addr_in,sizeof(s_addr_in)))
		{
			Log::ErrLog.Print("TCPSocket::Connect fail %s %d",pPeerIP,dwPort);
			return false;
		}
		return true;
	}

	void TCPSocket::BlockingTheSocket()
	{
		unsigned long ulMode=0;
		ioctlsocket(m_Socket,FIONBIO,&ulMode);
	}

	void TCPSocket::UnblockingTheSocket()
	{
		unsigned long ulMode=1;
		ioctlsocket(m_Socket,FIONBIO,&ulMode);
	}

	bool TCPSocket::AsyncRecvData(void *pData)
	{
		return true;
	}

	bool TCPSocket::SyncRecvData(void *pData)
	{
		int nRecvSize=0;
		Log::DebugLog.Print("TCPSocket::SyncRecvData recv start");
		nRecvSize=recv(m_Socket,(char*)pData,MAX_SOCKET_BUFFER_SIZE,0);
		if (nRecvSize==0)
		{
			Log::ErrLog.Print("TCPSocket::SyncRecvData recv data size is 0 max buffer %d",MAX_SOCKET_BUFFER_SIZE);
			return false;
		}
	
		return true;
	}

	bool TCPSocket::SendData(const char *pData,int nLen)
	{
		int nSndSize=0;
		nSndSize=send(m_Socket,(const char*)pData,nLen,0);
		if (SOCKET_ERROR==nSndSize)
		{
			if (WSAGetLastError()==WSAEWOULDBLOCK)
			{
				Log::ErrLog.Print("TCPSocket::SendData WSAGetLastError == WSAEWOULDBLOCK");
				return false;
			}
		}
		if (0!=(nSndSize-nLen))
		{
			Log::ErrLog.Print("TCPSocket::SendData nSndSize != nLen");
			return false;
		}
		return true;
	}
}