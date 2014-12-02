#pragma once
#ifdef InterfaceAPI
#else
#define InterfaceAPI  _declspec(dllimport)  
#endif

namespace Van
{
	class InterfaceAPI InterfaceManager
	{
	public:
		static void Init();
		static void RunScript(const char *filename);
		static void ConsoleInputThread(void *pData);
	};
}