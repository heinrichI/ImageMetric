// dllmain.cpp: ���������� ����� ����� ��� ���������� DLL.
#include "ImageMetric.h"
#include "ImageMetricsHelper.h"

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
	return ImageMetricsHelper.DrawMathes(firstImage, secondImage);
}

DLLAPI ImageInfo ResizeAndCalculateImageMetric(const WChar* image, int width, int heigth)
{
	return ImageMetricsHelper.DrawMathes(firstImage, secondImage);
}
