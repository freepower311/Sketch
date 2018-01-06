#pragma once
#include "Shape.h"
namespace Shapes
{
	class Parallelogram :
		public Shape
	{
	public:
		Parallelogram(CPoint, CPoint, COLORREF);
		~Parallelogram();

		void draw(CDC*, Shape* c = 0);
		void resize(double);
		std::string getName();

		CArchive& write(CArchive&) const;
		CArchive& read(CArchive&);
	};
}

