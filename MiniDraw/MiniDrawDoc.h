
// MiniDrawDoc.h : interface of the CMiniDrawDoc class
//


#pragma once


class CMiniDrawDoc : public CDocument
{
protected: // create from serialization only
	CMiniDrawDoc();
	DECLARE_DYNCREATE(CMiniDrawDoc)

// Attributes
public:

// Operations
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


