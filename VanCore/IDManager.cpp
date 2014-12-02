#define VanCore_EXPORT  _declspec(dllexport)
#include "IDManager.h"

namespace Van
{
	IDManager	*IDManager::m_pStatic=NULL;
	IDManager::IDManager()
	{
		m_uiMaxID=100;
		GetMoreIDs(1,100);
	}

	IDManager::~IDManager()
	{

	}

	IDManager	*IDManager::GetSingletonPtr()
	{
		if (NULL==m_pStatic)
		{
			m_pStatic=new IDManager();
		}
		return m_pStatic;
	}

	void	IDManager::Destroy()
	{
		if(NULL!=m_pStatic)
		{
			delete m_pStatic;
		}
	}

	unsigned int	IDManager::GetID()
	{
		if (!m_IDs.empty())
		{
			unsigned int uiTemp=m_IDs.top();
			m_IDs.pop();
			if (m_IDs.empty())
			{
				GetMoreIDs(m_uiMaxID,100);
			}
			return uiTemp;
		}
		return -1;
	}

	void	IDManager::ReleaseID(unsigned int id)
	{
		m_IDs.push(id);
	}

	void	IDManager::GetMoreIDs(unsigned int uiStartID,unsigned int uiCount)
	{
		m_uiMaxID=uiStartID+uiCount;
		for (unsigned int i=uiStartID;i<m_uiMaxID;i++)
		{
			m_IDs.push(i);
		}
	}
}