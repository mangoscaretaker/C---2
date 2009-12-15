
// MiniDrawView.cpp : implementation of the CMiniDrawView class
//

#include "stdafx.h"
#include "MiniDraw.h"

#include "MiniDrawDoc.h"
#include "MiniDrawView.h"

#include "NameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMiniDrawView

IMPLEMENT_DYNCREATE(CMiniDrawView, CScrollView)

BEGIN_MESSAGE_MAP(CMiniDrawView, CScrollView)
// Standard printing commands
  ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMiniDrawView::OnFilePrintPreview)
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMiniDrawView construction/destruction

CMiniDrawView::CMiniDrawView()
{
	// TODO: add construction code here
  m_Dragging = false;
	m_HArrow = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	m_HCross = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	m_PenDotted.CreatePen(PS_DOT, 1, RGB(0,0,0));
}

CMiniDrawView::~CMiniDrawView()
{
}

void CMiniDrawView::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SIZE Size = {300, 300};
	SetScrollSizes (MM_TEXT, Size);
}

BOOL CMiniDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// CMiniDrawView drawing

void CMiniDrawView::OnDraw(CDC* pDC)
{
	CMiniDrawDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
  CSize ScrollSize = GetTotalSize();
	pDC->MoveTo(ScrollSize.cx, 0);
	pDC->LineTo(ScrollSize.cx, ScrollSize.cy);
	pDC->LineTo(0, ScrollSize.cy);
  int index = pDoc->GetNumFigs();
	while (index--) 
		pDoc->GetFigure(index)->Draw(pDC);

	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMiniDrawView printing


void CMiniDrawView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMiniDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMiniDrawView::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMiniDrawView::OnEndPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMiniDrawView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMiniDrawView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMiniDrawView diagnostics

#ifdef _DEBUG
void CMiniDrawView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMiniDrawView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMiniDrawDoc* CMiniDrawView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMiniDrawDoc)));
	return (CMiniDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CMiniDrawView message handlers

void CMiniDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
  CClientDC ClientDC(this);
	OnPrepareDC(&ClientDC);
	ClientDC.DPtoLP(&point);

	//ga na of de cursor binnen het gebied waarin getekend mag worden ligt
	CSize ScrollSize = GetTotalSize();
  CRect ScrollRect(0,0, ScrollSize.cx,ScrollSize.cy);
	
  if (!ScrollRect.PtInRect(point)) return;

  ClientDC.SelectObject(&m_PenDotted);
  // rest code 	
  m_PointOld = point;

  // TODO: Add your message handler code here and/or call default
  m_PointOrigin = point;   //beginpunt vastleggen
  m_PointOld = point;	 //beginpunt is eindpunt
	SetCapture();
	m_Dragging = true;
	RECT Rect;
	GetClientRect(&Rect);
	ClientToScreen(&Rect);
	::ClipCursor(&Rect);    // globale functie van de Win32 API

  CScrollView::OnLButtonDown(nFlags, point);
}

void CMiniDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
  CString name;
  // TODO: Add your message handler code here and/or call default
  if (!m_Dragging) return;
  
  

  CSize ScrollSize = GetTotalSize();
  CRect ScrollRect(0,0, ScrollSize.cx,ScrollSize.cy);

  m_Dragging = false;
  ::ReleaseCapture();			   // zie OnLButtonDown()
  ::ClipCursor(NULL);			   // de cursor kan zich weer vrij bewegen

  if (((CMiniDrawApp *)AfxGetApp())->m_CurrentTool == ID_TOOLS_RECTANGLE)
  {
    CNameDialog nameDialog;
    nameDialog.DoModal();
    name = nameDialog.getName();
  }



  CClientDC ClientDC(this);
  OnPrepareDC(&ClientDC);
  ClientDC.DPtoLP(&point);
  ClientDC.SetROP2(R2_NOT);
  ClientDC.SelectObject(&m_PenDotted); //pen instellen
  ClientDC.SetBkMode(TRANSPARENT);     //achtergrond modus instellen
  ClientDC.SelectStockObject(NULL_BRUSH); //geen kwast

  CMiniDrawApp *PApp =(CMiniDrawApp *)AfxGetApp();
  
  CFigure *PFigure=NULL;
  switch(PApp->m_CurrentTool) {
   	case ID_TOOLS_LINE:
			ClientDC.MoveTo(m_PointOrigin);
			ClientDC.LineTo(m_PointOld);
      if (ScrollRect.PtInRect(point))
      {
			  PFigure = new CLine(m_PointOrigin.x, m_PointOrigin.y, point.x,point.y, PApp->m_CurrentColor, PApp->m_CurrentThickness);
      }
      break;
    case ID_TOOLS_RECTANGLE:
      if (ScrollRect.PtInRect(point))
      {
        ClientDC.Rectangle(m_PointOrigin.x, m_PointOrigin.y, m_PointOld.x, m_PointOld.y);
		    PFigure = new CRectangle(m_PointOrigin.x, m_PointOrigin.y,point.x, point.y,PApp->m_CurrentColor, PApp->m_CurrentThickness, name);
      }
      break;

    case ID_TOOLS_CIRCLE_FILLED:
  	  
        ClientDC.SelectStockObject(BLACK_BRUSH); //zwarte kwast
    
    case ID_TOOLS_CIRCLE:
		  if (ScrollRect.PtInRect(point))
      {
        ClientDC.Ellipse(m_PointOrigin.x,m_PointOrigin.y,m_PointOld.x, m_PointOld.y);
		    PFigure = new CCircle(m_PointOrigin.x, m_PointOrigin.y, point.x,point.y, PApp->m_CurrentColor, PApp->m_CurrentThickness, PApp->m_CurrentTool == ID_TOOLS_CIRCLE_FILLED);
      }
      break;
  }
  
  if (PFigure != NULL)
  {
    ClientDC.SetROP2(R2_COPYPEN); //R2_COPYPEN: de kleur die voor de pen ingesteld is
    PFigure->Draw(&ClientDC);
    CMiniDrawDoc *PDoc = GetDocument();
    PDoc->AddFigure(PFigure);
  }else {
    Invalidate();
  }

  CScrollView::OnLButtonUp(nFlags, point);
}

void CMiniDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  CClientDC ClientDC(this);
  OnPrepareDC(&ClientDC);
  ClientDC.DPtoLP(&point);
  ::SetCursor(m_HCross);		//standaard pijlcursor aangeven	
  if (!m_Dragging) {
      return;
  }

  CSize ScrollSize = GetTotalSize();
  CRect ScrollRect(0,0, ScrollSize.cx, ScrollSize.cy);
  if (!ScrollRect.PtInRect(point)) {
    ::SetCursor(m_HCross);
  } else {
    ::SetCursor(m_HArrow);
  }

  ClientDC.SelectObject(&m_PenDotted);
  ClientDC.SetBkMode(TRANSPARENT);
  ClientDC.SelectStockObject(NULL_BRUSH);
  ClientDC.SetROP2(R2_NOT);
  switch(((CMiniDrawApp *)AfxGetApp())->m_CurrentTool) {
    case ID_TOOLS_LINE:
	    ClientDC.MoveTo(m_PointOrigin);
	    ClientDC.LineTo(m_PointOld);
	    ClientDC.MoveTo(m_PointOrigin);
	    ClientDC.LineTo(point);
	    break;
    case ID_TOOLS_RECTANGLE:
	    ClientDC.Rectangle(m_PointOrigin.x, m_PointOrigin.y, m_PointOld.x, m_PointOld.y);
	    ClientDC.Rectangle(m_PointOrigin.x,m_PointOrigin.y,point.x,point.y);
	    break;
    case ID_TOOLS_CIRCLE_FILLED:
      ClientDC.SelectStockObject(BLACK_BRUSH);
    case ID_TOOLS_CIRCLE:
	    ClientDC.Ellipse(m_PointOrigin.x, m_PointOrigin.y, m_PointOld.x, m_PointOld.y);
	    ClientDC.Ellipse(m_PointOrigin.x, m_PointOrigin.y, point.x, point.y);
	    break;
  }
  m_PointOld = point;
  CScrollView::OnMouseMove(nFlags, point);

}
