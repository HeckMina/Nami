#pragma once

namespace Van
{
	class  WWW
	{
	public:
		void	Download(char *szUrl,char *szBuffer);
		void	DownloadAndLocate(char *szUrl,char *szPath);
	};
}