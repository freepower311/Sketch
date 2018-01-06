// SketcherDoc.cpp : implementation of the CSketcherDoc class
//

#include "stdafx.h"
#include "Sketcher.h"

#include "Elements.h"
#include "SketcherDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	//{{AFX_MSG_MAP(CSketcherDoc)
	ON_COMMAND(ID_COLOR_BLACK, OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, OnColorRed)
	ON_COMMAND(ID_ELEMENT_LINE, OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, OnElementRectangle)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, OnUpdateElementLine)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, OnUpdateElementRectangle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSketcherDoc construction/destruction

CSketcherDoc::CSketcherDoc()
{
	// TODO: add one-time construction code here
   m_Element = LINE;   // Set initial element type
   m_Color = BLACK;    // Set initial drawing color
   m_DocSize = CSize(3000,3000);  // Set initial document size 30x30 inches
}

CSketcherDoc::~CSketcherDoc()
{
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
   m_ElementList.Serialize(ar);    // Serialize the element list
   if (ar.IsStoring())
   {
      ar << m_Color                // Store the current color
         << m_Element              // the current element type,
         << m_DocSize;             // and the current document size
   }
   else
   {
      ar >> m_Color                // Retrieve the current color
         >> m_Element              // the current element type,
         >> m_DocSize;             // and the current document size
   }
}

/////////////////////////////////////////////////////////////////////////////
// CSketcherDoc diagnostics

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSketcherDoc commands

void CSketcherDoc::OnColorBlack() 
{
   m_Color = BLACK;        // Set the drawing color to black
}

void CSketcherDoc::OnColorRed() 
{
   m_Color = RED;          // Set the drawing color to red	
}

void CSketcherDoc::OnElementLine() 
{
   m_Element = LINE;       // Set element type as a line	
}

void CSketcherDoc::OnElementRectangle() 
{
   m_Element = RECTANGLE;  // Set element type as a rectangle	
}

void CSketcherDoc::OnUpdateColorBlack(CCmdUI* pCmdUI) 
{
   // Set menu item Checked if the current color is black
   pCmdUI->SetCheck(m_Color==BLACK);
}

void CSketcherDoc::OnUpdateColorRed(CCmdUI* pCmdUI) 
{
   // Set menu item Checked if the current color is red
   pCmdUI->SetCheck(m_Color==RED);
}

void CSketcherDoc::OnUpdateElementLine(CCmdUI* pCmdUI) 
{
   // Set Checked if the current element is a line
   pCmdUI->SetCheck(m_Element==LINE);
}

void CSketcherDoc::OnUpdateElementRectangle(CCmdUI* pCmdUI) 
{
   // Set Checked if the current element is a rectangle
   pCmdUI->SetCheck(m_Element==RECTANGLE);
}

void CSketcherDoc::DeleteElement(CElement* pElement)
{
   if(pElement)
   {
      // If the element pointer is valid,
      // find the pointer in the list and delete it
      POSITION aPosition = m_ElementList.Find(pElement);
      m_ElementList.RemoveAt(aPosition);
      delete pElement;           // Delete the element from the heap
   }
}

void CSketcherDoc::SendToBack(CElement* pElement)
{
   if(pElement)
   {
      // If the element pointer is valid,
      // find the pointer in the list and remove the element
      POSITION aPosition = m_ElementList.Find(pElement);
      m_ElementList.RemoveAt(aPosition);

      m_ElementList.AddHead(pElement);  // Put it back to the beginning
   }
}

// Get the rectangle enclosing the entire document
CRect CSketcherDoc::GetDocExtent()
{
   CRect DocExtent(0,0,1,1);    // Initial document extent
   CRect ElementBound(0,0,0,0); // Space for element bounding rectangle

   POSITION aPosition = m_ElementList.GetHeadPosition();

   while(aPosition)      // Loop through all the elements in the list
   {
      // Get the bounding rectangle for the element
      ElementBound=(m_ElementList.GetNext(aPosition))->GetBoundRect();

      // Make coordinates of document extent the outer limits
      DocExtent.UnionRect(DocExtent, ElementBound);
   }
   DocExtent.NormalizeRect();
   return DocExtent;
}
