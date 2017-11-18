#pragma once

#ifndef CSHAPECACHE_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include "CEllipse.h"
#include "CRectangle.h"
#include "CLine.h"
#include <vector>

namespace MyPaint
{
	class PAINTDLL CShapeCache
	{
	private:
		static std::vector<MyPaint::IShape*> shapeMap_;
	public:
		static void LoadCache();
		static void ClearCache();
		static IShape* GetShape(int shapeId);
	};
}