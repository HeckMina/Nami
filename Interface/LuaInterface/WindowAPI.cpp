#define InterfaceAPI __declspec(dllexport)
#include "WindowAPI.h"

namespace VanInterface
{
	int ShowRenderWindow(lua_State *L)
	{
		return 1;
	}

	luaL_Reg WindowAPI[]={
		{"ShowRenderWindow",ShowRenderWindow},
		{NULL,NULL}
	};
	int	RegisterWindowAPI(lua_State *L)
	{
		luaL_register(L,"Window",WindowAPI);
		return 1;
	}
}