#pragma once
#ifdef InterfaceAPI
#else
#define InterfaceAPI  _declspec(dllimport)  
#endif

#include "lua.hpp"

namespace VanInterface
{
	extern "C"
	{
		int ShowRenderWindow(lua_State *L);
	}
	int	RegisterWindowAPI(lua_State *L);
}