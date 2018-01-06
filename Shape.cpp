#include "stdafx.h"
#include "Shape.h"

namespace Shapes
{
	Shape::Shape(CPoint Start, CPoint End, COLORREF color)
	{
		this->enclosing_rect = CRect(Start, End);
		this->enclosing_rect.NormalizeRect();
		this->color = color;
		this->pen = 2;
	}

	Shape::~Shape()
	{
	}

	void Shape::move(CSize& size)
	{
		this->enclosing_rect += size;
	}

	void Shape::setColor(COLORREF new_color)
	{
		this->color = new_color;
	}

	CRect Shape::GetBoundRect() const
	{
		CRect BoundingRect;
		BoundingRect = this->enclosing_rect;
		BoundingRect.InflateRect(pen, pen);
		return BoundingRect;
	}

	CArchive& Shapes::operator<<(CArchive& ar, const Shape& shape)
	{
		return shape.write(ar);
	}

	CArchive& Shapes::operator >> (CArchive& ar, Shape& shape)
	{
		return shape.read(ar);
	}
}//namespace Shapes
