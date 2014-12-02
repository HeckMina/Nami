#include <Windows.h>
#include <iostream>
#include <process.h>
#include <string>
using namespace std;
#include "VersionManager.h"
#define WIN32_LEAN_AND_MEAN

INT WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	Van::VersionManager versionMgr;
	versionMgr.TryToUpdate();
	ShellExecute(NULL,"open",".\\AOI.exe",NULL,NULL,SW_SHOWNORMAL);
	return 0;
}