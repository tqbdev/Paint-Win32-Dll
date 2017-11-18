#include "CShapeCache.h"

namespace MyPaint
{
	std::vector<MyPaint::IShape*> CShapeCache::shapeMap_;

	void CShapeCache::LoadCache()
	{
		CLine* line = new CLine();
		shapeMap_.push_back(line);

		CRectangle* rect = new CRectangle();
		shapeMap_.push_back(rect);

		CEllipse* ellipse = new CEllipse();
		shapeMap_.push_back(ellipse);
	}

	void CShapeCache::ClearCache()
	{
		for (int i = shapeMap_.size() - 1; i >= 0; i--)
		{
			IShape* temp = shapeMap_[i];
			delete temp;
			shapeMap_.pop_back();
		}
	}

	IShape* CShapeCache::GetShape(int shapeId)
	{
		if (shapeId > -1 && shapeId < shapeMap_.size())
		{
			return shapeMap_[shapeId];
		}

		return NULL;
	}
}