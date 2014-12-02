#define VanCore_EXPORT	__declspec(dllexport)
#include "SceneManager.h"

namespace Van
{
	SceneManager*	SceneManager::m_pStatic=NULL;
	SceneManager	*SceneManager::GetSingletonPtr()
	{
		if (NULL==m_pStatic)
		{
			m_pStatic=new SceneManager();
		}
		return m_pStatic;
	}

	SceneManager::SceneManager()
	{

	}

	SceneManager::~SceneManager()
	{

	}

	void	SceneManager::Destroy()
	{
		if (NULL!=m_pStatic)
		{
			delete m_pStatic;
		}
	}

	void	SceneManager::AddCamera(Camera *pCamera,unsigned int nCullMask)
	{
		map<unsigned int,map<unsigned int,Camera*> >::iterator iter=m_SceneCameras.find(nCullMask);
		if (iter!=m_SceneCameras.end())
		{
			if(iter->second.find(pCamera->m_uiID)==iter->second.end())
			{
				iter->second.insert(pair<unsigned int,Camera *>(pCamera->m_uiID,pCamera));
			}
		}
	}

	void	SceneManager::AddGameObject(GameObject *pGameObject,unsigned int nCullMask)
	{
		map<unsigned int,map<unsigned int,GameObject*> >::iterator iter=m_Objects.begin();
		if (iter!=m_Objects.end())
		{
			if(iter->second.find(pGameObject->m_uiID)==iter->second.end())
			{
				iter->second.insert(pair<unsigned int,GameObject *>(pGameObject->m_uiID,pGameObject));
			}
		}
	}
}