#include "CRectangle.h"

namespace MyPaint
{
	CRectangle::CRectangle()
	{
	}


	CRectangle::~CRectangle()
	{
	}

	void CRectangle::Draw(Graphics *gp, POINT leftTop, POINT rightBottom, COLORREF color, DashStyle penStyle, double penWidth, BOOL bSetRop)
	{
		CShape::SetValue(leftTop, rightBottom, color, penStyle, penWidth);

		//if (bSetRop == TRUE) SetROP2(hdc, R2_MERGEPENNOT); // Chế độ vẽ không làm ảnh hưởng đến các hình đã vẽ

		//SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Nền trong suốt

		Color iColor;
		iColor.SetFromCOLORREF(this->color_);
		Pen* pen = new Pen(iColor, this->penWidth_);
		pen->SetDashStyle(this->penStyle_);

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

		//Graphics* graphics = new Graphics(hdc);
		gp->DrawRectangle(pen, upperConner.x, upperConner.y, abs(rightBottom_.x - leftTop_.x), abs(rightBottom_.y - leftTop_.y));

		delete pen;
		//delete graphics;
	}

	void CRectangle::WriteBinary(std::ofstream &out)
	{
		int id = 1;
		out.write((const char*)&id, sizeof(int));
		
		CShape::WriteBinary(out);
	}
}