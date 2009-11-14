
// MiniDrawDoc.h : interface of the CMiniDrawDoc class
//

#include <vector>
using namespace std;
#pragma once

class CFigure {
  protected:
      int m_X1; int m_Y1; int m_X2; int m_Y2;
    	int m_Thickness;
      COLORREF m_Color;
virtual void CopyAll( const CFigure& cFigure )	{}
	virtual void RemoveAll() {}

  public:
      CFigure() {};
	CFigure( const CFigure& cFigure )
{
		CopyAll( cFigure );
	}

	CFigure& operator = ( const CFigure& cFigure )	
{
		if ( this != &cFigure )	{
			RemoveAll();
			CopyAll( cFigure );
		}
		return *this;
	}

    CRect GetDimRect();
    virtual void Draw(CDC *PDC) = 0;
};
class CRectangle :public CFigure {
  protected:
    CRectangle() {}
  public:
    CRectangle(int X1, int Y1, int X2, int Y2, COLORREF Color, int Thickness);
    virtual void Draw(CDC *PDC);
};

class CCircle :public CFigure {
  protected:
    bool m_Filled;
    CCircle() {}
  public:
    CCircle(int X1, int Y1, int X2, int Y2, COLORREF Color, int Thickness, bool Filled);
    void Draw(CDC *PDC);
};

class CLine :public CFigure {
  protected:
    CLine() {}
  public:
    CLine (int X1, int Y1, int X2, int Y2, COLORREF Color, int Thickness);
    virtual void Draw(CDC * PDC);
};


class CMiniDrawDoc : public CDocument
{
protected: // create from serialization only
	CMiniDrawDoc();
	DECLARE_DYNCREATE(CMiniDrawDoc)

// Attributes
  vector<CFigure*> m_FigArray; 
public:

// Operations
  void AddFigure(CFigure *pFigure);
  CFigure *GetFigure(int index);
  int GetNumFigs();
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMiniDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


