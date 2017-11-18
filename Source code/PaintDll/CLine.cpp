#include "CLine.h"

namespace MyPaint
{
	CLine::CLine()
	{
	}


	CLine::~CLine()
	{
	}

	void CLine::Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop)
	{
		CShape::SetValue(leftTop, rightBottom, color, penStyle, penWidth);

		//if (bSetRop == TRUE) SetROP2(hdc, R2_MERGEPENNOT); // Chế độ vẽ không làm ảnh hưởng đến các hình đã vẽ

		Color iColor;
		iColor.SetFromCOLORREF(this->color_);
		Pen* pen = new Pen(iColor, this->penWidth_);
		pen->SetDashStyle(this->penStyle_);

		//Graphics* graphics = new Graphics(hdc);		
		gp->DrawLine(pen, leftTop_.x, leftTop_.y, rightBottom_.x, rightBottom_.y);

		delete pen;
		//delete graphics;
	}

	void CLine::WriteBinary(std::ofstream &out)
	{
		int id = 0;
		out.write((const char*)&id, sizeof(int));
		
		CShape::WriteBinary(out);
	}
}