#pragma once


// DlalogCodeView 对话框

class DlalogCodeView : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogCodeView)

public:
	DlalogCodeView(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogCodeView();
	const CString *Codes;
	const CString *Titles;
	int CodesNumber = 0;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CODEVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox ComboSolution;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboSolution();
	void WriteHTMLcode(LPCTSTR html);
};
