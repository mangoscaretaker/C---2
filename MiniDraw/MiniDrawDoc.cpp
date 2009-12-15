
// MiniDrawDoc.cpp : implementation of the CMiniDrawDoc class
//

#include "stdafx.h"
#include "MiniDraw.h"

#include "MiniDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniDrawDoc

IMPLEMENT_DYNCREATE(CMiniDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CMiniDrawDoc, CDocument)
END_MESSAGE_MAP()


// CMiniDrawDoc construction/destruction

CMiniDrawDoc::CMiniDrawDoc()
{
	// TODO: add one-time construction code here

}

CMiniDrawDoc::~CMiniDrawDoc()
{
}

BOOL CMiniDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMiniDrawDoc serialization

void CMiniDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMiniDrawDoc diagnostics

#ifdef _DEBUG
void CMiniDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMiniDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CMiniDrawDoc::AddFigure(CFigure* pFigure) {
   m_FigArray.push_back(pFigure);
}

CFigure *CMiniDrawDoc::GetFigure(int index) {
  vector<CFigure*>::iterator p = m_FigArray.begin();
	if(index < 0 || index > m_FigArray.size())
    return NULL;
  
  return *(p+index);
}



int CMiniDrawDoc::GetNumFigs() {
   return m_FigArray.size();
}



// CMiniDrawDoc commands

void CFigure::Serialize(CArchive & ar) {
	if (ar.IsStoring()) 
	  ar << m_X1 << m_Y1 << m_X2 << m_Y2  << m_Color << m_Thickness;
  else
	  ar >> m_X1 >> m_Y1 >> m_X2 >> m_Y2 >> m_Color >> m_Thickness;
}

void CLine::Serialize(CArchive & ar) {
	CFigure::Serialize(ar);
}

void CCircle::Serialize(CArchive & ar) {
	CFigure::Serialize(ar);
	if (ar.IsStoring()) 
	  ar << m_Filled;
	else
	{
	  ar >> m_Filled;
  }
}

void CRectangle::Serialize(CArchive & ar) {
	CFigure::Serialize(ar);
}

CRect CFigure::GetDimRect() {
  return CRect(min(m_X1,m_X2),min(m_Y1,m_Y2),max(m_X1,m_X2)+1,max(m_Y1,m_Y2)+1);
}



CLine::CLine(int X1, int Y1, int X2, int Y2, COLORREF Color, int Thickness) {
  m_X1 = X1;
  m_Y1 = Y1;
  m_X2 = X2;
  m_Y2 = Y2;
  m_Color = Color;
  m_Thickness = Thickness;
}

void CLine::Draw(CDC * PDC) {
   CPen pen, *pOldPen;
   //select pen/brush:
   pen.CreatePen(PS_SOLID,m_Thickness,m_Color);
   pOldPen = PDC->SelectObject(&pen);

   PDC->MoveTo(m_X1,m_Y1);
   PDC->LineTo(m_X2,m_Y2);
   //verwijder pen/brush:
   PDC->SelectObject(pOldPen);
   ::DeleteObject(pen);
}

CRectangle::CRectangle(int X1, int Y1, int X2, int Y2, COLORREF Color, int Thickness, CString name) {
// zelf maken
  m_X1 = X1;
  m_Y1 = Y1;
  m_X2 = X2;
  m_Y2 = Y2;
  m_Color = Color;
  m_Thickness = Thickness;
  m_name = name;
}

void CRectangle::Draw(CDC *PDC) {
   CPen pen, *pOldPen;

   //select pen/brush:
   pen.CreatePen(PS_SOLID,m_Thickness,m_Color);
   pOldPen = PDC->SelectObject(&pen);
   PDC->SelectStockObject(NULL_BRUSH);
   PDC->Rectangle(m_X1,m_Y1,m_X2,m_Y2);
   //verwijder pen/brush:
   PDC->SelectObject(pOldPen);
   
   PDC->TextOutW(m_X1, m_Y2, m_name, m_name.GetLength());
   
   ::DeleteObject(pen);

}

CCircle::CCircle(int X1, int Y1, int X2, int Y2, COLORREF Color, int Thickness, bool Filled) {
  m_X1 = min(X1,X2);
  m_Y1 = min(Y1,Y2);
  m_X2 = max(X1,X2);
  m_Y2 = max(Y1,Y2);
  m_Color = Color;
  m_Thickness = Thickness;
  m_Filled = Filled;	
}

void CCircle::Draw(CDC *PDC) {
  CPen pen, *pOldPen;

   //select pen/brush:
   pen.CreatePen(PS_SOLID,m_Thickness,m_Color);
   pOldPen = PDC->SelectObject(&pen);
   PDC->SelectStockObject(NULL_BRUSH);
   if (m_Filled)
	   PDC->SelectStockObject(BLACK_BRUSH);
   else
	   PDC->SelectStockObject(NULL_BRUSH);
   PDC->Ellipse(m_X1,m_Y1,m_X2,m_Y2);
   //verwijder pen/brush:
   PDC->SelectObject(pOldPen);
   ::DeleteObject(pen);
}