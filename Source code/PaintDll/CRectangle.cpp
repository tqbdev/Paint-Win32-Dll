#include "CRectangle.h"

namespace MyPaint
{
	CRectangle::CRectangle()
	{
	}


	CRectangle::~CRectangle()
	{
	}

	void CRectangle::Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill)
	{
		CShape::SetValue(leftTop, rightBottom, colorOutline, penStyle, penWidth, colorFill);

		POINT upperConner;
		if (leftTop_.x > rightBottom_.x && leftTop_.y > rightBottom_.y)
		{
			upperConner = rightBottom_;
		}
		else if (leftTop_.x < rightBottom_.x && leftTop_.y < rightBottom_.y)
		{
			upperConner = leftTop_;
		}
		else if (leftTop_.x < rightBottom_.x && leftTop_.y > rightBottom_.y)
		{
			upperConner.x = leftTop_.x;
			upperConner.y = rightBottom_.y;
		}
		else
		{
			upperConner.x = rightBottom_.x;
			upperConner.y = leftTop_.y;
		}

		if (this->colorFill_ != -1)
		{
			Color color_fill;
			color_fill.SetFromCOLORREF(this->colorFill_);
			SolidBrush *brush = new SolidBrush(color_fill);
			gp->FillRectangle(brush, upperConner.x, upperConner.y, abs(rightBottom_.x - leftTop_.x), abs(rightBottom_.y - leftTop_.y));
			delete brush;
		}

		Color iColor;
		iColor.SetFromCOLORREF(this->colorOutline_);
		Pen* pen = new Pen(iColor, this->penWidth_);
		pen->SetDashStyle(this->penStyle_);

		gp->DrawRectangle(pen, upperConner.x, upperConner.y, abs(rightBottom_.x - leftTop_.x), abs(rightBottom_.y - leftTop_.y));

		delete pen;
	}

	void CRectangle::WriteBinary(std::ofstream &out)
	{
		int id = 1;
		out.write((const char*)&id, sizeof(int));
		
		CShape::WriteBinary(out);
	}
}