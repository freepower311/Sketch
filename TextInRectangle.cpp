#include "stdafx.h"
#include "TextInRectangle.h"

namespace Shapes
{
	TextInRectangle::TextInRectangle(std::string text, CPoint start, CPoint end, COLORREF color) :
		Shape(start, end, color), Text(text, start, end, color), Rectangle(start, end, color)
	{
	}


	TextInRectangle::~TextInRectangle()
	{
	}

	void TextInRectangle::draw(CDC* pDC, Shapes::Shape* pElement)
	{
		Text::draw(pDC, pElement);
		Rectangle::draw(pDC, pElement);
	}

	void TextInRectangle::resize(double number_of_times)
	{
		CRect tmp = this->enclosing_rect;
		Text::resize(number_of_times);
		this->enclosing_rect = tmp;
		Rectangle::resize(number_of_times);
	}

	std::string TextInRectangle::getName()
	{
		return "TextInOval";
	}

	CArchive& TextInRectangle::write(CArchive& ar) const
	{
		Text::write(ar);
		Rectangle::write(ar);
		return ar;
	}

	CArchive& TextInRectangle::read(CArchive& ar)
	{
		Text::read(ar);
		Rectangle::read(ar);
		return ar;
	}
}