#pragma once

#ifndef CRECTANGLE_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include "CShape.h"

namespace MyPaint
{
	class PAINTDLL CRectangle : public CShape
	{
	public:
		CRectangle();
		~CRectangle();

		void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill);
		void WriteBinary(std::ofstream &out);
	};
}