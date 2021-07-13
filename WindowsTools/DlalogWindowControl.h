#pragma once


// DialogWindowControl 对话框

class DlalogWindowControl : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogWindowControl)

public:
	DlalogWindowControl(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogWindowControl();
	CEdit* OperateEdit = NULL;
	void initData();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WINDOW_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL Unattended = FALSE;

	CMFCColorButton ColorTransparent;
	CSliderCtrl SliderTransparent;
	CButton CheckTransparentColor;
	CButton CheckTransparentAlpha;
	afx_msg
		//void DrowErrorCode(DWORD dwLastError);
	void OnBnClickedButtonTransparentGet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonTransparentSet();
	afx_msg void OnBnClickedCheckControlWsExLayered();
	CButton CheckControlWsExLayered;
};
