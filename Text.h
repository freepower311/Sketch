#pragma once
#include "Shape.h"

namespace Shapes
{
	class Text : virtual public Shape
	{
	private:
		std::string text;
		int fontSize;

	public:
		Text(std::string, CPoint, CPoint, COLORREF);

		void draw(CDC*, Shape* c = 0);
		void resize(double);
		std::string getName();

		CArchive& write(CArchive&) const;
		CArchive& read(CArchive&);
	};
}

