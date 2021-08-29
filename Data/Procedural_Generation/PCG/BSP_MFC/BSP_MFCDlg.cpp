
// BSP_MFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BSP_MFC.h"
#include "BSP_MFCDlg.h"
#include "afxdialogex.h"
#include<iostream>
#include <random>
#include "TreeNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBSPMFCDlg 대화 상자



CBSPMFCDlg::CBSPMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BSP_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBSPMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBSPMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CBSPMFCDlg 메시지 처리기

BOOL CBSPMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CBSPMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CBSPMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBSPMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	rect_start_pos = point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CBSPMFCDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// BSP
	// 전체 맵 크기
	int maxHeight = 600;
	int maxWidth = 600;

	// 초기 맵 설정
	int** map = new int* [maxHeight];
	for (int i = 0; i < maxHeight; i++) {
		map[i] = new int[maxWidth];
		for (int j = 0; j < maxWidth; j++) {
			map[i][j] = 0;
		}
		map[i][0] = 1;
		map[i][maxWidth - 1] = 1;
	}
	for (int j = 0; j < maxWidth; j++) {
		map[0][j] = 1;
		map[maxHeight - 1][j] = 1;
	}

	// BSP 트리 초기화
	TreeNode root;
	root.setRoot(map, maxHeight, maxWidth);

	// 맵 제작
	root.devide(map, 128);


	CClientDC dc(this); //DC생성
	CPen my_pen(PS_SOLID, 1, RGB(0, 0, 255)); // 굵기가 5인 팬을 생성한다.
	dc.SelectObject(&my_pen); //  생성한 팬을 DC에 연결한다.
	SelectObject(dc, GetStockObject(NULL_BRUSH)); // 안이 투명한 도형을 그려주기 위해 NULL브러쉬를 만든다.

	if (nFlags & MK_CONTROL) // 컨트롤키가 눌려졌을때 
	{
		dc.Ellipse(rect_start_pos.x, rect_start_pos.y, point.x, point.y); // 원을 그려준다.
	}

	else { // 컨트롤키가 눌려지지 않았을때
		//dc.Rectangle(rect_start_pos.x, rect_start_pos.y, point.x, point.y); // 사각형을 그려준다.


		for (int i = 0; i < maxHeight; i++) {
			for (int j = 0; j < maxWidth; j++) {
				if (map[i][j] == 1) {
					//dc.SetPixelV(i, j, RGB(255, 0, 0));
				}
				else if (map[i][j] == 2) {
					dc.SetPixelV(i, j, RGB(0, 0, 255));
				}
				else if (map[i][j] == 3) {
					dc.SetPixelV(i, j, RGB(0, 255, 0));
					dc.SetPixelV(i + 1, j + 1, RGB(0, 255, 0));
					dc.SetPixelV(i - 1, j - 1, RGB(0, 255, 0));
				}
			}
		}

		/*
		dc.Rectangle(root.getX(), root.getY(), (root.getX() + root.getWidth()) * 3, (root.getY() + root.getHeight()) * 6);
		dc.Rectangle(root.goLeftNode()->getX(), root.goLeftNode()->getY(), (root.goLeftNode()->getX() + root.goLeftNode()->getWidth()) * 3, (root.goLeftNode()->getY() + root.goLeftNode()->getHeight()) * 6);
		dc.Rectangle(root.goRightNode()->getX(), root.goRightNode()->getY(), (root.goRightNode()->getX() + root.goRightNode()->getWidth()) * 3, (root.goRightNode()->getY() + root.goRightNode()->getHeight()) * 6);
		*/
	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);

	// 맵 매모리 삭제
	for (int i = 0; i < maxHeight; i++) {
		delete map[i];
	}
	delete map;
}
