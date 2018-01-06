#include "stdafx.h"
#include "Parallelogram.h"
#include "OurConstants.h"

namespace Shapes
{
	Parallelogram::Parallelogram(CPoint start, CPoint end, COLORREF color) : Shape(start, end, color)
	{
	}

	Parallelogram::~Parallelogram()
	{
	}

	void Parallelogram::draw(CDC* pDC, Shapes::Shape* pElement)
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
		pDC->Ellipse(enclosing_rect);

		pDC->SelectObject(pOldBrush);              // Restore the old brush
		pDC->SelectObject(pOldPen);                // Restore the old pen
	}

	void Parallelogram::resize(double number_of_times)
	{
		CPoint start, end;
		start = this->enclosing_rect.TopLeft();
		end = this->enclosing_rect.BottomRight();

		int width = end.x - start.x;
		int new_width = width * number_of_times;

		int height = end.y - start.y;
		int new_height = height * number_of_times;

		start.x -= (new_width - width) / 2.0;
		end.x += (new_width - width) / 2.0;
		start.y -= (new_height - height) / 2.0;
		end.y += (new_height - height) / 2.0;

		this->enclosing_rect = CRect(start, end);
	}

	std::string Parallelogram::getName()
	{
		return "Oval";
	}

	CArchive& Parallelogram::write(CArchive& ar) const
	{
		ar << enclosing_rect << color;
		return ar;
	}

	CArchive& Parallelogram::read(CArchive& ar)
	{
		ar >> enclosing_rect >> color;
		return ar;
	}
}