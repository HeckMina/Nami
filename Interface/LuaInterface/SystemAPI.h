#pragma once
#ifdef InterfaceAPI
#else
#define InterfaceAPI  _declspec(dllimport)  
#endif

namespace VanInterface
{
	extern "C"
	{
		int RuntimePlatform(lua_State *L);
		int AddEnviroment(lua_State *L);
		int BeginConsoleInputThread(lua_State *L);
		int GetInstallPathOf(lua_State *L);
		//internal version manager update the Van.exe
		int TryToUpdate(lua_State*L);
	}
	int	RegisterSystemAPI(lua_State *L);
}