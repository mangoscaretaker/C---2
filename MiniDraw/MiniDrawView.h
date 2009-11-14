
// MiniDrawView.h : interface of the CMiniDrawView class
//


#pragma once


class CMiniDrawView : public CView
{
protected: // create from serialization only
  CString m_ClassName;
	bool m_Dragging;		//wordt er verplaatst?
	HCURSOR m_HArrow;		//vorm van de cursor
	HCURSOR m_HCross;		//vorm van de cursor
	CPen m_PenDotted;		//vorm van de lijn
	CPoint m_PointOld;	//plaats van figuur
	CPoint m_PointOrigin;	//plaats van figuur

	CMiniDrawView();
	DECLARE_DYNCREATE(CMiniDrawView)

// Attributes
public:
	CMiniDrawDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMiniDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in MiniDrawView.cpp
inline CMiniDrawDoc* CMiniDrawView::GetDocument() const
   { return reinterpret_cast<CMiniDrawDoc*>(m_pDocument); }
#endif

