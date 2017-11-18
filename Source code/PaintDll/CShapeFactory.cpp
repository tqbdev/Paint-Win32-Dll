#include "CShapeFactory.h"

namespace MyPaint
{
	IShape* CShapeFactory::GetShape(int shapeId)
	{
		switch (shapeId)
		{
		case 0:
			return new CLine();
		case 1:
			return new CRectangle();
		case 2:
			return new CEllipse();
		default:
			return NULL;
		}
	}
}