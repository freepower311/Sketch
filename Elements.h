#ifndef Elements_h
#define Elements_h
// Generic element class
class CElement: public CObject
{
DECLARE_SERIAL(CElement)

protected:
   COLORREF m_Color;                          // Color of an element
   CRect m_EnclosingRect;             // Rectangle enclosing an element
   int m_Pen;                         // Pen width

public:
   virtual ~CElement(){}                      // Virtual destructor
   virtual void Draw(CDC* pDC, CElement* pElement=0) {}
   virtual void Move(CSize& aSize) {}  // Move an element
   CRect GetBoundRect();              // Get the bounding rectangle for an element
   virtual void Serialize(CArchive& ar);  // Serialize function for CElement

protected:
   CElement(){}                               // Default constructor
};

// Class defining a line object
class CLine: public CElement
{
DECLARE_SERIAL(CLine)

public:
   void Draw(CDC* pDC, CElement* pElement=0);
   void Move(CSize& aSize);  // Move an element
   
   // Constructor for a line object
   CLine(CPoint Start, CPoint End, COLORREF aColor);
   virtual void Serialize(CArchive& ar);  // Serialize function for CList

protected:
   CPoint m_StartPoint;          // Start point of line
   CPoint m_EndPoint;            // End point of line

   CLine(){}             // Default constructor - should not be used
};

// Class defining a rectangle object
class CRectangle: public CElement
{
DECLARE_SERIAL(CRectangle)

public:
   void Draw(CDC* pDC, CElement* pElement=0);
   void Move(CSize& aSize);  // Move an element
   
   // Constructor for a rectangle object
   CRectangle(CPoint Start, CPoint End, COLORREF aColor);
   virtual void Serialize(CArchive& ar);  // Serialize function for CRectangle

protected:
   CRectangle(){}        // Default constructor - should not be used
};

#endif
