#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif

namespace	Van
{
	class	VanCore_EXPORT	BuiltinGeometry
	{
	public:
	};
}