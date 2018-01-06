#pragma once
#include "Shape.h"

namespace Shapes
{
	class Rectangle :
		virtual public Shape
	{
	public:
		Rectangle(CPoint, CPoint, COLORREF);

		void draw(CDC*, Shape* c = 0);
		void resize(double);
		std::string getName();

		CArchive& write(CArchive&) const;
		CArchive& read(CArchive&);
	};
}
