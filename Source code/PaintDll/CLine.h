#pragma once

#ifndef CELLIPSE_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include "CShape.h"

namespace MyPaint
{
	class PAINTDLL CLine : public CShape
	{
	public:
		CLine();
		~CLine();

		void Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop = TRUE);
		void WriteBinary(std::ofstream &out);
	};
}