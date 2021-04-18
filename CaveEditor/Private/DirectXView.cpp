// DirectXView.cpp: 구현 파일
//

#include "pch.h"
#include "CaveEditor.h"
#include "DirectXView.h"
#include "MainFrm.h"
#include "inputclass.h"
#include "graphicsclass.h"


// DirectXView

IMPLEMENT_DYNCREATE(DirectXView, CView)

DirectXView::DirectXView()
{

}

DirectXView::~DirectXView()
{
}

BEGIN_MESSAGE_MAP(DirectXView, CView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_MOUSEHWHEEL()
ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// DirectXView 그리기

void DirectXView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// DirectXView 진단

#ifdef _DEBUG
void DirectXView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void DirectXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// DirectXView 메시지 처리기


BOOL DirectXView::Frame()
{
	// ESC 키 감지 및 종료 여부를 처리합니다
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// 그래픽 객체의 Frame을 처리합니다
	return m_Graphics->Frame();
}

void DirectXView::AddImageFile(WCHAR* filename)
{
	m_Graphics->AddBitmap(filename);
}

void DirectXView::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// m_Input 객체 반환
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}
}


void DirectXView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//m_hWnd = ((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1)->GetSafeHwnd();
	m_hWnd = GetSafeHwnd();
	//m_hFrameWnd = GetTopLevelParent()->GetSafeHwnd();
	m_hFrameWnd = GetTopLevelParent()->GetSafeHwnd();
	CRect rect;
	GetClientRect(&rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	m_Input = new InputClass;

	// m_Input 객체 초기화
	m_Input->Initialize();

	// m_Graphics 객체 생성.  그래픽 랜더링을 처리하기 위한 객체입니다.
	m_Graphics = new GraphicsClass;

	// m_Graphics 객체 초기화.
	m_Graphics->Initialize(width, height, m_hWnd);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void DirectXView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_dragFlag = true;
}

void DirectXView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_dragFlag) {
		m_Graphics->MoveObject(curSeletedObjectIndex, point.x, point.y);
	}

}


void DirectXView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	m_dragFlag = false;
}



BOOL DirectXView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (zDelta < 0) m_Graphics->ZoomOutScreen();
	else if(zDelta > 0) m_Graphics->ZoomInScreen();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
