// dllmain.cpp: ���������� ����� ����� ��� ���������� DLL.
#include "ImageMetric.h"
#include "ImageMetricsHelper.h"
#include "Engine.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // ����������� DLL
	case DLL_THREAD_ATTACH: // �������� ������ ������
	case DLL_THREAD_DETACH: // ���������� ������
	case DLL_PROCESS_DETACH: // ���������� DLL
		break;
	}
	return TRUE;
}


DLLAPI ImageInfo CalculateImageMetric(const WChar* image)
{
	return im::Engine::CalculateImageMetric(image);
	//if (!im::OpenCVHelper::ReadImage(img, *file, negotiator))
	//							return NULL;

//	return im::ImageMetricsHelper.(firstImage, secondImage);
}

DLLAPI ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth)
{
	im::Engine::ResizeAndCalculateImageMetric(image, width, heigth);
	//return im::ImageMetricsHelper.DrawMathes(firstImage, secondImage);
}
