#include "Hardware.h"

bool SupportSSE()
{
	unsigned int reax=0,rebx=0,recx=0,redx=0;
	CPUID(1,reax,rebx,recx,redx);
	if (0x02000000&redx!=0)
	{
		return true;
	}
	return false;
}

bool SupportSSE2()
{
	unsigned int reax=0,rebx=0,recx=0,redx=0;
	CPUID(1,reax,rebx,recx,redx);
	if (0x04000000&redx!=0)
	{
		return true;
	}
	return false;
}