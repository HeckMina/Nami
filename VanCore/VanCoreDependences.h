#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include "NT.h"
#include "Glm/glm.hpp"
#include "Glm/gtc/matrix_transform.hpp"
#include "Glm/gtx/transform2.hpp"
using namespace std;
#pragma comment(lib,"Wininet.lib")

#pragma warning(disable:4251)
#pragma warning(disable:4996)

namespace	Van
{
#ifdef	WIN32
typedef HWND	HPLATFORMWINDOW;
#elif
#endif
	enum	VanCore_EXPORT	CullMask
	{
		CM_Default=0x0001,
		CM_Terrain=0x0002,
		CM_Particle=0x0003
	};

	enum	VanCore_EXPORT	ObjectType
	{
		OT_Transform,
		OT_GameObject,
		OT_Material,
		OT_ColliderBox,
		OT_MeshRenderer,
		OT_Camera
	};

	template<typename T>
	class	ObjectBase
	{
		typedef		T	ObjectType;
	};
	//template<typename T>
	class	VanCore_EXPORT	Object
	{
	public:
		unsigned	int		m_iID;
		char				m_szName[64];
		ObjectType			m_Type;
		//typedef		T		ObjectType;
	};

	struct	VanCore_EXPORT	RenderQueue
	{

	};
}