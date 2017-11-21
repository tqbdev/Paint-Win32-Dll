#pragma once

#ifndef CSHAPE_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include "IShape.h"

namespace MyPaint
{
	class PAINTDLL CShape : public IShape
	{
	protected:
		POINT leftTop_;
		POINT rightBottom_;
		COLORREF colorOutline_;
		COLORREF colorFill_;
		DashStyle penStyle_;
		double penWidth_;

	public:
		virtual void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill) = 0;
		virtual void ReDraw(Graphics *gp);
		virtual void SetValue(POINT leftTop, POINT rightBottom, COLORREF colorOutline = RGB(0, 0, 0), DashStyle penStyle = DashStyle::DashStyleSolid, double penWidth = 1.0F, COLORREF colorFill = -1);
		virtual void WriteBinary(std::ofstream &out);
		virtual void ReadBinary(std::ifstream &in);
	};
}