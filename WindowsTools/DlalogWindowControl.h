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
	void moveLock(int x, int y);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WINDOW_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL Unattended = FALSE;
	int MoveLockX = 0;
	int MoveLockY = 0;
	BOOL MoveLockAutoing = FALSE;

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
	CEdit EditWindowControlMoveLeft;
	CEdit EditWindowControlMoveRight;
	CEdit EditWindowControlMoveTop;
	CEdit EditWindowControlMoveBottom;
	afx_msg void OnBnClickedButtonMoveGet();
	afx_msg void OnBnClickedButtonMoveSet();
	CButton CheckMoveRepaint;
	CButton CheckWindowControlMoveLock;
	afx_msg void OnEnChangeEditWindowControlMoveLeft();
	afx_msg void OnEnChangeEditWindowControlMoveRight();
	afx_msg void OnEnChangeEditWindowControlMoveTop();
	afx_msg void OnEnChangeEditWindowControlMoveBottom();
};
