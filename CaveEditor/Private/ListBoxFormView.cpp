// ListBoxFormView.cpp: 구현 파일
//

#include "pch.h"
#include "resource.h"
#include "ListBoxFormView.h"
#include "MainFrm.h"
#include "DirectXView.h"

// ListBoxFormView

IMPLEMENT_DYNCREATE(ListBoxFormView, CFormView)

ListBoxFormView::ListBoxFormView()
	: CFormView(IDD_FORMVIEW)
{

}

ListBoxFormView::~ListBoxFormView()
{
}

void ListBoxFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox1);
}

void ListBoxFormView::OnDestroy()
{
	CFormView::OnDestroy();
	m_listBox1.Detach();
}


BEGIN_MESSAGE_MAP(ListBoxFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &ListBoxFormView::AddTextureFileButton)
	ON_LBN_SELCHANGE(IDC_LIST1, &ChangeSelectedObject)
END_MESSAGE_MAP()

void ListBoxFormView::AddTextureFileButton()
{
	static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal()) {
		CString pathName = dlg.GetPathName();
		//MessageBox(pathName);
		p_dView->AddImageFile(T2W(pathName.GetBuffer()));
		m_listBox1.AddString(pathName);
		pathName.ReleaseBuffer();
	}
}
void ListBoxFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	p_dView = (DirectXView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
	//m_listBox1.Attach(GetDlgItem(IDC_LIST1)->m_hWnd);
}

void ListBoxFormView::ChangeSelectedObject()
{
	p_dView->SetSlectedObject(m_listBox1.GetCurSel());
}

// ListBoxFormView 진단

#ifdef _DEBUG
void ListBoxFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ListBoxFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ListBoxFormView 메시지 처리기
