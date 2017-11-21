#include "CShape.h"

namespace MyPaint
{
	void CShape::SetValue(POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill)
	{
		this->leftTop_ = leftTop;
		this->rightBottom_ = rightBottom;
		this->colorOutline_ = colorOutline;
		this->colorFill_ = colorFill;
		this->penStyle_ = penStyle;
		this->penWidth_ = penWidth;
	}

	void CShape::ReDraw(Graphics *gp)
	{
		Draw(gp, this->leftTop_, this->rightBottom_, this->colorOutline_, this->penStyle_, this->penWidth_, this->colorFill_);
	}

	void CShape::WriteBinary(std::ofstream &out)
	{
		int point = leftTop_.x;
		out.write((const char*)&point, sizeof(int));
		point = leftTop_.y;
		out.write((const char*)&point, sizeof(int));
		point = rightBottom_.x;
		out.write((const char*)&point, sizeof(int));
		point = rightBottom_.y;
		out.write((const char*)&point, sizeof(int));

		out.write((const char*)&colorOutline_, sizeof(colorOutline_));
		out.write((const char*)&colorFill_, sizeof(colorOutline_));
		out.write((const char*)&penStyle_, sizeof(penStyle_));
		out.write((const char*)&penWidth_, sizeof(penWidth_));
	}

	void CShape::ReadBinary(std::ifstream &in)
	{
		int point;
		in.read((char*)&point, sizeof(int));
		leftTop_.x = point;
		in.read((char*)&point, sizeof(int));
		leftTop_.y = point;
		in.read((char*)&point, sizeof(int));
		rightBottom_.x = point;
		in.read((char*)&point, sizeof(int));		
		rightBottom_.y = point;

		in.read((char*)&colorOutline_, sizeof(colorOutline_));
		in.read((char*)&colorFill_, sizeof(colorFill_));
		in.read((char*)&penStyle_, sizeof(penStyle_));
		in.read((char*)&penWidth_, sizeof(penWidth_));
	}
}