#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT	__declspec(dllimport)
#endif

#include "VanCoreDependences.h"
#include "Camera.h"
#include "GameObject.h"

#include "Object.h"

List<Component>

namespace	Van
{
	class VanCore_EXPORT	SceneManager
	{
	public:
		static	SceneManager	*	GetSingletonPtr();
		void	Destroy();
		void	AddCamera(Camera *pCamera,unsigned int nCullMask);
		void	AddGameObject(GameObject *pGameObject,unsigned int nCullMask);
	protected:
		SceneManager();
		~SceneManager();
	private:
		map<unsigned int,map<unsigned int,Camera*> >		m_SceneCameras;
		map<string,unsigned int>							m_Name2CullMask;
		map<unsigned int,string>							m_CullMask2Name;
		map<unsigned int,map<unsigned int,GameObject*> >	m_Objects;
		static	SceneManager	*							m_pStatic;
	};
}