#pragma once


// ObjectInfoDlg 대화 상자

class ObjectInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ObjectInfoDlg)

public:
	ObjectInfoDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ObjectInfoDlg();
	void Init(CString name, float posX, float posY,int width,int height, int textureIndex);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_nameEdit;
	CEdit m_posXEdit;
	CEdit m_posYEdit;
	CEdit m_width;
	CEdit m_height;
	CComboBox m_textureComboBox;

	HWND p_hwnd = nullptr;

public:
	bool isCreateDlg = false;


	virtual BOOL OnInitDialog();
	afx_msg void OnOkButton();
	CString GetName();
	void GetPos(float& x, float& y);
	void GetSize(int& width, int& height);
	int GetTextureIndex();
	void SetParentHwnd(HWND hwnd) { p_hwnd = hwnd; }
	void AddTextureFile(CString file);

};
