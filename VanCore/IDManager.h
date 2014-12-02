#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

#include <stack>
#include <iostream>

using namespace std;
namespace Van
{
	template class VanCore_EXPORT  std::allocator<unsigned int>;
	template class VanCore_EXPORT  std::stack<unsigned int>;

	class VanCore_EXPORT IDManager
	{
	public:
		static	IDManager	*GetSingletonPtr();
		void				Destroy();
		unsigned int		GetID();
		void				ReleaseID(unsigned int id);
		void				GetMoreIDs(unsigned int uiStartID,unsigned int uiCount);
	protected:
		IDManager();
		~IDManager();
	private:
		stack<unsigned int>			m_IDs;
		static	IDManager			*m_pStatic;
		unsigned int				m_uiMaxID;
	};
}