#define VanCore_EXPORT  _declspec(dllexport)

#include "Utils.h"
#include "Log.h"

namespace Van
{
	string Utils::GetInstallationOf(const char *pName)
	{
		string strRet="";
		HKEY hKey;
		char szProductType[MAX_PATH];
		memset(szProductType,0,sizeof(szProductType));
		DWORD dwBufLen = MAX_PATH;
		LONG lRet;
		lRet = RegOpenKeyExA(HKEY_CLASSES_ROOT,
			pName,
			0,
			KEY_QUERY_VALUE,
			&hKey);

		if(lRet != ERROR_SUCCESS)
		{
			Van::Log::DebugLog.Print("RegOpenKeyExA fail!");
			return "";
		}

		lRet = RegQueryValueExA(hKey,
			"",
			NULL,
			NULL,   
			(LPBYTE)szProductType,
			&dwBufLen);
		if(lRet != ERROR_SUCCESS)
		{
			Van::Log::DebugLog.Print("RegQueryValueExA fail!");
			return "";
		}
		RegCloseKey(hKey);
		strRet=szProductType;
		return strRet;
	}
}