
// WindowsToolsDlg.h: 头文件
//

#pragma once

#include "DlalogSelectWindow.h"

typedef LONG  NTSTATUS;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemProcessInformation = 0x5
} SYSTEM_INFORMATION_CLASS, * PSYSTEM_INFORMATION_CLASS;

typedef NTSTATUS(WINAPI* tagZwQuerySystemInformation)(
	_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
	);

typedef struct _SYSTEM_PROCESS_INFORMATION {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	BYTE Reserved1[48];
	PVOID Reserved2[3];
	HANDLE UniqueProcessId;
	PVOID Reserved3;
	ULONG HandleCount;
	BYTE Reserved4[4];
	PVOID Reserved5[11];
	SIZE_T PeakPagefileUsage;
	SIZE_T PrivatePageCount;
	LARGE_INTEGER Reserved6[6];
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;


// CWindowsToolsDlg 对话框
class CWindowsToolsDlg : public CDialogEx
{
// 构造
public:
	CWindowsToolsDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDOWSTOOLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CImageList *m_image = NULL;
	CImageList* m_show_image = NULL;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void addWindowToTree(CTreeCtrl* ptree, HWND hWnd, HTREEITEM f, CImageList* image, HWND fhWnd, int* number);
	//int GetControlTypeID(HWND hWnd, CString ClassName);
	void GetWindowInfoToWindow(HWND hWnd);
	friend DWORD ProgressRefresh(CWindowsToolsDlg* ToolsDlg);
	friend DWORD RefreshWindowsTree(CWindowsToolsDlg* ToolsDlg);
	BOOL SetTreeViewSelect(HTREEITEM RootItemHandle, HWND hWnd);
	void SetTreeViewBold(HTREEITEM RootItemHandle, HWND hWnd);
	void SetTreeViewBoldSelect(HTREEITEM RootItemHandle, HWND hWnd);
	void GetWindowRectToWindow(HWND hWnd, HWND ParenthWnd, HWND _Static = NULL);
	void MoveWindowFromWindow(HWND Static, BOOL Relative = FALSE);

	tag_WINDOW_TYPE_LIST IconStruct;
	int IconStructSum;
	CDC* WindowSelectUI;
	int WindowSelectStatus;
	HCURSOR CursorWindowSelect;
	HCURSOR CursorDefault;
	DlalogSelectWindow *m_DialogSelectWindow = NULL;
	BOOL EditWindowHandleDECEditing = FALSE;
	BOOL EditWindowHandleHEXEditing = FALSE;
	BOOL EditRelevantMessage = TRUE;
	CMenu menu;
	CMenu* pSysMenu = NULL;
	ITaskbarList3* m_pTaskBarlist = NULL;
	int Progress_MAX = 0;
	int Progress_POS = 0;
	int Progress_SUM = 0;
	BOOL Progress_ON = FALSE;
	int WindowClosing = 0;
	HANDLE hThread_ProgressRefresh = NULL;
	HANDLE hThread_RefreshWindowsTree = NULL;
	int WindowsTreeLeft = 0;
	BOOL GetHideWindowTemp = FALSE;
	CRect ClassNameEdirtRect;
	
	afx_msg void OnBnClickedButtonRefreshWindowsTree();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CButton ShowHideWindows;
	CButton ShowHideChildWindows;
	CEdit EditWindowHandleDEC;
	CEdit EditWindowHandleHEX;
	CEdit EditParentWindowHandle;
	CEdit EditWindowText;
	CEdit EditWindowClassName;
	CEdit EditWindowControlID;
	CEdit EditThreadHandle;
	CEdit EditProcessID;
	CEdit EditParentProcessID;
	CEdit EditProcessPath;
	CEdit EditProcessName;
	afx_msg void OnTvnSelchangedTreeWindowsTree(NMHDR* pNMHDR, LRESULT* pResult);
	CTreeCtrl TreeWindowsTreeCtrl;
	CString StaticProcessWOW;
	CString StaticParentProcessWOW;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	CEdit EditWindowRectLeft;
	CEdit EditWindowRectRight;
	CEdit EditWindowRectTop;
	CEdit EditWindowRectBottom;
	CEdit EditWindowRelativeRectLeft;
	CEdit EditWindowRelativeRectTop;
	afx_msg void OnEnChangeEditWindowHandleDec();
	afx_msg void OnEnChangeEditWindowHandleHex();
	afx_msg void OnEnKillfocusEditParentWindowHandle();
	afx_msg void OnEnChangeEditWindowText();
	CEdit EditWindowWidth;
	CEdit EditWindowHigth;
	afx_msg void OnEnChangeEditWindowRectLeft();
	afx_msg void OnEnChangeEditWindowRectRight();
	afx_msg void OnEnChangeEditWindowRectTop();
	afx_msg void OnEnChangeEditWindowRectBottom();
	afx_msg void OnEnChangeEditWindowRelatveRectLeft();
	afx_msg void OnEnChangeEditWindowRelatveRectTop();
	afx_msg void OnEnChangeEditWindowWidth();
	afx_msg void OnEnChangeEditWindowHigth();
	CComboBox ComboSpecifiesShow;
	afx_msg void OnCbnSelchangeComboSpecifiesShown();
	virtual void OnOK();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWindowRefreshWindowTree();
	void SetWindowShowText();
	afx_msg void OnNMRClickTreeWindowsTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFileExit();
	afx_msg void OnWindowHighlight();
	afx_msg void OnWindowSendMessage();
//	afx_msg void OnAppCommand(CWnd* pWnd, UINT nCmd, UINT nDevice, UINT nKey);
protected:
public:
	CProgressCtrl ProcessWindowsRefresh;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	afx_msg void OnWindowGenerateFindCode();
	afx_msg void OnWindowControlWindow();
	CEdit EditWindowStyle;
	CEdit EditWindowStyleEx;
	afx_msg void OnEnKillfocusEditWindowStyle();
	afx_msg void OnEnKillfocusEditWindowStyleEx();
	afx_msg void OnBnClickedButtonWindowStyleAdvanced();
	afx_msg void OnWindowGenerateFindCodeFast();
	afx_msg void OnEnChangeEditWindowStyle();
	CButton CheckDisabled;
	CStatic StaticWindowNmuber;
	afx_msg void OnBnClickedCheckDisabled();
	afx_msg void OnDestroy();

	CButton ReadFileIcon;
	afx_msg void OnBnClickedCheckShowHideWindows();
	afx_msg void OnBnClickedCheckShowHideChildWindows();
	afx_msg void OnBnClickedCheckReadFileIcon();
	CButton GetHideWindow;
	afx_msg void OnBnClickedCheckGetHideWindow();
	CEdit EditWindowClassName_1;
};
