#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#pragma warning(disable:4251)
#include "NT.h"
#include "glew.h"
#include "wglew.h"
#include "Glm/glm.hpp"
#include "Glm/gtc/matrix_transform.hpp"
#include "Glm/gtx/transform2.hpp"
using namespace std;


struct GLHardwareObject
{
	float				*m_fpVertex;
	float				*m_fpNormal;
	float				*m_fpUV;
};

struct	GLRenderMeta
{
	GLuint				m_uiVAO;
	GLRenderMeta		*m_pNext;
};