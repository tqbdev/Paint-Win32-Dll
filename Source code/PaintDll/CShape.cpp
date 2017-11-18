#include "CShape.h"

namespace MyPaint
{
	void CShape::SetValue(POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth)
	{
		this->leftTop_ = leftTop;
		this->rightBottom_ = rightBottom;
		this->color_ = color;
		this->penStyle_ = penStyle;
		this->penWidth_ = penWidth;
	}

	void CShape::ReDraw(Graphics *gp)
	{
		Draw(gp, this->leftTop_, this->rightBottom_, this->color_, this->penStyle_, this->penWidth_, TRUE);
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

		out.write((const char*)&color_, sizeof(color_));
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

		in.read((char*)&color_, sizeof(color_));
		in.read((char*)&penStyle_, sizeof(penStyle_));
		in.read((char*)&penWidth_, sizeof(penWidth_));
	}
}