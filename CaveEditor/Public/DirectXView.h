#pragma once


// DirectXView 보기
class InputClass;
class GraphicsClass;
class DirectXView : public CView
{
	DECLARE_DYNCREATE(DirectXView)

protected:
	DirectXView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~DirectXView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	HWND m_hFrameWnd;

	InputClass* m_Input = nullptr;
	GraphicsClass* m_Graphics = nullptr;
	
	bool m_dragFlag = false;
	int curSeletedObjectIndex = 0;

public:
	BOOL Frame();
	void AddImageFile(WCHAR* filename);
	void Shutdown();
	void SetSlectedObject(int i) { curSeletedObjectIndex = i; }

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};



