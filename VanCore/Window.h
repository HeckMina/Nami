#pragma once
#ifdef VanCore_EXPORT
#else
#define VanCore_EXPORT  _declspec(dllimport)  
#endif
#include <Windows.h>

int CreateWindow(WCHAR *Title,int nWith=CW_USEDEFAULT,int nHeight=CW_USEDEFAULT,WCHAR *WindowClassName);