#pragma once
#include "syUIForm.h"

// syUIToolPane

class syUIToolPane : public CDockablePane
{
	DECLARE_DYNAMIC(syUIToolPane)
public:
	syUIForm*	m_wndForm;
public:
	syUIToolPane();
	virtual ~syUIToolPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


