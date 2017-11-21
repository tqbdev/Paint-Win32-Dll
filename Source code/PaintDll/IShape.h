#pragma once

#ifndef ISHAPE_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include <windows.h>
#include <fstream>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;

namespace MyPaint
{
	// Interface for all shapes
	class PAINTDLL IShape
	{
	public:
		virtual void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill) = 0;
		virtual void ReDraw(Graphics *gp) = 0;
		virtual void SetValue(POINT leftTop, POINT rightBottom, COLORREF colorOutline = RGB(0,0,0), DashStyle penStyle = DashStyle::DashStyleSolid, double penWidth = 1.0F, COLORREF colorFill = -1) = 0;
		virtual void WriteBinary(std::ofstream &out) = 0;
		virtual void ReadBinary(std::ifstream &in) = 0;
	};
}