#define InterfaceAPI  _declspec(dllexport)
#include "VanCore.h"
#include <lua.hpp>
#include <string>
#include<iostream>
#include "Utils.h"
#include "SystemAPI.h"
#include "Application.h"
#include "Log.h"

namespace VanInterface
{
	int RuntimePlatform(lua_State *L)
	{
		string strPlatform=Van::Application::GetInstancePtr()->GetRuntimePlatform();
		lua_pushfstring(L,strPlatform.c_str(),strPlatform.size());
		return 1;
	}

	int AddEnviroment(lua_State *L)
	{
		if (!lua_isstring(L,1))
		{
			return 1;
		}
		Van::Application::GetInstancePtr()->AddEnviroment(lua_tostring(L,1));
		return 1;
	}

	int BeginConsoleInputThread(lua_State *L)
	{
		Van::Log::DebugLog.Print("BeginConsoleInputThread");
		//_beginthread(ConsoleInputThread,0,NULL);
		return 1;
	}

	int GetInstallPathOf(lua_State *L)
	{
		lua_pushstring(L,Van::Utils::GetInstallationOf(lua_tostring(L,1)).c_str());
		return 1;
	}

	int TryToUpdate(lua_State*L)
	{
		Van::VersionManager versionMgr;
		versionMgr.TryToUpdate();
		return 1;
	}
	

	luaL_Reg SystemAPI[]={
		{"RuntimePlatform",RuntimePlatform},
		{"BeginConsoleInputThread",BeginConsoleInputThread},
		{"GetInstallPathOf",GetInstallPathOf},
		{"AddEnviroment",AddEnviroment},
		{NULL,NULL}
	};

	luaL_Reg TimerAPI[]={
		{NULL,NULL}
	};

	luaL_Reg VersionManagerAPI[]={
		{"TryToUpdate",TryToUpdate},
		{NULL,NULL}
	};

	int RegisterSystemAPI(lua_State *L)
	{
		luaL_register(L,"System",SystemAPI);
		luaL_register(L,"VersionManager",VersionManagerAPI);
		luaL_register(L,"Timer",TimerAPI);
		return 1;
	}
}