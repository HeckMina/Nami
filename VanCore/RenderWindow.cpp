#define VanCore_EXPORT  _declspec(dllexport)
#include "RenderWindow.h"
#include "SystemEventManager.h"
#include "Log.h"
#include "GameObject.h"
#include "IDManager.h"
#include "SceneManager.h"
#include "Timer.h"

Van::GLDrawCall	drawcall;
namespace	Van
{
	RenderWindow::RenderWindow():m_pRenderWindow(NULL),
		m_uiHeight(800),m_uiWidth(600),m_bQuit(false)
	{
	
	}

	bool	RenderWindow::Init(void *pData)
	{
		bool	bRet=false;
		WNDCLASSEXA		wndclass;
		wndclass.cbWndExtra=0;
		wndclass.cbClsExtra=0;
		wndclass.cbSize=sizeof(WNDCLASSEXA);
		wndclass.hbrBackground=NULL;
		wndclass.hCursor=LoadCursorA(NULL,MAKEINTRESOURCEA(IDC_ARROW));
		wndclass.hInstance=*(HINSTANCE*)pData;
		wndclass.style=CS_VREDRAW|CS_HREDRAW;
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName="vCoreMainWindow";
		if (NULL==wndclass.hInstance)
		{
			Van::Log::ErrLog.Print("hinstance is null");
		}
		wndclass.hIcon=(HICON)LoadImageA(wndclass.hInstance,"../Logo.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
		wndclass.hIconSm=(HICON)LoadImageA(wndclass.hInstance,"../Logo.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
		wndclass.lpfnWndProc=SystemEventManager::SystemEventProcesser;
		if (!RegisterClassExA(&wndclass))
		{
			Van::Log::ErrLog.Print("RegisterClassExA fail!");
			return false;
		}
		Van::Log::DebugLog.Print("Register Render Window Sucess!");
		m_hWnd=CreateWindowExA((DWORD)NULL,
			"vCoreMainWindow",
			"Van Core Render Window",
			WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|!WS_MAXIMIZEBOX,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			*(HINSTANCE*)pData,
			NULL);
		if(NULL==m_hWnd)
		{
			Log::ErrLog.Print("create Window fail!");
			return false;
		}
		m_hDC=GetDC(m_hWnd);
		DWORD dwCurrentStyle = GetWindowLongA(m_hWnd, GWL_STYLE);
		SetWindowLong(m_hWnd, GWL_STYLE, dwCurrentStyle &~WS_SYSMENU);
		m_pRenderWindow=new GLRenderWindow();
		RECT	rect;
		GetWindowRect(m_hWnd,&rect);
		m_uiWidth=rect.right-rect.left;
		m_uiHeight=rect.bottom-rect.top;
		if(m_pRenderWindow->CreateRendererViaDevice(m_hWnd,m_hDC,m_uiWidth,m_uiHeight))
		{
			bRet=true;
			CreateScene();
		}
		return bRet;
	}
	GameObject	go;
	void	RenderWindow::CreateScene()
	{
		m_MainCamera.m_CullMask=1;
		m_MainCamera.m_ViewMatrix=glm::lookAt(glm::vec3(0,0,5.0),glm::vec3(0,0,0),glm::vec3(0,1,0));
		m_MainCamera.m_uiID=IDManager::GetSingletonPtr()->GetID();
		SceneManager::GetSingletonPtr()->AddCamera(&m_MainCamera,m_MainCamera.m_CullMask);
		//go.m_Mesh.InitFromFBXFile("media/model/Worm.fbx");
		go.m_Mesh.Init();
		go.m_uiID=IDManager::GetSingletonPtr()->GetID();
		go.m_Mat.Init();
		go.m_Mat.m_GLShader.AddAttribute("projectionMatrix",glm::perspective(60.0f,(float)m_uiWidth/(float)m_uiHeight,0.1f,100.0f));
		go.m_Mat.m_GLShader.AddAttribute("modelMatrix",glm::mat4(2.0));
		go.m_Mat.m_GLShader.AddAttribute("viewMatrix",glm::lookAt(glm::vec3(0,0,5.0),glm::vec3(0,0,0),glm::vec3(0,1,0)));
		go.m_Mat.m_GLShader.AddAttribute("rotateMatrix",glm::rotate(glm::mat4(1.0f),0.0f,glm::vec3(0.0f,0.0f,1.0f)));
		SceneManager::GetSingletonPtr()->AddGameObject(&go,go.m_CullMask);
	}

	void	RenderWindow::Show()
	{
		ShowWindow(m_hWnd,SW_HIDE);
		UpdateWindow(m_hWnd);
		MSG		msg;
		Timer	t;
		t.Init();
		float fTimeSinceLastFrame=0.0f;
		while(!m_bQuit)
		{
			if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if(msg.message==WM_QUIT)
				{
					cout<<"quit message "<<endl;
					break;
				}
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//frustun culling then
				fTimeSinceLastFrame+=t.GetElapsedTime(true);
				if(fTimeSinceLastFrame>0.033f)
				{
					fTimeSinceLastFrame=0.0f;
					FrustumCulling();
					m_pRenderWindow->RenderOneFrame();
					SwapBuffers(m_hDC);
				}
				else
				{
					Sleep((0.033f-fTimeSinceLastFrame)*1000);
				}
			}
		}
	}

	void	RenderWindow::SetTest(void*p)
	{
		//memcpy(m_pRenderWindow->m_pData,p,sizeof(int));
	}

	void	RenderWindow::FrustumCulling()
	{
		go.m_Mat.MakeAsCurrentMat();
		drawcall.m_uiVAO=go.m_Mesh.m_nHardwareID;
		drawcall.m_nCount=382;
		m_pRenderWindow->AddOneRenderMeta(drawcall);
	}

	void	RenderWindow::Enable()
	{
		ShowWindow(m_hWnd,SW_SHOW);
	}

	void	RenderWindow::Disable()
	{
		ShowWindow(m_hWnd,SW_HIDE);
	}

	void	RenderWindow::Quit()
	{
		//clean the renderer
		//then do something else
		m_bQuit=true;
	}
}