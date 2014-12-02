#define InterfaceAPI  _declspec(dllexport)
#include <lua.hpp>
#include <string>
using namespace std;
#include "NetWorkAPI.h"
#include "TCPSocket.h"
#include "Log.h"

namespace VanInterface
{
	int InitSocket(lua_State *L)
	{
		Van::TCPSocket *pSocket=(Van::TCPSocket*)lua_touserdata(L,1);
		Van::Log::DebugLog.Print("TCPSocket init by default settings");
		pSocket->Init(AF_INET,SOCK_STREAM,0);
		return 1;
	}

	int NewSocket(lua_State *L)
	{
		Van::TCPSocket *a = (Van::TCPSocket *)lua_newuserdata(L, sizeof(Van::TCPSocket));
		return 1;
	}

	int Connect(lua_State *L)
	{
		Van::TCPSocket *pSocket=(Van::TCPSocket*)lua_touserdata(L,1);
		string strIP=lua_tostring(L,2);
		unsigned short dwPort=(unsigned short)lua_tointeger(L,3);
		Van::Log::DebugLog.Print("TCPSocket connect to %s : %d",strIP.c_str(),dwPort);
		pSocket->Connect(strIP.c_str(),dwPort);
		return 1;
	}

	int Send(lua_State *L)
	{
		Van::TCPSocket *pSocket=(Van::TCPSocket*)lua_touserdata(L,1);
		pSocket->SendData((char*)lua_touserdata(L,2),lua_tointeger(L,3));
		return 1;
	}

	int Recv(lua_State *L)
	{
		Van::TCPSocket *pSocket=(Van::TCPSocket*)lua_touserdata(L,1);
		char	szBuffer[MAX_SOCKET_BUFFER_SIZE];
		memset(szBuffer,0,MAX_SOCKET_BUFFER_SIZE);
		pSocket->SyncRecvData(szBuffer);
		char	chCmd=0;
		char	chType=0;
		unsigned short dwLen=0;
		memcpy(&chCmd,szBuffer,sizeof(chCmd));
		memcpy(&chType,szBuffer+1,sizeof(chType));
		memcpy(&dwLen,szBuffer+2,2);
		lua_pushnumber(L,chCmd);
		lua_pushnumber(L,chType);
		lua_pushnumber(L,dwLen-1);
		lua_pushlstring(L,szBuffer+4,strlen(szBuffer+4)-1);
		return 4;
	}

	int Close(lua_State *L)
	{
		Van::TCPSocket *pSocket=(Van::TCPSocket*)lua_touserdata(L,1);
		return 1;
	}

	int		NewWWW(lua_State *L)
	{
		return 1;
	}

	int InitNetWorkEnvironment(lua_State *L)
	{
		Van::Log::DebugLog.Print("InitNetWorkEnvironment!");
		if(Van::TCPSocket::Init((byte)2,byte(2)))
		{
			Van::Log::DebugLog.Print("InitNetWorkEnvironment sucess!");
		}
		return 1;
	}

	int	GetIPOf(lua_State *L)
	{
		if (lua_gettop(L)<1)
		{
			Van::Log::DebugLog.Print("GetIPOf no arg %s:%d",__FILE__,__LINE__);
			return 1;
		}
		if (!lua_isstring(L,1))
		{
			Van::Log::DebugLog.Print("GetIPOf arg is not a string %s:%d",__FILE__,__LINE__);
			return 1;
		}
		lua_pushstring(L,Van::TCPSocket::GetTargetIPByName(lua_tostring(L,1)).c_str());
		return 1;
	}

	int Pack(lua_State*L)
	{
		char chCmd=lua_tonumber(L,1);
		char chType=lua_tonumber(L,2);
		unsigned short dwLen=lua_tonumber(L,3)+1;
		char *pack=(char*)lua_newuserdata(L,sizeof(char)*(4+dwLen));
		memset(pack,0,4+dwLen);
		memcpy(pack,&chCmd,sizeof(chCmd));
		memcpy(pack+1,&chType,sizeof(chType));
		memcpy(pack+2,&dwLen,sizeof(dwLen));
		if(dwLen!=1)
		{
			memcpy(pack+4,lua_tostring(L,4),dwLen-1);
		}
		pack[4+dwLen-1]='\n';
		lua_pushnumber(L,4+dwLen);
		return 2;
	}
	int		WaitForSeconds(lua_State *L)
	{
		Sleep(lua_tonumber(L,1));
		return 1;
	}
	int Unpack(lua_State *L)
	{
		Van::TCPSocket *pSocket=(Van::TCPSocket*)lua_touserdata(L,1);
		char buffer[10240];
		pSocket->SyncRecvData(buffer);
		lua_pushstring(L,buffer);
		return 1;
	}

	luaL_Reg SocketAPI[]={
		{"New",NewSocket},
		{"Init",InitSocket},
		{"Connect",Connect},
		{"Send",Send},
		{"Recv",Recv},
		{NULL,NULL}
	};

	luaL_Reg NetWorkAPI[]={
		{"Init",InitNetWorkEnvironment},
		{"GetIPOf",GetIPOf},
		{NULL,NULL}
	};

	luaL_Reg WWWAPI[]={
		{"New",NewWWW},
		{NULL,NULL}
	};

	int RegisterNetWorkAPI(lua_State *L)
	{
		luaL_register(L,"NetWork",NetWorkAPI);
		luaL_register(L,"Socket",SocketAPI);
		luaL_register(L,"WWW",WWWAPI);
		lua_register(L,"Pack",Pack);
		lua_register(L,"Unpack",Unpack);
		lua_register(L,"Sleep",WaitForSeconds);
		return 1;
	}
}