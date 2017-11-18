#include "CEllipse.h"

namespace MyPaint
{
	CEllipse::CEllipse()
	{
	}


	CEllipse::~CEllipse()
	{
	}

	void CEllipse::Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop)
	{
		CShape::SetValue(leftTop, rightBottom, color, penStyle, penWidth);

		//if (bSetRop == TRUE) SetROP2(hdc, R2_MERGEPENNOT); // Chế độ vẽ không làm ảnh hưởng đến các hình đã vẽ

		//SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Nền trong suốt

		Color iColor;
		iColor.SetFromCOLORREF(this->color_);
		Pen* pen = new Pen(iColor, this->penWidth_);
		pen->SetDashStyle(this->penStyle_);
	
		//Graphics* graphics = new Graphics(hdc);
		gp->DrawEllipse(pen, leftTop_.x, leftTop_.y, rightBottom_.x - leftTop_.x, rightBottom_.y - leftTop_.y);

		delete pen;
		//delete graphics;
	}

	void CEllipse::WriteBinary(std::ofstream &out)
	{
		int id = 2;
		out.write((const char*)&id, sizeof(int));
		
		CShape::WriteBinary(out);
	}
}