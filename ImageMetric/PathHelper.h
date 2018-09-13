#pragma once

#include <string>
#include <vector>

#include "StringHelper.h"

#include <Shlwapi.h>  //PathFileExists
#pragma comment(lib,"Shlwapi.lib")

using namespace std;

#define DELIMETER TEXT('\\')
#define LONG_PATH_ID  L"\\\\?\\"

namespace im
{
	class PathHelper
	{
	public:
		PathHelper(void);
		~PathHelper(void);

		//обрезает конечный слеш пр€мой или обратный в пути к папке
		static void PathHelper::TrimSlash(wstring & path)
		{
			if ((path[path.length()-1] == '/') || (path[path.length()-1] == '\\'))
				path.resize(path.size() - 1);

			string::size_type pos = path.rfind('\"');
			if ((pos != string::npos) && (pos != 0)) //если найдена точка
			{
				path.resize(pos);
			}
		}

		static void GetFilesInFolderRecur(const wstring & dirPath, vector<wstring> & filesList)
		{
			//const size_t terminal_lenth = 79;
			WIN32_FIND_DATAW stFD = {0};  
			wstring strDirName;  
			strDirName = dirPath;  

			if (strDirName[strDirName.length() - 1] == L'"')
				strDirName.erase(strDirName.length() - 1);
				//strDirName.pop_back();

			if ((strDirName[strDirName.length()-1] != L'/') && (strDirName[strDirName.length()-1] != '\\'))
				strDirName.push_back(L'\\');

			strDirName = GetPathForSearchInAPI(strDirName, true);

			wstring strFindName = strDirName + L"*";  
			HANDLE hFile = FindFirstFileW(strFindName.c_str(), &stFD);  
			BOOL bExist = FindNextFileW(hFile, &stFD);  

			for (;bExist;)  
			{  
				//cout.end;
				//cout << "\r" << strDirName.substr(strDirName.length() > terminal_lenth ? strDirName.length() - terminal_lenth : 0);

				wstring strTmpName = strDirName + stFD.cFileName;  
				if (strDirName + L"." == strTmpName || strDirName + L".." == strTmpName)
				{  
					bExist = FindNextFileW(hFile, &stFD);  
					continue;  
				}  
				if (PathIsDirectoryW(strTmpName.c_str()))  
				{  
					strTmpName += L"\\";  
					GetFilesInFolderRecur(strTmpName, filesList);  
					bExist = FindNextFileW(hFile, &stFD);  
					continue;  
				}  
				std::wstring strSubImg = strDirName + stFD.cFileName; 
				wstring clearedPath = ClearPath(strSubImg);
				filesList.push_back(clearedPath);
				//cout << " (" << filesList.size() << ")";
				bExist = FindNextFileW(hFile, &stFD);  
			}  
			// m_nImgNumber = m_szImgs.size();  
			//return m_nImgNumber;   
			FindClose(hFile);
		}

		static void GetFilesInFolder(const wstring& dirPath, vector<wstring> &fileList)
		{
			HANDLE handle;
			WIN32_FIND_DATAW fileData;
			wstring strDirName = dirPath;  

			if (strDirName[strDirName.length() - 1] == L'"')
				strDirName.erase(strDirName.length() - 1);

			if ((strDirName[strDirName.length()-1] != L'/') && (strDirName[strDirName.length()-1] != '\\'))
				strDirName.push_back(L'\\');

			strDirName = GetPathForSearchInAPI(strDirName, true);

			wstring strFindName = strDirName + L"*";  

			if ((handle = FindFirstFileW(strFindName.c_str(), &fileData)) == INVALID_HANDLE_VALUE)
			{
				return; 
			}
			BOOL bExist;
			do 
			{
				const wstring tmpPath = strDirName + fileData.cFileName;

				if (tmpPath == strDirName + L"." || tmpPath == strDirName + L"..")  
				{  
					bExist = FindNextFileW(handle, &fileData);
					continue;  
				}
				if (PathIsDirectoryW(tmpPath.c_str()))  
				{  
					bExist = FindNextFileW(handle, &fileData);
					continue;  
				}  

				//const wstring full_file_name = strDirName + L"/" + tmpPath;
				wstring clearedPath = ClearPath(tmpPath);
				fileList.push_back(clearedPath);
				bExist = FindNextFileW(handle, &fileData);
			} 
			while (bExist);
			FindClose(handle);
		}

		//static inline void ToLower(wstring& ext);
		static void ToLower(wstring& ext)
		{
			for (size_t i = 0; i < ext.length(); ++i)
			{
				ext[i] = tolower(ext[i]);
			}
		}

		//static inline bool ReplaceExt(wstring& rename, const wstring& newExt);
		static bool ReplaceExt(wstring & rename, const wstring& newExt) 
		{
			string::size_type pos = rename.rfind('.', rename.length( ));

			if (pos != string::npos) //если найдена точка
			{
				rename.replace(pos, rename.length(), newExt);
				return true;
			}
			return false;
		}

		static wstring GetApplicationDirectory()
		{
			wstring appPath = GetApplicationPath();
			return GetFileDirectory(appPath.c_str(), appPath.size());
		}

		static wstring GetApplicationPath()
		{
			wchar_t path[MAX_PATH];
			DWORD result = GetModuleFileName(NULL, path, MAX_PATH);
			if(result == 0)
				return wstring();
	//		if(result == MAX_PATH)
	//		{
	//#ifdef UNICODE
	//			TChar *buffer = new TChar[MAX_PATH_EX];
	//			TString str;
	//			result = GetModuleFileName(NULL, buffer, MAX_PATH_EX);
	//			if(result > 0 && result < MAX_PATH_EX)
	//				str = buffer;
	//			delete [] buffer;
	//			return str;
	//#else
	//			return TString();
	//#endif
	//		}
			return wstring(path);  
		}

		static wstring GetFileDirectory(const wchar_t* path, size_t size)
		{
			ptrdiff_t i = size - 1;
			while(i >= 0 && path[i] != DELIMETER) i--;
			if(i < 0)
				return wstring();
			else
				return wstring(path, i);
		}

		//force в люблм случае добавить префик дл€ длинного пути
		//https://msdn.microsoft.com/ru-ru/library/windows/desktop/aa365247(v=vs.85).aspx#maxpath
		static wstring GetPathForSearchInAPI(const wstring & sourcePath, bool force = false)
		{
			size_t sourceLen = sourcePath.length();

			if (sourcePath.substr(0, 4) == LONG_PATH_ID)
				return sourcePath;
			if(!force && sourceLen <= (MAX_PATH - 1)) //If the path is longer in the range of MAX_PATH return it directly
			{
				return sourcePath;
			}
			else 
			if(sourceLen > (PATHCCH_MAX_CCH - ((sizeof(LONG_PATH_ID) / sizeof(WCHAR)) - 1))) //If have no space to store the prefix fail
			{
				throw std::runtime_error("Path " + StringHelper::ToString(sourcePath) + " too long!");
			}
			return LONG_PATH_ID + sourcePath;
		}

		static wstring ClearPath(const wstring & sourcePath)
		{
			if (sourcePath.substr(0, 4) == LONG_PATH_ID)
				return sourcePath.substr(4);
			else 
				return sourcePath;
		}

		static bool IsFileExists(const string & fileName)
		{
			DWORD fileAttribute = GetFileAttributesA(fileName.c_str());
			return (fileAttribute != INVALID_FILE_ATTRIBUTES);
		}
	};
}