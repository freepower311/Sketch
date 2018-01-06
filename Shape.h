#pragma once

#include "afx.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <string>

namespace Shapes
{
	class Shape : public CObject
	{
	protected:
		COLORREF color;
		CRect enclosing_rect;
		int pen;

	public:
		Shape(CPoint, CPoint, COLORREF);
		virtual ~Shape();

		void move(CSize&);
		void setColor(COLORREF);
		CRect GetBoundRect() const;

		virtual void draw(CDC*, Shape* s = 0) = 0;
		virtual void resize(double) = 0;
		virtual std::string getName() = 0;

		virtual CArchive& write(CArchive&) const = 0;
		virtual CArchive& read(CArchive&) = 0;

		friend CArchive& operator<<(CArchive&, const Shape&);
		friend CArchive& operator >> (CArchive&, Shape&);
	};
} //namespace Shapes

