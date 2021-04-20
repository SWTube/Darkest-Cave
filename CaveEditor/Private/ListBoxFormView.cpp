// ListBoxFormView.cpp: 구현 파일
//

#include "pch.h"
#include "resource.h"
#include "ListBoxFormView.h"
#include "MainFrm.h"
#include "DirectXView.h"
#include "../ObjectInfoDlg.h"
#include "GraphicsClass.h"
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
	DDX_Control(pDX, IDC_LIST2, m_textureListbox);
}

void ListBoxFormView::OnDestroy()
{
	CFormView::OnDestroy();
	delete m_infoDlg;
}


BEGIN_MESSAGE_MAP(ListBoxFormView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &ListBoxFormView::AddTextureFileButton)
	ON_LBN_SELCHANGE(IDC_LIST1, &ChangeSelectedObject)
	ON_LBN_DBLCLK(IDC_LIST1, &OpenObjectInfoDlg)
	ON_MESSAGE(INFO_DLG_OK_BUTTON, &ListBoxFormView::OnInfoDlgOkButton)
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
		m_textureListbox.AddString(pathName);
		m_infoDlg->AddTextureFile(pathName);
		pathName.ReleaseBuffer();
	}
}
void ListBoxFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	p_dView = (DirectXView*)((CMainFrame*)AfxGetMainWnd())->m_wndSplitter.GetPane(0, 1);
	m_infoDlg = new ObjectInfoDlg();
	m_infoDlg->Create(IDD_DIALOG1, this);
	m_infoDlg->SetParentHwnd(m_hWnd);
}

void ListBoxFormView::ChangeSelectedObject()
{
	p_dView->SetSlectedObject(m_listBox1.GetCurSel());
}

void ListBoxFormView::OpenObjectInfoDlg()
{
	int curIndex = m_listBox1.GetCurSel();
	CString name;
	m_listBox1.GetText(curIndex, name);
	float posX, posY;
	GraphicsClass::GetInstance()->GetObjectPosition(curIndex, posX, posY);
	int width, height;
	GraphicsClass::GetInstance()->GetBitmapSize(curIndex,width, height);
	m_infoDlg->Init(name, posX, posY,width,height, GraphicsClass::GetInstance()->GetBitmapTextureIndex(curIndex));
	m_infoDlg->ShowWindow(SW_SHOW);
}

void ListBoxFormView::ApplyObjectInfo()
{
	int curIndex = m_listBox1.GetCurSel();
	CString preName; 
	m_listBox1.GetText(curIndex, preName);
	CString curName = m_infoDlg->GetName();
	if (preName != curName) {
		m_listBox1.DeleteString(curIndex);
		m_listBox1.InsertString(curIndex, curName);
	}
	float x, y;
	m_infoDlg->GetPos(x, y);
	GraphicsClass::GetInstance()->MoveObject(curIndex, x, y);
	int w, h;
	m_infoDlg->GetSize(w, h);
	GraphicsClass::GetInstance()->SetBitmapSize(curIndex,w, h);
	GraphicsClass::GetInstance()->SetBitmapTexture(curIndex, m_infoDlg->GetTextureIndex());
}

LRESULT ListBoxFormView::OnInfoDlgOkButton(WPARAM wParam, LPARAM lParam)
{
	ApplyObjectInfo();
	return LRESULT();
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
