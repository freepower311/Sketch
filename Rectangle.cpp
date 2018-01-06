#include "stdafx.h"
#include "Rectangle.h"
#include "OurConstants.h"

namespace Shapes
{
	Rectangle::Rectangle(CPoint start, CPoint end, COLORREF color) : Shape(start, end, color)
	{
	}

	void Rectangle::draw(CDC* pDC, Shapes::Shape* pElement)
	{
		// Create a pen for this object and
		// initialize it to the object color and line width of 1 pixel
		CPen aPen;
		COLORREF aColor = color;             // Initialize with element color
		if (this == pElement)                   // This element selected?
			aColor = SELECT_COLOR;              // Set highlight color
		if (!aPen.CreatePen(PS_SOLID, pen, aColor))
		{
			AfxMessageBox("Pen creation failed drawing a rectangle", MB_OK);
			AfxAbort();
		}

		// Select the pen
		CPen* pOldPen = pDC->SelectObject(&aPen);
		// Select the brush
		CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

		// Now draw the Rectangle
		pDC->Rectangle(enclosing_rect);

		pDC->SelectObject(pOldBrush);              // Restore the old brush
		pDC->SelectObject(pOldPen);                // Restore the old pen
	}

	void Rectangle::resize(double number_of_times)
	{
		CPoint start, end;
		start = this->enclosing_rect.TopLeft();
		end = this->enclosing_rect.BottomRight();

		int size = end.x - start.x;
		int new_size = size * number_of_times;

		start.x -= (new_size - size) / 2.0;
		start.y -= (new_size - size) / 2.0;
		end.x += (new_size - size) / 2.0;
		end.y += (new_size - size) / 2.0;

		this->enclosing_rect = CRect(start, end);
	}

	std::string Shapes::Rectangle::getName()
	{
		return "Rectangle";
	}

	CArchive& Shapes::Rectangle::write(CArchive& ar) const
	{
		ar << enclosing_rect << color;
		return ar;
	}

	CArchive& Shapes::Rectangle::read(CArchive& ar)
	{
		ar >> enclosing_rect >> color;
		return ar;
	}
}
