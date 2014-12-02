#pragma once
#ifdef InterfaceAPI
#else
#define InterfaceAPI  _declspec(dllimport)  
#endif

namespace VanInterface
{
	extern "C"
	{
		//file
		int GetFileSize(lua_State*L);
		//dir
		int ExistDir(lua_State*L);
		int GetAllFilesInThisDir(lua_State*L);
	}
	
	int RegisterFileSystemAPI(lua_State*L);
}