// ObjectInfoDlg.cpp: 구현 파일
//

#include "pch.h"
#include "resource.h"
#include "ObjectInfoDlg.h"
#include "afxdialogex.h"


// ObjectInfoDlg 대화 상자

IMPLEMENT_DYNAMIC(ObjectInfoDlg, CDialogEx)

ObjectInfoDlg::ObjectInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

ObjectInfoDlg::~ObjectInfoDlg()
{
}

void ObjectInfoDlg::Init(CString name, float posX, float posY,int width,int height, int textureIndex)
{
	m_nameEdit.SetWindowTextW(name);
	CString str;
	str.Format(_T("%f"), posX);
	m_posXEdit.SetWindowTextW(str);
	str.Format(_T("%f"), posY);
	m_posYEdit.SetWindowTextW(str);
	str.Format(_T("%d"), width);
	m_width.SetWindowTextW(str);
	str.Format(_T("%d"), height);
	m_height.SetWindowTextW(str);
	m_textureComboBox.SetCurSel(textureIndex);
}

void ObjectInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_nameEdit);
	DDX_Control(pDX, IDC_EDIT2, m_posXEdit);
	DDX_Control(pDX, IDC_EDIT3, m_posYEdit);
	DDX_Control(pDX, IDC_COMBO2, m_textureComboBox);
	DDX_Control(pDX, IDC_EDIT4, m_width);
	DDX_Control(pDX, IDC_EDIT5, m_height);
}


BEGIN_MESSAGE_MAP(ObjectInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ObjectInfoDlg::OnOkButton)
END_MESSAGE_MAP()


// ObjectInfoDlg 메시지 처리기


BOOL ObjectInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ObjectInfoDlg::OnOkButton()
{
	this->ShowWindow(SW_HIDE);
	::SendMessage(p_hwnd, INFO_DLG_OK_BUTTON,0,0);
}

CString ObjectInfoDlg::GetName()
{
	CString temp;
	m_nameEdit.GetWindowTextW(temp);
	return temp;
}

void ObjectInfoDlg::GetPos(float& x, float& y)
{
	CString temp;
	m_posXEdit.GetWindowTextW(temp);
	x = _tstof(temp);
	m_posYEdit.GetWindowTextW(temp);
	y = _tstof(temp);
}

void ObjectInfoDlg::GetSize(int& width, int& height)
{
	CString temp;
	m_width.GetWindowTextW(temp);
	width = _ttoi(temp);
	m_height.GetWindowTextW(temp);
	height = _ttoi(temp);
}

int ObjectInfoDlg::GetTextureIndex()
{
	return m_textureComboBox.GetCurSel();
}

void ObjectInfoDlg::AddTextureFile(CString file)
{
	m_textureComboBox.AddString(file);
}
