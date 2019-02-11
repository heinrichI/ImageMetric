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
		NOT_READ_IMAGE = 3
	};


  /*------------Structures-----------------------------------------------------*/


	struct ImageInfo
	{
		wchar_t Path[MAX_PATH_LENGTH];
		double JpegQuality;
		double Sharpness;
		int JpegPeak;
		unsigned int FileSize;
        unsigned int Width;
        unsigned int Height;
	};


	/*------------Types------------------------------------------------------*/

	typedef wchar_t WChar;

	//current step, max step, message
	typedef void (__stdcall *ReportProgressCallback)(size_t, size_t, const WChar *);
	typedef void (__stdcall *AddToLogCallback)(const WChar *);
	typedef bool (__stdcall *CancellationPendingCallback)();

	struct DLLAPI WorkProgressInteropNegotiator 
	{
		//current step, max step, message
		ReportProgressCallback progressCallback;
		AddToLogCallback addToLogCallback;
		CancellationPendingCallback cancellationPending;
		bool cancel;
	};

	/*------------Functions-------------------------------------------------------*/

	DLLAPI Error CalculateImageMetric(const WChar* imagePath, WorkProgressInteropNegotiator& negotiator, ImageInfo * exportImageInfo);
	DLLAPI ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth);

}