#pragma once


// DlalogGenerateFindCode 对话框

class DlalogGenerateFindCode : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogGenerateFindCode)

public:
	DlalogGenerateFindCode(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogGenerateFindCode();
	HWND OperateHWND = NULL;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GENERATE_FIND_CODE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnIdok();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
