#pragma once



// ListBoxFormView 폼 보기
class DirectXView;
class ObjectInfoDlg;

class ListBoxFormView : public CFormView
{
	DECLARE_DYNCREATE(ListBoxFormView)

protected:
	ListBoxFormView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ListBoxFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnDestroy();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void AddTextureFileButton();
	virtual void OnInitialUpdate();
	void ChangeSelectedObject();
	void OpenObjectInfoDlg();
	void ApplyObjectInfo();
private:
	CListBox m_listBox1;
	DirectXView* p_dView = nullptr;
	CListBox m_textureListbox;

	ObjectInfoDlg* m_infoDlg = nullptr;


protected:
	afx_msg LRESULT OnInfoDlgOkButton(WPARAM wParam, LPARAM lParam);
};


