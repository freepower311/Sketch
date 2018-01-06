#include "stdafx.h"
#include "Text.h"
#include "OurConstants.h"

namespace Shapes
{
	Text::Text(std::string text, CPoint start, CPoint end, COLORREF color) : Shape(start, end, color)
	{
		this->text = text;
		this->fontSize = 100;
	}

	void Text::draw(CDC* pDC, Shapes::Shape* pElement)
	{
		// Create a pen for this object and
		// initialize it to the object color and line width of 1 pixel
		COLORREF aColor = color;            // Initialize with element color
		if (this == pElement)               // This element selected?
			aColor = SELECT_COLOR;          // Set highlight color

											// Select the brush
		CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

		// Select the font
		CFont* font = new CFont();
		font->CreatePointFont(fontSize, "Arial", pDC);
		CFont* pOldFont = pDC->SelectObject(font);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(aColor);

		// Now draw the text
		int height = pDC->DrawText(this->text.c_str(), CRect(this->enclosing_rect), DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_CALCRECT);
		CRect rc = CRect(this->enclosing_rect);
		int center_y = rc.CenterPoint().y;
		rc.top = center_y - height / 2;
		rc.bottom = center_y + height / 2;
		pDC->DrawText(this->text.c_str(), rc, DT_CENTER | DT_VCENTER | DT_WORDBREAK);

		pDC->SelectObject(pOldBrush); // Restore the old brush
		pDC->SelectObject(pOldFont);  // Restore the old font
	}

	void Text::resize(double number_of_times)
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

		this->fontSize *= number_of_times;
	}

	std::string Shapes::Text::getName()
	{
		return "Text";
	}

	CArchive& Shapes::Text::write(CArchive& ar) const
	{
		CString c_string(text.c_str());
		ar << c_string << fontSize << enclosing_rect << color;
		return ar;
	}

	CArchive& Shapes::Text::read(CArchive& ar)
	{
		CString c_string;
		ar >> c_string >> fontSize >> enclosing_rect >> color;
		text = std::string(c_string);
		return ar;
	}
}
