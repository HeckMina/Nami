#pragma once
#ifdef VanCore_EXPORT
#elif
#define VanCore_EXPORT	__declspec(dllimport)
#endif

#include "Mesh.h"
#include "Material.h"

namespace	Van
{
	//struct	VanCore_EXPORT	Transform:public Object
	//{
	//	Vector3		m_vec3LocalPosition;
	//	Vector3		m_vec3LocalDirection;
	//	Vector3		m_vec3LocalScale;
	//};
	class	VanCore_EXPORT	GameObject
	{
	public:
		Mesh			m_Mesh;
		Material		m_Mat;
		unsigned int	m_uiID;
		unsigned int	m_CullMask;
	};
}
