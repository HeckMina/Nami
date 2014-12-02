#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif


namespace Van
{
	enum TextureType
	{
		Default_RGBA
	};
	class VanCore_EXPORT Texture
	{
	public:
		TextureType		m_Type;
	};
}