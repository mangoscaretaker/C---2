
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


// CMiniDrawDoc commands
