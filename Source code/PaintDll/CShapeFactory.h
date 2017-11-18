#pragma once

#ifndef CSHAPEFACTORY_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include "CEllipse.h"
#include "CRectangle.h"
#include "CLine.h"

namespace MyPaint
{
	class PAINTDLL CShapeFactory
	{
	public:
		IShape* GetShape(int shapeId);
	};
}