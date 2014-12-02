#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

#include <Windows.h>
#include<winsock.h>
#include <string>
using namespace std;

namespace Van
{
#define MAX_SOCKET_BUFFER_SIZE	10240
	class VanCore_EXPORT TCPSocket
	{
	public:
		static bool			m_bInit;
		static bool			Init(byte chHVersion=2,byte chLVersion=2);
		static bool			CleanUp();
		static string		GetTargetIPByName(const char *pName);
	protected:
		SOCKET			m_Socket;
		unsigned long	m_PeerAddr;
		int				m_BufferSize;
	public:
		TCPSocket();
		~TCPSocket();
		bool		Init(int nAF=AF_INET,int nType=SOCK_STREAM,int nProtocol=0);
		bool		Connect(const char *pPeerIP,unsigned short dwPort=9527);
		
		void		BlockingTheSocket();
		void		UnblockingTheSocket();
		//this method is not implemented yet
		bool		AsyncRecvData(void *pData);
		bool		SyncRecvData(void *pData);
		bool		SendData(const char *pData,int nLen);
	};
}