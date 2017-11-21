#include "CLine.h"

namespace MyPaint
{
	CLine::CLine()
	{
	}


	CLine::~CLine()
	{
	}

	void CLine::Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF colorOutline, DashStyle penStyle, double penWidth, COLORREF colorFill)
	{
		CShape::SetValue(leftTop, rightBottom, colorOutline, penStyle, penWidth);

		Color iColor;
		iColor.SetFromCOLORREF(this->colorOutline_);
		Pen* pen = new Pen(iColor, this->penWidth_);
		pen->SetDashStyle(this->penStyle_);
	
		gp->DrawLine(pen, leftTop_.x, leftTop_.y, rightBottom_.x, rightBottom_.y);

		delete pen;
	}

	void CLine::WriteBinary(std::ofstream &out)
	{
		int id = 0;
		out.write((const char*)&id, sizeof(int));
		
		CShape::WriteBinary(out);
	}
}