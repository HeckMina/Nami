#define VanCore_EXPORT	__declspec(dllexport)
#include "SystemEventManager.h"

namespace Van
{
	HRESULT		CALLBACK	SystemEventManager::SystemEventProcesser(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		return DefWindowProcA(hWnd,uMsg,wParam,lParam);
	}
}