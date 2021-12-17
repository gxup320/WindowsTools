#pragma once


// DialogSelectWindow 对话框

class DlalogSelectWindow : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogSelectWindow)

public:
	DlalogSelectWindow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogSelectWindow();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT_WINDOW };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDC* pDC;
	HANDLE hThread_MarkWindows = NULL;
	BOOL ALL_EXITING = FALSE;

	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual BOOL DestroyWindow();
};
