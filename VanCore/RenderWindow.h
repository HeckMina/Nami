#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

#include <Windows.h>
#include "GLRenderWindow.h"
#include "Camera.h"


namespace Van
{
	class GLRenderWindow;
	class Camera;
	class VanCore_EXPORT RenderWindow
	{
	protected:
		HWND						m_hWnd;
		HDC							m_hDC;
		unsigned int				m_uiWidth;
		unsigned int				m_uiHeight;
		GLRenderWindow				*m_pRenderWindow;
		bool						m_bQuit;
		float						m_szfFrustum[6][4];
		Camera						m_MainCamera;
	public:
		RenderWindow();
		bool						Init(void *pData);
		void						CreateScene();
		void						Enable();
		void						Disable();
		void						Show();
		void						Quit();
		void						FrustumCulling();
		void						SetTest(void*p);
	};
}