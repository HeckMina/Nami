#define InterfaceAPI  _declspec(dllexport)
#include "VanCore.h"
#include "Interface.h"
#include "lua.hpp"
#include "Log.h"
#include "SystemAPI.h"
#include "NetWorkAPI.h"
#include "FileSystemAPI.h"
#pragma comment(lib, "lua5.1.lib")

#pragma warning(disable:4996)
lua_State* L;
extern "C"
{
	int test(lua_State *L)
	{
		lua_tostring(L,1);
		return 1;
	}
}



void RegisterLuaAPI()
{
	VanInterface::RegisterFileSystemAPI(L);
	VanInterface::RegisterSystemAPI(L);
	VanInterface::RegisterNetWorkAPI(L);
	lua_register(L, "test", test);
}

namespace Van
{
	void	InterfaceManager::ConsoleInputThread(void *pData)
	{
		string	strPath="AOI/";
		string	tempStr="";
		char	cg[256];
		while(tempStr!=string("q"))
		{
			memset(cg,0,sizeof(cg));
			cin.getline(cg,256);
			tempStr=cg;
			Log::DebugLog.Print("command is :%s",tempStr.c_str());
			if(memcmp(tempStr.c_str(),"show window",strlen("show window"))==0)
			{
				Application::GetInstancePtr()->GetRenderWindow()->Enable();
			}
			else if (memcmp(tempStr.c_str(),"hide window",strlen("hide window"))==0)
			{
				Application::GetInstancePtr()->GetRenderWindow()->Disable();
			}
			else
			{
				luaL_dofile(L,(strPath+tempStr).c_str());
			}
		}
		cout<<"bye"<<endl;
		Application::GetInstancePtr()->Quit();
	}

	void	InterfaceManager::Init()
	{
		L = lua_open();
		luaL_openlibs(L);
		RegisterLuaAPI();
		Van::Log::DebugLog.Print("lua init complete");
		luaL_dofile(L,"AOI/main");
		lua_close(L);
	}

	void InterfaceManager::RunScript(const char *filename)
	{
		luaL_dofile(L,filename);
	}
}