#pragma once
#include "Text.h"
#include "Rectangle.h"

namespace Shapes
{
	class TextInRectangle : public Text, public Rectangle
	{
	public:
		TextInRectangle(std::string, CPoint, CPoint, COLORREF);
		~TextInRectangle();
		void draw(CDC*, Shape* c = 0);
		void resize(double);
		std::string getName();

		CArchive& write(CArchive&) const;
		CArchive& read(CArchive&);
	};
}

