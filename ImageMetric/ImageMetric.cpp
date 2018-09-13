// dllmain.cpp: определяет точку входа для приложения DLL.
#include "ImageMetric.h"
#include "ImageMetricsHelper.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // Подключение DLL
	case DLL_THREAD_ATTACH: // Создание нового потока
	case DLL_THREAD_DETACH: // Завершение потока
	case DLL_PROCESS_DETACH: // Отключение DLL
		break;
	}
	return TRUE;
}


DLLAPI ImageInfo CalculateImageMetric(const WChar* image)
{
	return im::Engine.CalculateImageMetric;
	if (!im::OpenCVHelper::ReadImage(img, *file, negotiator))
								return NULL;

	return im::ImageMetricsHelper.(firstImage, secondImage);
}

DLLAPI ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth)
{
	return im::ImageMetricsHelper.DrawMathes(firstImage, secondImage);
}
