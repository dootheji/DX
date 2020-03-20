// syUIToolPane.cpp: 구현 파일
//

#include "stdafx.h"
#include "UITool.h"
#include "syUIToolPane.h"


// syUIToolPane

IMPLEMENT_DYNAMIC(syUIToolPane, CDockablePane)

syUIToolPane::syUIToolPane()
{

}

syUIToolPane::~syUIToolPane()
{
}


BEGIN_MESSAGE_MAP(syUIToolPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()



// syUIToolPane 메시지 처리기




int syUIToolPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_wndForm = syUIForm::CreateOne(this);
	return 0;
}


void syUIToolPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_wndForm)
	{
		m_wndForm->SetWindowPos(NULL, 0, 0, cx, cy,
			SWP_NOZORDER);
	}

}


int syUIToolPane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd ||
		pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}
