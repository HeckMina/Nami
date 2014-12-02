#define InterfaceAPI  _declspec(dllexport)
#include <lua.hpp>
#include <list>
#include <string>
using namespace std;
#include "Log.h"
#include "FileSystemAPI.h"
#include "Directory.h"
#pragma  warning(disable:4996)

namespace VanInterface
{
	int		ExistDir(lua_State*L)
	{
		int n = lua_gettop(L);
		if (n<1)
		{
			Van::Log::ErrLog.Print("GetAllFilesInThisDir fail,while no input arg");
			lua_pushnil(L);
			return 1;
		}
		if (!lua_isstring(L,1))
		{
			Van::Log::ErrLog.Print("GetAllFilesInThisDir fail,input path is not a string");
			lua_pushnil(L);
			return 1;
		}
		lua_pushboolean(L,Van::Directory::Exsit(lua_tostring(L,1)));
		return 1;
	}
	int		GetFileSize(lua_State *L)
	{
		return 1;
	}

	int		GetAllFilesInThisDir(lua_State*L)
	{
		int n = lua_gettop(L);
		if (n<1)
		{
			Van::Log::ErrLog.Print("GetAllFilesInThisDir fail,while no input arg");
			lua_pushnil(L);
			return 1;
		}
		if (!lua_isstring(L,1))
		{
			Van::Log::ErrLog.Print("GetAllFilesInThisDir fail,input path is not a string");
			lua_pushnil(L);
			return 1;
		}
		string strDir=lua_tostring(L,1);
		list<string> lFiles=Van::Directory::GetAllFilesInThisDirectory(strDir);
		if (!lFiles.empty())
		{
			lua_newtable(L);
			int		nIndex=1;
			for (list<string>::iterator iter=lFiles.begin();iter!=lFiles.end();iter++)
			{
				lua_pushnumber(L,nIndex++);
				lua_pushstring(L,(*iter).c_str());
				lua_settable(L,-3);
			}
		}
		else
		{
			lua_pushnil(L);
		}
		return 1;
	}

	luaL_Reg	FileSystemAPI[]=
	{
		{"Size",GetFileSize},
		{NULL,NULL}
	};
	luaL_Reg	DirAPI[]=
	{
		{"Exist",ExistDir},
		{"GetAllFiles",GetAllFilesInThisDir},
		{NULL,NULL}
	};

	int RegisterFileSystemAPI(lua_State*L)
	{
		luaL_register(L,"File",FileSystemAPI);
		luaL_register(L,"Dir",DirAPI);
		return 1;
	}
}