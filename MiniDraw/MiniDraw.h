
// MiniDraw.h : main header file for the MiniDraw application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMiniDrawApp:
// See MiniDraw.cpp for the implementation of this class
//

class CMiniDrawApp : public CWinAppEx
{
public:
  int m_CurrentThickness;
  UINT m_CurrentTool;
  COLORREF m_CurrentColor;
	CMiniDrawApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
  afx_msg void OnToolsLine();
	afx_msg void OnUpdateToolsLine(CCmdUI* pCmdUI);
	afx_msg void OnToolsRectangle();
	afx_msg void OnUpdateToolsRectangle(CCmdUI* pCmdUI);
	afx_msg void OnToolsCircle();
	afx_msg void OnUpdateToolsCircle(CCmdUI* pCmdUI);
	afx_msg void OnToolsCircleFilled();
	afx_msg void OnUpdateToolsCircleFilled(CCmdUI* pCmdUI);
	afx_msg void OnLineSingle();
	afx_msg void OnUpdateLineSingle(CCmdUI* pCmdUI);
	afx_msg void OnLineDouble();
	afx_msg void OnUpdateLineDouble(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
};

extern CMiniDrawApp theApp;
