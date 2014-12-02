#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include "VanCoreDependences.h"
namespace Van
{
	class	VanCore_EXPORT	Input
	{
	public:

	};
}