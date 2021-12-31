#pragma once


// DialogEditControl 对话框

class DlalogEditControl : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogEditControl)

public:
	DlalogEditControl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogEditControl();
	CEdit* OperateEdit = NULL;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIdok();
	afx_msg void OnBnClickedButtonEditTextSet();
	CEdit EditEditText;
	afx_msg void OnBnClickedButtonEditTextGet();
	afx_msg void OnBnClickedButtonEditSelect();
	afx_msg void OnBnClickedButtonEditCopy();
	afx_msg void OnBnClickedButtonEditCut();
	afx_msg void OnBnClickedButtonEditPaste();
	afx_msg void OnBnClickedButtonEditDelete();
	afx_msg void OnBnClickedButtonEditUndo();
	CEdit EditEditLimitTextLength;
	afx_msg void OnBnClickedButtonEditLimitSet();
};
