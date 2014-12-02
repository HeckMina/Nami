#pragma once
#ifdef InterfaceAPI
#else
#define InterfaceAPI  _declspec(dllimport)  
#endif

namespace VanInterface
{
	extern "C"
	{
		int		NewSocket(lua_State *L);
		int		InitSocket(lua_State *L);
		int		Connect(lua_State* L);
		int		Send(lua_State* L);
		int		Recv(lua_State* L);
		int		Close(lua_State *L);
		int		Pack(lua_State*L);
		int		Unpack(lua_State *L);
		int		WaitForSeconds(lua_State *L);
		int		InitNetWorkEnvironment(lua_State *L);
		int		GetIPOf(lua_State *L);
		int		NewWWW(lua_State *L);
	}
	int		RegisterNetWorkAPI(lua_State *L);
}