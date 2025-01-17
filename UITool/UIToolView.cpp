﻿
// UIToolView.cpp: CUIToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "UITool.h"
#endif

#include "UIToolDoc.h"
#include "UIToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUIToolView

IMPLEMENT_DYNCREATE(CUIToolView, CView)

BEGIN_MESSAGE_MAP(CUIToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CUIToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CUIToolView 생성/소멸

CUIToolView::CUIToolView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CUIToolView::~CUIToolView()
{
}

BOOL CUIToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CUIToolView 그리기

void CUIToolView::OnDraw(CDC* /*pDC*/)
{
	CUIToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CUIToolView 인쇄


void CUIToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CUIToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CUIToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CUIToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CUIToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CUIToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CUIToolView 진단

#ifdef _DEBUG
void CUIToolView::AssertValid() const
{
	CView::AssertValid();
}

void CUIToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUIToolDoc* CUIToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUIToolDoc)));
	return (CUIToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CUIToolView 메시지 처리기


void CUIToolView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	pApp->m_Tool.ResizeDevice(cx, cy);
	if (g_pDevice)
	{
		pApp->m_Tool.m_CameraBack.Init();
		pApp->m_Tool.m_CameraBack.SetProjMatrix(D3DX_PI / 4, g_rtClient.right / g_rtClient.bottom, 1.0f, 1000.0f);
	}
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


LRESULT CUIToolView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	CUIToolApp* pApp = (CUIToolApp*)AfxGetApp();
	HWND hWnd = pApp->m_Tool.m_hWnd;
	MSG msg;
	msg.hwnd = hWnd;
	msg.message = message;
	pApp->m_Tool.MessageProc(msg);
	pApp->m_Tool.MsgProc(hWnd, message, wParam, lParam);

	return CView::WindowProc(message, wParam, lParam);
}
