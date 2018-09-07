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

	//DLLAPI Result CppLongFunction(const WChar* directoryPath, WorkProgressInteropNegotiator& negotiator);
	DLLAPI Error ComputeHashes(WorkProgressInteropNegotiator & negotiator);
	DLLAPI Error CompareHashes(WorkProgressInteropNegotiator & negotiator);
	DLLAPI Error PostCheckBySURF(WorkProgressInteropNegotiator& negotiator);

	DLLAPI Error OptionsSet(SearchOptions * pOptions);
	DLLAPI Error Initialize();
	DLLAPI Error BeforeRelease();

//	DLLAPI DuplPairExport* GetFinalResult(unsigned int * size);
	DLLAPI unsigned int * GetResultSize();
	//DLLAPI DuplPairExport* GetResult(unsigned int & index);
	DLLAPI Error FillResult(DuplPairExport * exportResult, unsigned int index);
	DLLAPI Error DrawMathes(const WChar * firstImage, const WChar * secondImage);
	DLLAPI Error ClearHashStrorage(WorkProgressInteropNegotiator& negotiator, bool deleteResized);

	DLLAPI Error ClearSearchPath();
	DLLAPI Error AddSearchPath(const SearchPathEx* path);

}