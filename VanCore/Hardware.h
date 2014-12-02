#pragma once
#include <stdio.h>
#pragma warning(disable:4806)
#define CPUID(a,r0,r1,r2,r3) \
	__asm	mov eax,a \
	__asm	cpuid \
	__asm	mov r0,eax \
	__asm	mov r1,ebx \
	__asm	mov r2,ecx \
	__asm	mov r3,edx 

bool SupportSSE();
bool SupportSSE2();