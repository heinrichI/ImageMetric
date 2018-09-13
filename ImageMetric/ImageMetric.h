#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows:
#include <windows.h>

//длина самого длинного пути 32767 (0x8000-32768)
#define PATHCCH_MAX_CCH 32767
#define MAX_PATH_LENGTH PATHCCH_MAX_CCH

#define DLLAPI __declspec(dllexport)

extern "C"
{
	/*------------Enumerations-----------------------------------------------*/

	enum Error : __int32
	{
		OK = 0,
		ERROR_UNKNOWN = 1,
		ERROR_INVALID_POINTER = 2,
	};


  /*------------Structures-----------------------------------------------------*/


	struct ImageInfo
	{
		wchar_t Path[MAX_PATH_LENGTH];
		double JpegQuality;
		double Sharpness;
		unsigned int FileSize;
        unsigned int Width;
        unsigned int Height;
	};


	/*------------Types------------------------------------------------------*/

	typedef wchar_t WChar;

	/*------------Functions-------------------------------------------------------*/

	DLLAPI ImageInfo CalculateImageMetric(const WChar* image);
	DLLAPI ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth);

}