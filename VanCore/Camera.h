#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT	__declspec(dllimport)
#endif

#include "Glm/glm.hpp"
#include "Glm/gtc/matrix_transform.hpp"
#include "Glm/gtx/transform2.hpp"

namespace Van
{
	class	VanCore_EXPORT	Camera
	{
	public:
		unsigned int	m_CullMask;
		glm::mat4		m_ViewMatrix;
		unsigned int	m_uiID;
	public:
		Camera();
		~Camera();
	};
}