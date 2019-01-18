#pragma once

//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"

#include <string>
// Файлы заголовков Windows:
#include <windows.h>

using namespace std;
//using namespace cv;

namespace
{
	UINT GetCurrentCodePage()
	{
		TCHAR codePage[6];
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_IDEFAULTANSICODEPAGE,
			(LPTSTR)&codePage, 6);
		return _wtoi(codePage);
	}

	//-------------------------------------------------------------------------

	UINT g_currentCodePage = GetCurrentCodePage();
}

namespace im
{
	class StringHelper
	{
	public:

		static string ToString(const wstring & path)
		{
			std::string result(path.size(), 0);
			WideCharToMultiByte(g_currentCodePage, WC_COMPOSITECHECK,
					path.c_str(), path.size() + 1, (char*)result.c_str(), result.size() + 1, NULL, NULL);

			return result;
		}

		static string ToString(const wchar_t * path)
		{
			//const size_t size = std::wcslen(path);
			const size_t size = std::char_traits<wchar_t>::length(path);
			std::string result(size, 0);
			WideCharToMultiByte(g_currentCodePage, WC_COMPOSITECHECK,
					path, size, (char*)result.c_str(), result.size(), NULL, NULL);

			return result;
		}

		static wstring ToWstring(const char * inputChar)
		{
			const size_t size = std::strlen(inputChar);
			std::wstring result(size, 0);
			MultiByteToWideChar(g_currentCodePage, MB_PRECOMPOSED,
					inputChar, size, (wchar_t*)result.c_str(), result.size());

			return result;
		}

		static wstring ToWstring(const wchar_t * inputChar)
		{
			//const size_t size = std::wcslen(inputChar);
			std::wstring result(inputChar);

			return result;
		}

	};
}
