#include "stdafx.h"
#include "GDIPlusSetup.h"

#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

Gdiplus::GdiplusStartupInput	gdiplusStartupInput;
ULONG_PTR						gdiplusToken;

namespace MyPaint
{
	void GDIPlusSetup::GDIPlusInit()
	{
		using namespace Gdiplus;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}

	void GDIPlusSetup::GDIPlusDestroy()
	{
		using namespace Gdiplus;
		GdiplusShutdown(gdiplusToken);
	}
}