#pragma once


// DlalogSendMessage 对话框

class DlalogSendMessage : public CDialogEx
{
	DECLARE_DYNAMIC(DlalogSendMessage)

public:
	DlalogSendMessage(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlalogSendMessage();
	HWND OperateHWND = NULL;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEND_MESSAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	CEdit EditHwnd;

	CEdit* mDemoEdit = NULL;
	CStatic* mDemoStatic = NULL;
	CComboBox* mDemoComboBox = NULL;

//	afx_msg void OnEnChangeSmsgEditHwnd();
	//CEdit EditClassName;
	//CComboBox ComboWindowType;
	CComboBox ComboMessage;
	tag_WINDOW_TYPE_LIST ControlType = { 0 };
	//afx_msg void OnCbnSelchangeSmsgComboWindowType();
	afx_msg void OnCbnSelchangeSmsgComboMessage();

	void DrowErrorCode(DWORD dwLastError, CStatic& _Static);

	CButton ButtonSend;
	afx_msg void OnBnClickedSmsgButtonSend();
	afx_msg void OnEnChangeSmsgEditHwnd();
	CEdit EditClassName;
	CComboBox ComboWindowType;
	afx_msg void OnCbnSelchangeSmsgComboWindowType();
	CStatic StaticWindowHandle;
	CStatic StaticWindowClassName;
	CStatic StaticWindowType;
	CStatic StaticMessage;
};
