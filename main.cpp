#include "VanCore.h"
#include "Interface.h"
#include "TCPSocket.h"
#include "Log.h"
#include <io.h>
#include <stdlib.h>


void	LuaScriptProcess(void *pData)
{
	Van::Log::DebugLog.Print("lua thread hajimeta");
	Van::InterfaceManager::Init();
}


INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	Van::Log::DebugLog.SetLog("DebugLog",strlen("DebugLog"),1,1);
	Van::Log::ErrLog.SetLog("ErrLog",strlen("ErrLog"),1,1);
	Van::Log::DebugLog.Print("Welcome to Namespace Van!Debug Log init complete...");
	Van::Log::ErrLog.Print("Welcome to Namespace Van!ErrLog init complete...");
	Van::VersionManager versionMgr;
	versionMgr.TryToUpdate();
	_beginthread(LuaScriptProcess,0,NULL);
	Van::Application::GetInstancePtr()->GetRenderWindow()->Show();
	return 0;
}