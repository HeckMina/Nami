#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include<windows.h>
namespace Van
{
	class	VanCore_EXPORT	SystemEventManager
	{
	public:
		static HRESULT CALLBACK	SystemEventProcesser(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	};
}