#include "CEllipse.h"

namespace MyPaint
{
	CEllipse::CEllipse()
	{
	}


	CEllipse::~CEllipse()
	{
	}

	void CEllipse::Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill)
	{
		CShape::SetValue(leftTop, rightBottom, colorOutline, penStyle, penWidth, colorFill);

		if (this->colorFill_ != -1)
		{
			Color color_fill;
			color_fill.SetFromCOLORREF(this->colorFill_);
			SolidBrush *brush = new SolidBrush(color_fill);
			gp->FillEllipse(brush, leftTop_.x, leftTop_.y, rightBottom_.x - leftTop_.x, rightBottom_.y - leftTop_.y);
			delete brush;
		}

		Color iColor;
		iColor.SetFromCOLORREF(this->colorOutline_);
		Pen* pen = new Pen(iColor, this->penWidth_);
		pen->SetDashStyle(this->penStyle_);
	
		gp->DrawEllipse(pen, leftTop_.x, leftTop_.y, rightBottom_.x - leftTop_.x, rightBottom_.y - leftTop_.y);

		delete pen;
	}

	void CEllipse::WriteBinary(std::ofstream &out)
	{
		int id = 2;
		out.write((const char*)&id, sizeof(int));
		
		CShape::WriteBinary(out);
	}
}