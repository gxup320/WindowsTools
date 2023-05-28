
// WindowsToolsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "WindowsTools.h"
#include "WindowsToolsDlg.h"
#include "afxdialogex.h"
#include "Language.h"
#include "DlalogSendMessage.h"
#include <tlhelp32.h>
#include "DlalogGenerateFindCode.h"
#include "DlalogControl.h"
#include "DlalogWindowStyle.h"
#include "DlalogCodeView.h"

HMODULE hDll_Ntdll = LoadLibrary(TEXT("Ntdll.dll"));
tagZwQuerySystemInformation ZwQuerySystemInformation = (tagZwQuerySystemInformation)GetProcAddress(hDll_Ntdll, "ZwQuerySystemInformation");
HWND MarkWindowHwnd = NULL;
HWND SelectWindowHwnd = NULL;
HTREEITEM SelectWindowItam = NULL;
#pragma comment(lib,"Version.lib")
CString G_ReadPrivateProfileString(CString FileName, CString AppName, CString KeyName, CString Default);
BOOL G_WritePrivateProfileString(CString FileName, CString AppName, CString KeyName, CString String);


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
//	virtual void OnOK();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWindowsToolsDlg 对话框



CWindowsToolsDlg::CWindowsToolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWSTOOLS_DIALOG, pParent)
	, StaticProcessWOW(_T(""))
	, StaticParentProcessWOW(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindowsToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SHOW_HIDE_WINDOWS, ShowHideWindows);
	DDX_Control(pDX, IDC_CHECK_SHOW_HIDE_CHILD_WINDOWS, ShowHideChildWindows);
	DDX_Control(pDX, IDC_EDIT_WINDOW_HANDLE_DEC, EditWindowHandleDEC);
	DDX_Control(pDX, IDC_EDIT_WINDOW_HANDLE_HEX, EditWindowHandleHEX);
	DDX_Control(pDX, IDC_EDIT_PARENT_WINDOW_HANDLE, EditParentWindowHandle);
	DDX_Control(pDX, IDC_EDIT_WINDOW_TEXT, EditWindowText);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CLASS_NAME, EditWindowClassName);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CONTROL_ID, EditWindowControlID);
	DDX_Control(pDX, IDC_EDIT_THREAD_HANDLE, EditThreadHandle);
	DDX_Control(pDX, IDC_EDIT_PROCESS_ID, EditProcessID);
	DDX_Control(pDX, IDC_EDIT_PARENT_PROCESS_ID, EditParentProcessID);
	DDX_Control(pDX, IDC_EDIT_PROCESS_PATH, EditProcessPath);
	DDX_Control(pDX, IDC_EDIT_PROCESS_NAME, EditProcessName);
	DDX_Control(pDX, IDC_TREE_WINDOWS_TREE, TreeWindowsTreeCtrl);
	DDX_Text(pDX, IDC_STATIC_PROCESS_WOW, StaticProcessWOW);
	DDX_Text(pDX, IDC_STATIC_PARENT_PROCESS_WOW, StaticParentProcessWOW);
	DDX_Control(pDX, IDC_EDIT_WINDOW_RECT_LEFT, EditWindowRectLeft);
	DDX_Control(pDX, IDC_EDIT_WINDOW_RECT_RIGHT, EditWindowRectRight);
	DDX_Control(pDX, IDC_EDIT_WINDOW_RECT_TOP, EditWindowRectTop);
	DDX_Control(pDX, IDC_EDIT_WINDOW_RECT_BOTTOM, EditWindowRectBottom);
	DDX_Control(pDX, IDC_EDIT_WINDOW_RELATVE_RECT_LEFT, EditWindowRelativeRectLeft);
	DDX_Control(pDX, IDC_EDIT_WINDOW_RELATVE_RECT_TOP, EditWindowRelativeRectTop);
	DDX_Control(pDX, IDC_EDIT_WINDOW_WIDTH, EditWindowWidth);
	DDX_Control(pDX, IDC_EDIT_WINDOW_HIGTH, EditWindowHigth);
	DDX_Control(pDX, IDC_COMBO_SPECIFIES_SHOWN, ComboSpecifiesShow);
	DDX_Control(pDX, IDC_PROGRESS_WINDOWS_REFRESH, ProcessWindowsRefresh);
	DDX_Control(pDX, IDC_EDIT_WINDOW_STYLE, EditWindowStyle);
	DDX_Control(pDX, IDC_EDIT_WINDOW_STYLE_EX, EditWindowStyleEx);
	DDX_Control(pDX, IDC_CHECK_DISABLED, CheckDisabled);
	DDX_Control(pDX, IDC_STATIC_WINDOWS_NUMBER, StaticWindowNmuber);
	DDX_Control(pDX, IDC_CHECK_READ_FILE_ICON, ReadFileIcon);
	DDX_Control(pDX, IDC_CHECK_GET_HIDE_WINDOW, GetHideWindow);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CLASS_NAME_1, EditWindowClassName_1);
}

BEGIN_MESSAGE_MAP(CWindowsToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH_WINDOWS_TREE, &CWindowsToolsDlg::OnBnClickedButtonRefreshWindowsTree)
	ON_WM_SIZE()
ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_WINDOWS_TREE, &CWindowsToolsDlg::OnTvnSelchangedTreeWindowsTree)
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_CLOSE()
ON_EN_CHANGE(IDC_EDIT_WINDOW_HANDLE_DEC, &CWindowsToolsDlg::OnEnChangeEditWindowHandleDec)
ON_EN_CHANGE(IDC_EDIT_WINDOW_HANDLE_HEX, &CWindowsToolsDlg::OnEnChangeEditWindowHandleHex)
ON_EN_KILLFOCUS(IDC_EDIT_PARENT_WINDOW_HANDLE, &CWindowsToolsDlg::OnEnKillfocusEditParentWindowHandle)
ON_EN_CHANGE(IDC_EDIT_WINDOW_TEXT, &CWindowsToolsDlg::OnEnChangeEditWindowText)
ON_EN_CHANGE(IDC_EDIT_WINDOW_RECT_LEFT, &CWindowsToolsDlg::OnEnChangeEditWindowRectLeft)
ON_EN_CHANGE(IDC_EDIT_WINDOW_RECT_RIGHT, &CWindowsToolsDlg::OnEnChangeEditWindowRectRight)
ON_EN_CHANGE(IDC_EDIT_WINDOW_RECT_TOP, &CWindowsToolsDlg::OnEnChangeEditWindowRectTop)
ON_EN_CHANGE(IDC_EDIT_WINDOW_RECT_BOTTOM, &CWindowsToolsDlg::OnEnChangeEditWindowRectBottom)
ON_EN_CHANGE(IDC_EDIT_WINDOW_RELATVE_RECT_LEFT, &CWindowsToolsDlg::OnEnChangeEditWindowRelatveRectLeft)
ON_EN_CHANGE(IDC_EDIT_WINDOW_RELATVE_RECT_TOP, &CWindowsToolsDlg::OnEnChangeEditWindowRelatveRectTop)
ON_EN_CHANGE(IDC_EDIT_WINDOW_WIDTH, &CWindowsToolsDlg::OnEnChangeEditWindowWidth)
ON_EN_CHANGE(IDC_EDIT_WINDOW_HIGTH, &CWindowsToolsDlg::OnEnChangeEditWindowHigth)
ON_CBN_SELCHANGE(IDC_COMBO_SPECIFIES_SHOWN, &CWindowsToolsDlg::OnCbnSelchangeComboSpecifiesShown)
//ON_WM_APPCOMMAND()
ON_COMMAND(ID_WINDOW_REFRESH_WINDOW_TREE, &CWindowsToolsDlg::OnWindowRefreshWindowTree)
ON_NOTIFY(NM_RCLICK, IDC_TREE_WINDOWS_TREE, &CWindowsToolsDlg::OnNMRClickTreeWindowsTree)
ON_COMMAND(ID_FILE_EXIT, &CWindowsToolsDlg::OnFileExit)
ON_COMMAND(ID_WINDOW_HIGHLIGHT, &CWindowsToolsDlg::OnWindowHighlight)
ON_COMMAND(ID_WINDOW_SEND_MESSAGE, &CWindowsToolsDlg::OnWindowSendMessage)
//ON_WM_APPCOMMAND()
ON_WM_TIMER()
ON_WM_SETFOCUS()
ON_WM_CREATE()
ON_COMMAND(ID_WINDOW_GENERATE_FIND_CODE, &CWindowsToolsDlg::OnWindowGenerateFindCode)
ON_COMMAND(ID_WINDOW_CONTROL_WINDOW, &CWindowsToolsDlg::OnWindowControlWindow)
ON_EN_KILLFOCUS(IDC_EDIT_WINDOW_STYLE, &CWindowsToolsDlg::OnEnKillfocusEditWindowStyle)
ON_EN_KILLFOCUS(IDC_EDIT_WINDOW_STYLE_EX, &CWindowsToolsDlg::OnEnKillfocusEditWindowStyleEx)
ON_BN_CLICKED(IDC_BUTTON_WINDOW_STYLE_ADVANCED, &CWindowsToolsDlg::OnBnClickedButtonWindowStyleAdvanced)
ON_COMMAND(ID_WINDOW_GENERATE_FIND_CODE_FAST, &CWindowsToolsDlg::OnWindowGenerateFindCodeFast)
ON_EN_CHANGE(IDC_EDIT_WINDOW_STYLE, &CWindowsToolsDlg::OnEnChangeEditWindowStyle)
ON_BN_CLICKED(IDC_CHECK_DISABLED, &CWindowsToolsDlg::OnBnClickedCheckDisabled)
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_CHECK_SHOW_HIDE_WINDOWS, &CWindowsToolsDlg::OnBnClickedCheckShowHideWindows)
ON_BN_CLICKED(IDC_CHECK_SHOW_HIDE_CHILD_WINDOWS, &CWindowsToolsDlg::OnBnClickedCheckShowHideChildWindows)
ON_BN_CLICKED(IDC_CHECK_READ_FILE_ICON, &CWindowsToolsDlg::OnBnClickedCheckReadFileIcon)
ON_BN_CLICKED(IDC_CHECK_GET_HIDE_WINDOW, &CWindowsToolsDlg::OnBnClickedCheckGetHideWindow)
END_MESSAGE_MAP()



// CWindowsToolsDlg 消息处理程序

BOOL CWindowsToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, AllLanguage->GetLanguageStruct()->SYSMENU_ABOUTBOX);
	}
	CMenu* subMenu;
	menu.LoadMenu(IDR_MENU_HOME);
	SetMenu(&menu);

	subMenu = menu.GetSubMenu(2);//获取第三个菜单
	const std::vector<LanguageStruct>* LanguageList = AllLanguage->GetLanguageList();
	if (LanguageList->size() != 0)
	{
		subMenu->DeleteMenu(0, MF_BYPOSITION);

		for (std::vector<LanguageStruct>::const_iterator iter = LanguageList->cbegin(); iter != LanguageList->cend(); iter++)
		{
			subMenu->AppendMenu(MF_STRING, iter->LangID + 10000, iter->LANGUAGE);
		}
		
	}

	

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码


	WindowSelectUI = GetDC();
	WindowSelectStatus = IDB_BITMAP_FREE;
	CursorWindowSelect = AfxGetApp()->LoadCursor(IDC_CURSOR_WINDOW_SELECT);
	CursorDefault = LoadCursor(NULL, IDC_ARROW);
	m_DialogSelectWindow = new DlalogSelectWindow;
	m_DialogSelectWindow->Create(IDD_DIALOG_SELECT_WINDOW, this);
	ComboSpecifiesShow.AddString(_T("SW_HIDE"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWNORMAL/SW_NORMAL"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWMINIMIZED"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWMAXIMIZED/SW_MAXIMIZE"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWNOACTIVATE"));
	ComboSpecifiesShow.AddString(_T("SW_SHOW"));
	ComboSpecifiesShow.AddString(_T("SW_MINIMIZE"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWMINNOACTIVE"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWNA"));
	ComboSpecifiesShow.AddString(_T("SW_RESTORE"));
	ComboSpecifiesShow.AddString(_T("SW_SHOWDEFAULT"));
	ComboSpecifiesShow.AddString(_T("SW_FORCEMINIMIZE/SW_MAX"));

	//Set language
	SetWindowShowText();

	if (G_ReadPrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ShowHideWindows"), _T("FALSE")) == "TRUE")
	{
		ShowHideWindows.SetCheck(BST_CHECKED);
	}
	if (G_ReadPrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ShowHideChildWindows"), _T("TRUE")) == "TRUE")
	{
		ShowHideChildWindows.SetCheck(BST_CHECKED);
	}
	if (G_ReadPrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ReadFileIcon"), _T("TRUE")) == "TRUE")
	{
		ReadFileIcon.SetCheck(BST_CHECKED);
	}
	if (G_ReadPrivateProfileString(_T("./config.ini"), _T("SniffingWindow"), _T("GetHideWindow"), _T("FALSE")) == "TRUE")
	{
		GetHideWindow.SetCheck(BST_CHECKED);
	}
	hThread_ProgressRefresh = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProgressRefresh, this, 0, NULL);
	
	CRect treeRect;
	GetDlgItem(IDC_TREE_WINDOWS_TREE)->GetWindowRect(&treeRect);
	ScreenToClient(&treeRect);
	WindowsTreeLeft = treeRect.left;
	EditWindowClassName.GetWindowRect(&ClassNameEdirtRect);
	ScreenToClient(&ClassNameEdirtRect);


	OnBnClickedButtonRefreshWindowsTree();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWindowsToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWindowsToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		// load IDB_BITMAP1 from our resources
		CBitmap bmp;
		if (bmp.LoadBitmap(WindowSelectStatus))
		{
			CDC dcMemory;
			dcMemory.CreateCompatibleDC(WindowSelectUI);

			CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);

			WindowSelectUI->BitBlt(30, 30, 31, 28, &dcMemory,
				0, 0, SRCCOPY);
			dcMemory.SelectObject(pOldBitmap);
		}
		else
		{
			TRACE0("ERROR: Where's IDB_BITMAP1?\n");
		}
	}


}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWindowsToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString GetProcessPath(DWORD PID)
{
	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	if (hProcess == INVALID_HANDLE_VALUE)
	{
		return CString(_T(""));
	}
	MODULEENTRY32 mode;
	mode.dwSize = sizeof(mode);
	Module32First(hProcess, &mode);
	CString path = mode.szExePath;
	CloseHandle(hProcess);
	return path;
}


void CWindowsToolsDlg::addWindowToTree(CTreeCtrl* ptree, HWND hWnd, HTREEITEM f, CImageList* image, HWND fhWnd, int* number)
{
	HICON hicon = NULL;
	CString str;
	TCHAR ClassName[51] = { 0 };
	::RealGetWindowClass(hWnd, ClassName, 50);
	int WindowTextLength = ::GetWindowTextLength(hWnd) + 1;
	LPTSTR WindowText = new TCHAR[WindowTextLength];
	::GetWindowText(hWnd, WindowText, WindowTextLength);
#ifdef _WIN64
	str.Format(_T("%llu"), hWnd);
#else
	str.Format(_T("%u"), hWnd);
#endif // _WIN64

	
	str = str + _T("|") + ClassName + _T("|") + WindowText;
	delete[] WindowText;
	int i;
	BOOL swshow = ::IsWindowVisible(hWnd);
	if ((swshow == FALSE && ShowHideWindows.GetCheck() == BST_UNCHECKED && f == ptree->GetRootItem()) ||
		(swshow == FALSE && ShowHideChildWindows.GetCheck() == BST_UNCHECKED && f != ptree->GetRootItem()))
	{
		return;
	}
	//if (hWnd == ::GetDesktopWindow())
	//{
	//	i = IconStruct.DESKTOP;
	//}
	//else
	{
#ifdef _WIN64
		hicon = (HICON)::GetClassLongA(hWnd, GCLP_HICONSM);
#else /* _WIN64 */
		hicon = (HICON)::GetClassLongA(hWnd, GCL_HICONSM);
#endif /* _WIN64 */
		if (hicon != NULL)
		{
			i = image->Add(hicon);
		}
		else
		{
			LRESULT re = ::SendMessageTimeout(hWnd, WM_GETICON, ICON_SMALL2, 0, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 10, (PDWORD_PTR)&hicon);
			if (re && hicon != NULL)
			{
				i = image->Add(hicon);
			}
			else if (fhWnd == ::GetDesktopWindow())
			{
				if (ReadFileIcon.GetCheck() == BST_CHECKED)
				{
					DWORD PID;
					::GetWindowThreadProcessId(hWnd, &PID);
					if (PID != 0)
					{
						//SHFILEINFO sIcon;
						hicon = ::ExtractIcon(AfxGetInstanceHandle(), GetProcessPath(PID), 0);
						if (hicon != NULL)
						{
							i = image->Add(hicon);
							DestroyIcon(hicon);
						}
						else
						{
							i = IconStruct.PROCESS;
						}
					}
					else
					{
						i = IconStruct.PROCESS;
					}
				}
				else
				{
					i = IconStruct.PROCESS;
				}
			}
			else
			{
				//根据类名使用图标
				i = GetControlTypeID(hWnd, ClassName,IconStruct);
			}
		}
	}
	(*number)++;
	HTREEITEM hitem;
	//if (hWnd == ::GetDesktopWindow())
	//{
	//	hitem = ptree->InsertItem(AllLanguage->GetLanguageStruct()->DIALOG_TREE_LOADING, i, i, f, TVI_LAST);
	//}
	//else
	{
		hitem = ptree->InsertItem(str, i, i, f, TVI_LAST);
	}
	ptree->SetItemData(hitem, (DWORD_PTR)hWnd);
	int cItemState = NULL;

	if (swshow == FALSE)
	{
		cItemState |= TVIS_CUT;
	}
	if (hWnd == MarkWindowHwnd)
	{
		cItemState |= TVIS_BOLD;
	}
	if (hWnd == SelectWindowHwnd)
	{
		SelectWindowItam = hitem;
	}
	ptree->SetItem(hitem, TVIF_STATE, str, 0, 0, cItemState, TVIS_CUT | TVIS_BOLD, NULL);
	//TRACE(_T("%Ts\n"), str);
	HWND m_hwnd = ::GetWindow(hWnd, GW_CHILD);
	while (m_hwnd != NULL)
	{
		addWindowToTree(ptree, m_hwnd, hitem, image, hWnd, number);
		m_hwnd = ::GetWindow(m_hwnd, GW_HWNDNEXT);
	}
	//if (hWnd == ::GetDesktopWindow())
	//{
	//	ptree->SetItem(hitem, TVIF_TEXT, str, 0, 0, NULL, NULL, NULL);
	//	ptree->Expand(hitem, TVE_EXPAND);
	//}

}

DWORD ProgressRefresh(CWindowsToolsDlg* ToolsDlg)
{
	int Progress_MAX = 0;
	int Progress_POS = 0;
	int Progress_SUM = 0;
	BOOL Progress_ON = FALSE;
	HWND ToolsDlgHwnd = ToolsDlg->m_hWnd;
	while (ToolsDlg->WindowClosing == 0)
	{
		if (Progress_ON != ToolsDlg->Progress_ON)
		{
			Progress_ON = ToolsDlg->Progress_ON;
			if (Progress_ON)
			{
				if (ToolsDlg->m_pTaskBarlist != NULL)
				{
					ToolsDlg->m_pTaskBarlist->SetProgressState(ToolsDlg->m_hWnd, TBPF_INDETERMINATE);
					ToolsDlg->m_pTaskBarlist->SetProgressValue(ToolsDlg->m_hWnd, 0, 0);
				}
			}
			else
			{
				if (ToolsDlg->m_pTaskBarlist != NULL)
				{
					ToolsDlg->m_pTaskBarlist->SetProgressState(ToolsDlg->m_hWnd, TBPF_NOPROGRESS);
				}
			}
		}
		if (Progress_POS != ToolsDlg->Progress_POS)
		{
			Progress_POS = ToolsDlg->Progress_POS;
			ToolsDlg->ProcessWindowsRefresh.SetPos(Progress_POS);
			if (ToolsDlg->m_pTaskBarlist != NULL && Progress_ON)
			{
				ToolsDlg->m_pTaskBarlist->SetProgressValue(ToolsDlg->m_hWnd, Progress_POS, Progress_MAX);
			}
		}
		if (Progress_MAX != ToolsDlg->Progress_MAX)
		{
			Progress_MAX = ToolsDlg->Progress_MAX;
			ToolsDlg->ProcessWindowsRefresh.SetRange(0, Progress_MAX);
		}
		if (Progress_SUM != ToolsDlg->Progress_SUM)
		{
			Progress_SUM = ToolsDlg->Progress_SUM;
			CString tempString;
			tempString.Format(_T("%d"), Progress_SUM);
			ToolsDlg->StaticWindowNmuber.SetWindowText(tempString);
		}
		Sleep(100);
	}
	ToolsDlg->WindowClosing++;
	return 0;
}

DWORD RefreshWindowsTree(CWindowsToolsDlg* ToolsDlg)
{
	CTreeCtrl* ptree = (CTreeCtrl*)ToolsDlg->GetDlgItem(IDC_TREE_WINDOWS_TREE);
	ptree->DeleteAllItems();
// 	CImageList* temp_image = new CImageList;
// 	temp_image->Create(16, 16, ILC_COLOR32 | ILC_MASK, ToolsDlg->IconStructSum, ToolsDlg->IconStructSum);
// 	for (int i = 0; i < ToolsDlg->IconStructSum; i++)
// 	{
// 		ToolsDlg->m_image.Copy(i, temp_image, i);
// 	}
// 	
// 	ptree->SetImageList(temp_image, TVSIL_NORMAL);
// 	if (ToolsDlg->m_show_image != NULL)
// 	{
// 		delete ToolsDlg->m_show_image;
// 	}
//	ToolsDlg->m_show_image = temp_image;

	if (ToolsDlg->m_image != NULL)
	{
		ToolsDlg->m_image->DeleteImageList();
		delete ToolsDlg->m_image;
	}
	ToolsDlg->m_image = new CImageList;
	//初始化图片组
	ToolsDlg->m_image->Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 0);
	ToolsDlg->IconStruct.STATIC = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_STATIC));
	ToolsDlg->IconStruct.COMPUTER = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_COMPUTER));
	ToolsDlg->IconStruct.CR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_CR));
	ToolsDlg->IconStruct.DESKTOP = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_DESKTOP));
	ToolsDlg->IconStruct.EDIT = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_EDIT));
	//ToolsDlg->IconStruct.LINK = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_LINK));
	ToolsDlg->IconStruct.MENU = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_MENU));
	ToolsDlg->IconStruct.MFC = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_MFC));
	ToolsDlg->IconStruct.PROCESS = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_PROCESS));
	ToolsDlg->IconStruct.PROGRESSBAR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_PROGRESSBAR));
	ToolsDlg->IconStruct.WINDOW = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_WINDOW));
	ToolsDlg->IconStruct.SYSTABCONTROL32 = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_SYSTABCONTROL32));
	ToolsDlg->IconStruct.GROUPBOX = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_GROUPBOX));
	ToolsDlg->IconStruct.CHECKBOX = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_CHECKBOX));
	ToolsDlg->IconStruct.RADIOBUTTON = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_RADIOBUTTON));
	ToolsDlg->IconStruct.BUTTON = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_BUTTON));
	ToolsDlg->IconStruct.SYSLINK = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_SYSLINK));
	ToolsDlg->IconStruct.SYSLISTVIEW32 = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_SYSLISTVIEW32));
	ToolsDlg->IconStruct.SYSHEADER32 = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_SYSHEADER32));
	ToolsDlg->IconStruct.SCROLLBAR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_SCROLLBAR));
	ToolsDlg->IconStruct.SYSTREEVIEW32 = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_SYSTREEVIEW32));
	ToolsDlg->IconStruct.STATUSBAR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_STATUSBAR));
	ToolsDlg->IconStruct.COMBOBOX = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_COMBOBOX));
	ToolsDlg->IconStruct.TRACKBAR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_TRACKBAR));
	ToolsDlg->IconStruct.UPDOWN32 = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_UPDOWN32));
	ToolsDlg->IconStruct.LISTBOX = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_LISTBOX));
	ToolsDlg->IconStruct.TOOLBAR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_TOOLBAR));
	ToolsDlg->IconStruct.MDI = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_MDI));
	ToolsDlg->IconStruct.DATA_TIME = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_DATA_TIME));
	ToolsDlg->IconStruct.ANIMATION = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_ANIMATION));
	ToolsDlg->IconStruct.HOT_KEY = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_HOT_KEY));
	ToolsDlg->IconStruct.IP_ADDRESS = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_IP_ADDRESS));
	ToolsDlg->IconStruct.MONTH_CALENDAR = ToolsDlg->m_image->Add(AfxGetApp()->LoadIcon(IDI_ICON_MONTH_CALENDAR));
	ToolsDlg->IconStructSum = ToolsDlg->IconStruct.MONTH_CALENDAR + 1;
	ptree->SetImageList(ToolsDlg->m_image, TVSIL_NORMAL);

// 	for (int i = 10000; i >= ToolsDlg->IconStructSum; i--)
// 	{
// 		ToolsDlg->m_image.Remove(i);
// 	}
	CString TempString;
	ToolsDlg->EditWindowHandleDEC.GetWindowText(TempString);
#ifdef _WIN64
	SelectWindowHwnd = (HWND)_ttoll(TempString);
#else
	SelectWindowHwnd = (HWND)_ttoi(TempString);
#endif // _WIN64

	SelectWindowItam = NULL;
	// Initialize the pointer. You can also do this in the constructor.
	// Remember to release after use
// 	if (ToolsDlg->m_pTaskBarlist == NULL)
// 	{
// 		CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&ToolsDlg->m_pTaskBarlist);
// 	}
	//if (ToolsDlg->m_pTaskBarlist != NULL)
	//{
	//	ToolsDlg->m_pTaskBarlist->SetProgressState(ToolsDlg->m_hWnd, TBPF_INDETERMINATE);
	//	ToolsDlg->m_pTaskBarlist->SetProgressValue(ToolsDlg->m_hWnd, 0, 0);
	//}
	ToolsDlg->Progress_ON = TRUE;
	//ToolsDlg->ProcessWindowsRefresh.SetPos(0);
	ToolsDlg->Progress_POS = 0;
	HWND hWnd = ::GetDesktopWindow();
	std::vector<HWND> hWndList;
	HWND tHwnd = GetWindow(hWnd, GW_CHILD);

	HTREEITEM hitem = ptree->InsertItem(AllLanguage->GetLanguageStruct()->DIALOG_TREE_LOADING, ToolsDlg->IconStruct.DESKTOP, ToolsDlg->IconStruct.DESKTOP, 0, TVI_LAST);
	while (tHwnd != NULL)
	{
		hWndList.push_back(tHwnd);
		tHwnd = GetWindow(tHwnd, GW_HWNDNEXT);
	}

	//ToolsDlg->ProcessWindowsRefresh.SetRange(0,(short)hWndList.size());
	ToolsDlg->Progress_MAX = hWndList.size();
	//if (ToolsDlg->m_pTaskBarlist != NULL)
	//{
	//	ToolsDlg->m_pTaskBarlist->SetProgressValue(ToolsDlg->m_hWnd, 0, hWndList.size());
	//}
	for (int i = 0, number = 0; i < hWndList.size() && ToolsDlg->WindowClosing == 0; i++)
	{
		ToolsDlg->addWindowToTree(ptree, hWndList[i], hitem, ToolsDlg->m_image, hWnd, &number);
		//ToolsDlg->ProcessWindowsRefresh.SetPos(i + 1);
		ToolsDlg->Progress_POS = i + 1;
		//CString tempString;
		//tempString.Format(_T("%d"), number);
		//ToolsDlg->StaticWindowNmuber.SetWindowText(tempString);
		ToolsDlg->Progress_SUM = number;
		//if (ToolsDlg->m_pTaskBarlist != NULL)
		//{
		//	ToolsDlg->m_pTaskBarlist->SetProgressValue(ToolsDlg->m_hWnd, i + 1, hWndList.size());
		//}
	}
	CString ClassName;
	::RealGetWindowClass(hWnd, ClassName.GetBuffer(100), 100);
	ClassName.ReleaseBuffer();
	CString tempString;
	tempString.Format(_T("%u"), (size_t)hWnd);
	tempString = tempString + _T("|") + ClassName + _T("|");
	ptree->SetItem(hitem, TVIF_TEXT, tempString, 0, 0, NULL, NULL, NULL);
	ptree->Expand(hitem, TVE_EXPAND);
	ptree->SetItemData(hitem, (DWORD_PTR)hWnd);
	HTREEITEM hItem = ptree->GetRootItem();
	if (SelectWindowItam != NULL)
	{
		ptree->SelectItem(SelectWindowItam);
	}
	ToolsDlg->TreeWindowsTreeCtrl.EnableWindow(TRUE);
	ToolsDlg->menu.EnableMenuItem(ID_WINDOW_REFRESH_WINDOW_TREE, MF_ENABLED);
	ToolsDlg->ShowHideWindows.EnableWindow(TRUE);
	ToolsDlg->ShowHideChildWindows.EnableWindow(TRUE);
	ToolsDlg->ReadFileIcon.EnableWindow(TRUE);
	ToolsDlg->GetDlgItem(IDC_BUTTON_REFRESH_WINDOWS_TREE)->EnableWindow(TRUE);
	//if (ToolsDlg->m_pTaskBarlist != NULL)
	//{
	//	ToolsDlg->m_pTaskBarlist->SetProgressState(ToolsDlg->m_hWnd, TBPF_NOPROGRESS);
	//}
	ToolsDlg->Progress_ON = FALSE;
	return 0;
}

void CWindowsToolsDlg::OnBnClickedButtonRefreshWindowsTree()
{
	// TODO: 在此添加控件通知处理程序代码
	TreeWindowsTreeCtrl.EnableWindow(FALSE);
	menu.EnableMenuItem(ID_WINDOW_REFRESH_WINDOW_TREE, MF_GRAYED);
	ShowHideWindows.EnableWindow(FALSE);
	ShowHideChildWindows.EnableWindow(FALSE);
	ReadFileIcon.EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_REFRESH_WINDOWS_TREE)->EnableWindow(FALSE);
	UpdateData(TRUE);
	DWORD TexitCode;
	if (hThread_RefreshWindowsTree != NULL)
	{
		GetExitCodeThread(hThread_RefreshWindowsTree, &TexitCode);
		CloseHandle(hThread_RefreshWindowsTree);
	}
	hThread_RefreshWindowsTree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RefreshWindowsTree, this, 0, NULL);
	
	//RefreshWindowsTree(this);
}

void CWindowsToolsDlg::GetWindowRectToWindow(HWND hWnd, HWND ParenthWnd, HWND _Static /*= NULL*/)
{
	CString TempString;
	//RECT
	RECT rect = { };
	POINT p;
	::GetWindowRect(hWnd, &rect);
	p.x = rect.left;
	p.y = rect.top;
	::ScreenToClient(ParenthWnd, &p);
	rect.left = p.x;
	rect.top = p.y;
	p.x = rect.right;
	p.y = rect.bottom;
	::ScreenToClient(ParenthWnd, &p);
	rect.right = p.x;
	rect.bottom = p.y;
	if (EditWindowRectLeft.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.left);
		EditWindowRectLeft.SetWindowText(TempString);
	}
	if (EditWindowRectRight.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.right);
		EditWindowRectRight.SetWindowText(TempString);
	}
	if (EditWindowRectTop.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.top);
		EditWindowRectTop.SetWindowText(TempString);
	}
	if (EditWindowRectBottom.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.bottom);
		EditWindowRectBottom.SetWindowText(TempString);
	}
	if (EditWindowWidth.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.right - rect.left);
		EditWindowWidth.SetWindowText(TempString);
	}
	if (EditWindowHigth.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.bottom - rect.top);
		EditWindowHigth.SetWindowText(TempString);
	}
	//POINT point = { 0 };
	//::MapWindowPoints(hWnd, ParenthWnd, &point, 1);
	if (EditWindowRelativeRectLeft.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.left);
		EditWindowRelativeRectLeft.SetWindowText(TempString);
	}
	if (EditWindowRelativeRectTop.m_hWnd != _Static)
	{
		TempString.Format(_T("%d"), rect.top);
		EditWindowRelativeRectTop.SetWindowText(TempString);
	}
}

void CWindowsToolsDlg::GetWindowInfoToWindow(HWND hWnd)
{
	//
	CString TempString;
	//Message
	EditRelevantMessage = FALSE;
	//Window handle
	HWND PhWnd = ::GetParent(hWnd);
	if (!EditWindowHandleDECEditing)
	{
#ifdef _WIN64
		TempString.Format(_T("%llu"), hWnd);
#else
		TempString.Format(_T("%u"), hWnd);
#endif // _WIN64
		EditWindowHandleDEC.SetWindowText(TempString);
	}
	if (!EditWindowHandleHEXEditing)
	{
#ifdef _WIN64
		TempString.Format(_T("%08llX"), hWnd);
#else
		TempString.Format(_T("%08X"), hWnd);
#endif // _WIN64
		EditWindowHandleHEX.SetWindowText(TempString);
	}
#ifdef _WIN64
	TempString.Format(_T("%llu"), PhWnd);
#else
	TempString.Format(_T("%u"), PhWnd);
#endif // _WIN64
	EditParentWindowHandle.SetWindowText(TempString);
	//Style
	TempString.Format(_T("%08lX"), ::GetWindowLong(hWnd, GWL_STYLE));
	EditWindowStyle.SetWindowTextW(TempString);
	TempString.Format(_T("%08lX"), ::GetWindowLong(hWnd, GWL_EXSTYLE));
	EditWindowStyleEx.SetWindowTextW(TempString);
	//Text
	int TextLength = ::GetWindowTextLength(hWnd) + 1;

	::GetWindowText(hWnd, TempString.GetBuffer(TextLength), TextLength);
	TempString.ReleaseBuffer();
	EditWindowText.SetWindowText(TempString);
	//Class name
	::RealGetWindowClass(hWnd, TempString.GetBuffer(50), 50);
	TempString.ReleaseBuffer();
	CString ClassName_1;
	::GetClassName(hWnd, ClassName_1.GetBuffer(50), 50);
	ClassName_1.ReleaseBuffer();
	if (TempString == ClassName_1)
	{
		EditWindowClassName_1.ShowWindow(SW_HIDE);
		//CRect tempRect = CRect(ClassNameEdirtRect.left, ClassNameEdirtRect.top, ClassNameEdirtRect.right, ClassNameEdirtRect.bottom);
		EditWindowClassName.MoveWindow(ClassNameEdirtRect);
	}
	else
	{
		EditWindowClassName_1.SetWindowText(ClassName_1);
		EditWindowClassName_1.ShowWindow(SW_SHOW);
		CRect tempRect = CRect(ClassNameEdirtRect.left, ClassNameEdirtRect.top, ClassNameEdirtRect.right - (ClassNameEdirtRect.right - ClassNameEdirtRect.left) / 2, ClassNameEdirtRect.bottom);
		EditWindowClassName.MoveWindow(tempRect);
		//EditWindowClassName.
	}
	EditWindowClassName.SetWindowText(TempString);
	//Invalidate();
	
	//Control ID
	TempString.Format(_T("%d"), ::GetDlgCtrlID(hWnd));
	EditWindowControlID.SetWindowText(TempString);
	
	//ShowWindow
	WINDOWPLACEMENT windowplacement = { 0 };
	windowplacement.length = sizeof(WINDOWPLACEMENT);
	if (::IsWindowVisible(hWnd))
	{
		::GetWindowPlacement(hWnd, &windowplacement);
		if (windowplacement.showCmd <= 10 && windowplacement.showCmd >= 0)
		{
			ComboSpecifiesShow.SetCurSel(windowplacement.showCmd);
		}
		else
		{
			ComboSpecifiesShow.SetCurSel(-1);
		}
	}
	else
	{
		ComboSpecifiesShow.SetCurSel(0);
	}
	//Disabled
	if (::IsWindowEnabled(hWnd))
	{
		CheckDisabled.SetCheck(BST_UNCHECKED);
	}
	else
	{
		CheckDisabled.SetCheck(BST_CHECKED);
	}
	//Process and Thread
	DWORD ProcessID = 0;
	DWORD ThreadHandle = ::GetWindowThreadProcessId(hWnd, &ProcessID);
	TempString.Format(_T("%u"), ProcessID);
	EditProcessID.SetWindowText(TempString);
	TempString.Format(_T("%u"), ThreadHandle);
	EditThreadHandle.SetWindowText(TempString);
	HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, ProcessID);
	if (hProcess == NULL)
	{
		StaticProcessWOW = _T("--");
		EditProcessName.SetWindowText(_T(""));
		EditProcessPath.SetWindowText(_T(""));
	}
	else
	{
		//WOW64
		BOOL WOW64;
		BOOL re = ::IsWow64Process(hProcess, &WOW64);
		if (re)
		{
			if (WOW64)
			{
				StaticProcessWOW = _T("32");
			}
			else
			{
				StaticProcessWOW = _T("64");
			}
		}
		else
		{
			StaticProcessWOW = _T("--");
		}
		//Path
		HANDLE ProcessSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
		if (ProcessSnapshot == NULL)
		{
			EditProcessName.SetWindowText(_T(""));
			EditProcessPath.SetWindowText(_T(""));
		}
		else
		{
			MODULEENTRY32 me;
			me.dwSize = sizeof(me);
			BOOL re = ::Module32First(ProcessSnapshot, &me);
			if (re)
			{
				EditProcessPath.SetWindowText(me.szExePath);
				EditProcessName.SetWindowText(me.szModule);
			}
			else
			{
				EditProcessPath.SetWindowText(_T(""));
				EditProcessName.SetWindowText(_T(""));
			}
			CloseHandle(ProcessSnapshot);
		}
		CloseHandle(hProcess);
	}

	EditParentProcessID.SetWindowText(_T(""));
	DWORD ParentProcessID = 0;
	ULONG psize;
	PVOID buffer;
	PVOID NextData = NULL;
	SYSTEM_PROCESS_INFORMATION system_process;
	::ZwQuerySystemInformation(SystemProcessInformation, NULL, 0ul, &psize);
	buffer = GlobalAlloc(GMEM_ZEROINIT, psize);

	NTSTATUS re = ZwQuerySystemInformation(SystemProcessInformation, buffer, psize, &psize);
	if (re == 0)
	{
		NextData = buffer;
		CopyMemory(&system_process, buffer, sizeof(system_process));

		while (system_process.NextEntryOffset != 0ul)
		{
			NextData = (char*)NextData + system_process.NextEntryOffset;
			CopyMemory(&system_process, NextData, sizeof(system_process));
			if ((DWORD)system_process.UniqueProcessId == ProcessID)
			{
				ParentProcessID = (DWORD)system_process.Reserved3;
#ifdef _WIN64
				TempString.Format(_T("%llu"), system_process.Reserved3);
#else
				TempString.Format(_T("%u"), system_process.Reserved3);
#endif // _WIN64
				EditParentProcessID.SetWindowText(TempString);
				break;
			}
		}
	}
	GlobalFree(buffer);
	{
		HANDLE hProcess = ::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, ParentProcessID);
		if (hProcess == NULL)
		{
			StaticParentProcessWOW = _T("--");
// 			EditParentProcessName = _T("");
// 			EditParentProcessPath = _T("");
		}
		else
		{
			//WOW64
			BOOL WOW64;
			BOOL re = ::IsWow64Process(hProcess, &WOW64);
			if (re)
			{
				if (WOW64)
				{
					StaticParentProcessWOW = _T("32");
				}
				else
				{
					StaticParentProcessWOW = _T("64");
				}
			}
			else
			{
				StaticParentProcessWOW = _T("--");
			}
			//Path
// 			HANDLE ProcessSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);
// 			if (ProcessSnapshot == NULL)
// 			{
// 				EditParentProcessName = _T("");
// 				EditParentProcessPath = _T("");
// 			}
// 			else
// 			{
// 				MODULEENTRY32 me;
// 				me.dwSize = sizeof(me);
// 				BOOL re = ::Module32First(ProcessSnapshot, &me);
// 				if (re)
// 				{
// 					EditParentProcessPath = me.szExePath;
// 					EditParentProcessName = me.szModule;
// 				}
// 				else
// 				{
// 					EditParentProcessPath = _T("");
// 					EditParentProcessName = _T("");
// 				}
// 				CloseHandle(ProcessSnapshot);
// 			}
			CloseHandle(hProcess);
		}
		GetWindowRectToWindow(hWnd, PhWnd);
	}
	UpdateData(FALSE);
	EditRelevantMessage = TRUE;
}

BOOL CWindowsToolsDlg::SetTreeViewSelect(HTREEITEM RootItemHandle, HWND hWnd)
{
	while (RootItemHandle != NULL)
	{
		if ((HWND)TreeWindowsTreeCtrl.GetItemData(RootItemHandle) == hWnd)
		{
			TreeWindowsTreeCtrl.SelectItem(RootItemHandle);
			return TRUE;
		}
		if (SetTreeViewSelect(TreeWindowsTreeCtrl.GetChildItem(RootItemHandle), hWnd))
		{
			return TRUE;
		}
		RootItemHandle = TreeWindowsTreeCtrl.GetNextSiblingItem(RootItemHandle);
	}
	return FALSE;
}

void CWindowsToolsDlg::SetTreeViewBold(HTREEITEM RootItemHandle, HWND hWnd)
{
	while (RootItemHandle != NULL)
	{
		if (hWnd != NULL && (HWND)TreeWindowsTreeCtrl.GetItemData(RootItemHandle) == hWnd)
		{
			TreeWindowsTreeCtrl.SetItem(RootItemHandle, TVIF_STATE, NULL, 0, 0, TVIS_BOLD, TVIS_BOLD, NULL);
		}
		else
		{
			TreeWindowsTreeCtrl.SetItem(RootItemHandle, TVIF_STATE, NULL, 0, 0, NULL, TVIS_BOLD, NULL);
		}
		SetTreeViewBold(TreeWindowsTreeCtrl.GetChildItem(RootItemHandle), hWnd);
		RootItemHandle = TreeWindowsTreeCtrl.GetNextSiblingItem(RootItemHandle);
	}
}

void CWindowsToolsDlg::SetTreeViewBoldSelect(HTREEITEM RootItemHandle, HWND hWnd)
{
	while (RootItemHandle != NULL)
	{
		if (hWnd != NULL && (HWND)TreeWindowsTreeCtrl.GetItemData(RootItemHandle) == hWnd)
		{
			TreeWindowsTreeCtrl.SetItem(RootItemHandle, TVIF_STATE, NULL, 0, 0, TVIS_BOLD, TVIS_BOLD, NULL);
			//TreeWindowsTreeCtrl.Expand(TreeWindowsTreeCtrl.GetParentItem(RootItemHandle), TVE_EXPAND);
			TreeWindowsTreeCtrl.SelectItem(RootItemHandle);
		}
		else
		{
			TreeWindowsTreeCtrl.SetItem(RootItemHandle, TVIF_STATE, NULL, 0, 0, NULL, TVIS_BOLD, NULL);
		}
		SetTreeViewBoldSelect(TreeWindowsTreeCtrl.GetChildItem(RootItemHandle), hWnd);
		RootItemHandle = TreeWindowsTreeCtrl.GetNextSiblingItem(RootItemHandle);
	}
}

void CWindowsToolsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	// TODO: 在此处添加消息处理程序代码
	CTreeCtrl* ptree = (CTreeCtrl*)GetDlgItem(IDC_TREE_WINDOWS_TREE);
	if (ptree != NULL && WindowsTreeLeft != 0)
	{
		//CRect treeRect = { 0 };
		//ptree->GetWindowRect(&treeRect);
		ptree->MoveWindow(CRect(WindowsTreeLeft, 12, cx - 12, cy - 12), FALSE);
		Invalidate();
	}
}

void CWindowsToolsDlg::OnTvnSelchangedTreeWindowsTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HWND hWnd = (HWND)TreeWindowsTreeCtrl.GetItemData(pNMTreeView->itemNew.hItem);
	CMenu* pSubMenu = menu.GetSubMenu(1);
	if (MarkWindowHwnd != NULL && MarkWindowHwnd == hWnd)
	{
		pSubMenu->CheckMenuItem(ID_WINDOW_HIGHLIGHT, MF_CHECKED);
	}
	else
	{
		pSubMenu->CheckMenuItem(ID_WINDOW_HIGHLIGHT, MF_UNCHECKED);
	}
	GetWindowInfoToWindow(hWnd);
	*pResult = 0;
}

HWND LocalWindowFromPoint(POINT point, HWND parent, BOOL GetHideWindow)
{
	if (parent == NULL)
	{
		HWND hWnd = ::WindowFromPoint(point);
		parent = ::GetParent(hWnd);
		TRACE("hwnd is %d parent is null, GetParent:%d(%d)\n", hWnd, parent, ::IsChild(parent, hWnd));
		if (parent == NULL || ::IsChild(parent, hWnd) == FALSE)
		{
			parent = hWnd;
		}
	}
	//获取子窗口
	HWND cur = GetWindow(parent, GW_CHILD);
	POINT minWindow = { 0x3FFFFFFF, 0x3FFFFFFF };
	HWND minWindowHandle = NULL;
	while (cur != NULL)
	{
		if (IsWindow(cur) == FALSE ||			//过滤非窗口的句柄
			GetHideWindow == FALSE && IsWindowVisible(cur) == FALSE)//过滤隐藏窗口
		{
			cur = GetWindow(cur, GW_HWNDNEXT);
			continue;
		}
		//判断是否在范围内
		RECT rect;
		GetWindowRect(cur, &rect);
		if (rect.left < point.x && rect.right > point.x && rect.top < point.y && rect.bottom > point.y)
		{
			if (minWindow.x + minWindow.y > rect.right - rect.left + rect.bottom - rect.top)
			{
				minWindow.x = rect.right - rect.left;
				minWindow.y = rect.bottom - rect.top;
				minWindowHandle = cur;
			}
		}
		cur = GetWindow(cur, GW_HWNDNEXT);
	}
	if (minWindowHandle == NULL)
	{
		return parent;
	}
	return LocalWindowFromPoint(point, minWindowHandle, GetHideWindow);
}

void CWindowsToolsDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x > 30 && point.x < 61 && point.y > 30 && point.y < 58)
	{
		if (GetHideWindow.GetCheck() == BST_CHECKED)
		{
			GetHideWindowTemp = TRUE;
		}
		else
		{
			GetHideWindowTemp = FALSE;
		}
		WindowSelectStatus = IDB_BITMAP_BUSY;
		InvalidateRect(CRect(30, 30, 61, 58));
		SetCursor(CursorWindowSelect);
		SetCapture();
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CWindowsToolsDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (WindowSelectStatus == IDB_BITMAP_BUSY)
	{
		ReleaseCapture();
		WindowSelectStatus = IDB_BITMAP_FREE;
		InvalidateRect(CRect(30, 30, 61, 58));
		POINT mpoint;
		GetCursorPos(&mpoint);
		//HWND hWnd = ::WindowFromPoint(mpoint);
		HWND hWnd = LocalWindowFromPoint(mpoint, NULL, GetHideWindowTemp);
		if (IsLocalWindow(hWnd))
		{
			MarkWindowHwnd = NULL;
			SetTreeViewBoldSelect(TreeWindowsTreeCtrl.GetRootItem(), NULL);
		}
		else
		{
			MarkWindowHwnd = hWnd;
			GetWindowInfoToWindow(hWnd);
			SetTreeViewBoldSelect(TreeWindowsTreeCtrl.GetRootItem(), hWnd);
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CWindowsToolsDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (WindowSelectStatus == IDB_BITMAP_BUSY)
	{
		POINT mpoint;
		GetCursorPos(&mpoint);
		//HWND hWnd = ::WindowFromPoint(mpoint);
		HWND hWnd = LocalWindowFromPoint(mpoint, NULL, GetHideWindowTemp);
		if (IsLocalWindow(hWnd))
		{
			MarkWindowHwnd = NULL;
		}
		else
		{
			MarkWindowHwnd = hWnd;
			GetWindowInfoToWindow(hWnd);
		}
		//Invalidate();
	}
	else
	{
		if (point.x > 30 && point.x < 61 && point.y > 30 && point.y < 58)
		{
			SetCursor(CursorWindowSelect);
		}
		else
		{
			SetCursor(CursorDefault);
		}
		
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CWindowsToolsDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (WindowClosing)
	{
		return;
	}
	DWORD TexitCode;
	WindowClosing = 1;//在全局添加正在退出标记
	EnableWindow(FALSE);//禁用窗口，防止被输入造成不必要的麻烦
	if (hThread_ProgressRefresh != NULL)
	{
		TexitCode = STILL_ACTIVE;
		while (TexitCode == STILL_ACTIVE)//如果线程仍然继续，就等待
		{
			DoEvents();//处理窗口事件，没有这个的话操作窗口的代码会一直等待，出现假死状态
			Sleep(1);
			GetExitCodeThread(hThread_ProgressRefresh, &TexitCode);//获取线程返回值，正常情况是获取到线程里执行return返回的值，若线程没有结束会获取到STILL_ACTIVE
		}
		TRACE("hThread_ProgressRefresh:%u\n", TexitCode);//输出调试文本
		CloseHandle(hThread_ProgressRefresh);//关闭线程句柄
	}
	if (hThread_RefreshWindowsTree != NULL)
	{
		TexitCode = STILL_ACTIVE;
		while (TexitCode == STILL_ACTIVE)
		{
			DoEvents();
			Sleep(1);
			GetExitCodeThread(hThread_RefreshWindowsTree, &TexitCode);
		}
		TRACE("hThread_RefreshWindowsTree:%u\n", TexitCode);
		CloseHandle(hThread_RefreshWindowsTree);
	}
	if (m_image != NULL)
	{
		m_image->DeleteImageList();
		delete m_image;
	}
	if (m_DialogSelectWindow != NULL)
	{
		m_DialogSelectWindow->DestroyWindow();
		delete m_DialogSelectWindow;
	}
	//EndDialog(0);
	CDialogEx::OnClose();
}

void CWindowsToolsDlg::OnEnChangeEditWindowHandleDec()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		EditWindowHandleDECEditing = TRUE;
		HWND hWnd = NULL;
		CString TempString;
		EditWindowHandleDEC.GetWindowText(TempString);
		_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
		GetWindowInfoToWindow(hWnd);
		SetTreeViewSelect(TreeWindowsTreeCtrl.GetRootItem(), hWnd);
		EditWindowHandleDECEditing = FALSE;
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowHandleHex()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		EditWindowHandleHEXEditing = TRUE;
		HWND hWnd = NULL;
		CString TempString;
		EditWindowHandleHEX.GetWindowText(TempString);
#ifdef _WIN64
		int i_ret = _stscanf(TempString, _T("%llx"), (PULONG_PTR)&hWnd);
#else
		int i_ret = _stscanf(TempString, _T("%x"), (PULONG_PTR)&hWnd);
#endif // _WIN64
		if (i_ret == 0)
		{
			hWnd = NULL;
		}
		GetWindowInfoToWindow(hWnd);
		SetTreeViewSelect(TreeWindowsTreeCtrl.GetRootItem(), hWnd);
		EditWindowHandleHEXEditing = FALSE;
	}

}

void CWindowsToolsDlg::OnEnKillfocusEditParentWindowHandle()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString;
	HWND hWnd = NULL;
	EditWindowHandleDEC.GetWindowText(TempString);
#ifdef _WIN64
	int i_ret = _stscanf(TempString, _T("%llu"), (PULONG_PTR)&hWnd);
#else
	int i_ret = _stscanf(TempString, _T("%u"), (PULONG_PTR)&hWnd);
#endif // _WIN64
	if (i_ret == 0 || hWnd == 0)
	{
		return;
	}
	HWND PhWnd = NULL;
	EditParentWindowHandle.GetWindowText(TempString);
#ifdef _WIN64
	i_ret = _stscanf(TempString, _T("%llu"), (PULONG_PTR)&PhWnd);
#else
	i_ret = _stscanf(TempString, _T("%u"), (PULONG_PTR)&PhWnd);
#endif // _WIN64
	if (i_ret == 0)
	{
		PhWnd = NULL;
	}
	if (::GetParent(hWnd) != PhWnd)
	{
		::SetParent(hWnd, PhWnd);
		GetWindowInfoToWindow(hWnd);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowText()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		CString TempString;
		HWND hWnd = NULL;
		EditWindowHandleDEC.GetWindowText(TempString);
		_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
		EditWindowText.GetWindowText(TempString);
		::SetWindowText(hWnd, TempString);
	}
}

void CWindowsToolsDlg::MoveWindowFromWindow(HWND _Static, BOOL Relative)
{
	int top, lift, width, higth;
	CString TempString;
	HWND hWnd = NULL;
	EditWindowHandleDEC.GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	HWND PhWnd = NULL;
	EditParentWindowHandle.GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&PhWnd);
	if (Relative)
	{
		//WINDOWINFO wi;
		//wi.cbSize = sizeof(wi);
		//::GetWindowInfo(PhWnd, &wi);
		EditWindowRelativeRectLeft.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &lift);
		EditWindowWidth.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &width);
		EditWindowRelativeRectTop.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &top);
		EditWindowHigth.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &higth);
		//lift -= (wi.rcClient.left - wi.rcWindow.left);
		//top -= (wi.rcClient.top - wi.rcWindow.top);
	}
	else
	{
		//RECT rect;
		//POINT point = { 0 };
		//::GetWindowRect(hWnd, &rect);
		//::MapWindowPoints(hWnd, PhWnd, &point, 1);
		EditWindowRectLeft.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &lift);
		EditWindowRectRight.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &width);
		width -= lift;
		EditWindowRectTop.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &top);
		EditWindowRectBottom.GetWindowText(TempString);
		_stscanf(TempString, _T("%d"), &higth);
		higth -= top;
		//top -= (rect.top - point.y);
		//lift -= (rect.left - point.x);
		//WINDOWINFO wi;
		//wi.cbSize = sizeof(wi);
		//::GetWindowInfo(PhWnd,&wi);
		//lift -= (wi.rcClient.left - wi.rcWindow.left);
		//top -= (wi.rcClient.top - wi.rcWindow.top);
	}
	::MoveWindow(hWnd, lift, top, width, higth, TRUE);
	EditRelevantMessage = FALSE;
	GetWindowRectToWindow(hWnd, PhWnd, _Static);
	EditRelevantMessage = TRUE;
}

BOOL CWindowsToolsDlg::IsLocalWindow(HWND hWnd)
{
	while (hWnd != NULL)
	{
		if (hWnd == m_hWnd)
		{
			return TRUE;
		}
		hWnd = ::GetParent(hWnd);
	}
	return FALSE;
}

void CWindowsToolsDlg::OnEnChangeEditWindowRectLeft()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// 
	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowRectLeft.m_hWnd);
	}

}

void CWindowsToolsDlg::OnEnChangeEditWindowRectRight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowRectRight.m_hWnd);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowRectTop()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowRectTop.m_hWnd);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowRectBottom()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowRectBottom.m_hWnd);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowRelatveRectLeft()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowRelativeRectLeft.m_hWnd, TRUE);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowRelatveRectTop()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowRelativeRectTop.m_hWnd, TRUE);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowWidth.m_hWnd, TRUE);
	}
}

void CWindowsToolsDlg::OnEnChangeEditWindowHigth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		MoveWindowFromWindow(EditWindowHigth.m_hWnd, TRUE);
	}
}

void CWindowsToolsDlg::OnCbnSelchangeComboSpecifiesShown()
{
	// TODO: 在此添加控件通知处理程序代码
	if (EditRelevantMessage)
	{
		CString TempString;
		HWND hWnd = NULL;
		EditWindowHandleDEC.GetWindowText(TempString);
		_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
		::ShowWindow(hWnd, ComboSpecifiesShow.GetCurSel());
		GetWindowInfoToWindow(hWnd);
	}
}

void CWindowsToolsDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

BOOL CWindowsToolsDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (  LOWORD(wParam) > 10000 && LOWORD(wParam) < 20000)
	{
		AllLanguage->SetLanguageID(LOWORD(wParam) - 10000);
		SetWindowShowText();
	}
	
	return CDialog::OnCommand(wParam, lParam);
}

void CWindowsToolsDlg::OnWindowRefreshWindowTree()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedButtonRefreshWindowsTree();
}

void CWindowsToolsDlg::SetWindowShowText()
{
// 	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		pSysMenu->ModifyMenu(IDM_ABOUTBOX, MF_BYCOMMAND, IDM_ABOUTBOX, AllLanguage->GetLanguageStruct()->SYSMENU_ABOUTBOX);
	}

	CMenu* subMenu;
	menu.ModifyMenu(0, MF_BYPOSITION, NULL, AllLanguage->GetLanguageStruct()->MENU_FILE);
	subMenu = menu.GetSubMenu(0);
	subMenu->ModifyMenu(ID_FILE_EXIT, MF_BYCOMMAND, ID_FILE_EXIT, AllLanguage->GetLanguageStruct()->MENU_FILE_EXIT);

	menu.ModifyMenu(1, MF_BYPOSITION, NULL, AllLanguage->GetLanguageStruct()->MENU_WINDOW);
	subMenu = menu.GetSubMenu(1);
	subMenu->ModifyMenu(ID_WINDOW_REFRESH_WINDOW_TREE, MF_BYCOMMAND, ID_WINDOW_REFRESH_WINDOW_TREE, AllLanguage->GetLanguageStruct()->MENU_WINDOW_REFRESH_WINDOW_TREE);
	subMenu->ModifyMenu(ID_WINDOW_HIGHLIGHT, MF_BYCOMMAND | subMenu->GetMenuState(ID_WINDOW_HIGHLIGHT, MF_CHECKED), ID_WINDOW_HIGHLIGHT, AllLanguage->GetLanguageStruct()->MENU_WINDOW_HIGHLIGHT);
	subMenu->ModifyMenu(ID_WINDOW_SEND_MESSAGE, MF_BYCOMMAND | subMenu->GetMenuState(ID_WINDOW_SEND_MESSAGE, MF_CHECKED), ID_WINDOW_SEND_MESSAGE, AllLanguage->GetLanguageStruct()->MENU_WINDOW_SEND_MESSAGE);
	subMenu->ModifyMenu(ID_WINDOW_CONTROL_WINDOW, MF_BYCOMMAND | subMenu->GetMenuState(ID_WINDOW_CONTROL_WINDOW, MF_CHECKED), ID_WINDOW_CONTROL_WINDOW, AllLanguage->GetLanguageStruct()->MENU_WINDOW_CONTROL_WINDOW);
	subMenu->ModifyMenu(ID_WINDOW_GENERATE_FIND_CODE, MF_BYCOMMAND | subMenu->GetMenuState(ID_WINDOW_GENERATE_FIND_CODE, MF_CHECKED), ID_WINDOW_GENERATE_FIND_CODE, AllLanguage->GetLanguageStruct()->MENU_WINDOW_GENERATE_FIND_CODE);
	subMenu->ModifyMenu(ID_WINDOW_GENERATE_FIND_CODE_FAST, MF_BYCOMMAND | subMenu->GetMenuState(ID_WINDOW_GENERATE_FIND_CODE_FAST, MF_CHECKED), ID_WINDOW_GENERATE_FIND_CODE_FAST, AllLanguage->GetLanguageStruct()->MENU_WINDOW_GENERATE_FIND_CODE_FAST);

	menu.ModifyMenu(2, MF_BYPOSITION, NULL, AllLanguage->GetLanguageStruct()->MENU_LANGUAGE);

	subMenu = menu.GetSubMenu(2);//获取第三个菜单
	const std::vector<LanguageStruct>* LanguageList = AllLanguage->GetLanguageList();
	if (LanguageList->size() != 0)
	{
		for (std::vector<LanguageStruct>::const_iterator iter = LanguageList->cbegin(); iter != LanguageList->cend(); iter++)
		{
			if (iter->LangID == AllLanguage->GetLanguageStruct()->LangID)
			{
				//subMenu->AppendMenu(MF_CHECKED, iter->LOCALE_ID + 100000, iter->LANGUAGE);
				subMenu->CheckMenuItem((UINT)iter->LangID + 10000, MF_CHECKED);
			}
			else
			{
				subMenu->CheckMenuItem((UINT)iter->LangID + 10000, MF_UNCHECKED);
			}
		}

	}
	
	SetMenu(&menu);


	SetWindowText(AllLanguage->GetLanguageStruct()->TITLE_WINDOW_TOOLS);
	GetDlgItem(IDC_STATIC_WINDOW_HANDLE_DEC)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_HANDLE_DEC);
	GetDlgItem(IDC_STATIC_WINDOW_HANDLE_HEX)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_HANDLE_HEX);
	GetDlgItem(IDC_STATIC_PARENT_WINDOW_HANDLE)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_PARENT_WINDOW_HANDLE);
	GetDlgItem(IDC_STATIC_WINDOW_TEXT)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_TEXT);
	GetDlgItem(IDC_STATIC_WINDOW_CLASS_NAME)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_CLASS_NAME);
	GetDlgItem(IDC_STATIC_WINDOW_CONTROL_ID)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_CONTROL_ID);
	GetDlgItem(IDC_STATIC_THREAD_HANDLE)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_THREAD_HANDLE);
	GetDlgItem(IDC_STATIC_PROCESS_ID)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_PROCESS_ID);
	GetDlgItem(IDC_STATIC_PARENT_PROCESS_ID)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_PARENT_PROCESS_ID);
	GetDlgItem(IDC_STATIC_PROCESS_PATH)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_PROCESS_PATH);
	GetDlgItem(IDC_STATIC_PROCESS_NAME)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_PROCESS_NAME);
	GetDlgItem(IDC_STATIC_WINDOW_RECT)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RECT);
	GetDlgItem(IDC_STATIC_WINDOW_RECT_LEFT)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RECT_LEFT);
	GetDlgItem(IDC_STATIC_WINDOW_RECT_RIGHT)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RECT_RIGHT);
	GetDlgItem(IDC_STATIC_WINDOW_RECT_TOP)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RECT_TOP);
	GetDlgItem(IDC_STATIC_WINDOW_RECT_BOTTOM)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RECT_BOTTOM);
	GetDlgItem(IDC_STATIC_WINDOW_RELATIVE_POSITION)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RELATIVE_POSITION);
	GetDlgItem(IDC_STATIC_WINDOW_RELATIVE_POSITION_LEFT)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RELATIVE_POSITION_LEFT);
	GetDlgItem(IDC_STATIC_WINDOW_RELATIVE_POSITION_TOP)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_RELATIVE_POSITION_TOP);
	GetDlgItem(IDC_STATIC_WIDTH)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WIDTH);
	GetDlgItem(IDC_STATIC_HIGTH)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_HIGTH);
	GetDlgItem(IDC_STATIC_SPECIFIES_SHOWN)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_SPECIFIES_SHOWN);
	GetDlgItem(IDC_STATIC_REFRESH)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_REFRESH);
	GetDlgItem(IDC_CHECK_SHOW_HIDE_WINDOWS)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_SHOW_HIDE_WINDOWS);
	GetDlgItem(IDC_CHECK_SHOW_HIDE_CHILD_WINDOWS)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_SHOW_HIDE_CHILD_WINDOWS);
	GetDlgItem(IDC_CHECK_READ_FILE_ICON)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_READ_FILE_ICON);
	GetDlgItem(IDC_BUTTON_REFRESH_WINDOWS_TREE)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_REFRESH_WINDOWS_TREE);
	GetDlgItem(IDC_STATIC_WINDOW_STYLE)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_STYLE);
	GetDlgItem(IDC_STATIC_WINDOW_STYLE_EX)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_STYLE_EX);
	GetDlgItem(IDC_BUTTON_WINDOW_STYLE_ADVANCED)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_STYLE_ADVANCED);
	GetDlgItem(IDC_CHECK_DISABLED)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_CHECK_DISABLED);
	GetDlgItem(IDC_CHECK_GET_HIDE_WINDOW)->SetWindowText(AllLanguage->GetLanguageStruct()->CHECK_GET_HIDE_WINDOW);

}

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetWindowText(AllLanguage->GetLanguageStruct()->TITLE_ABOUT);
	//获取版本信息
	TCHAR ExecFileName[MAX_PATH] = { 0 };
	DWORD dwHandle, dwLen;
	BOOL verStatus;
	VS_FIXEDFILEINFO * verInfo;
	CString verString;
	LPVOID verData = NULL;
	GetModuleFileName(NULL, ExecFileName, MAX_PATH);
	dwLen = GetFileVersionInfoSize(ExecFileName, &dwHandle);
	if (dwLen == 0)
	{
		DrowErrorCode(GetLastError(), m_hWnd);
		CDialogEx::OnOK();
		return TRUE;
	}
	verData = new char[dwLen];
	verStatus = GetFileVersionInfo(ExecFileName, dwHandle, dwLen, verData);
	if (!verStatus)
	{
		delete[] verData;
        DrowErrorCode(GetLastError(), m_hWnd);
        CDialogEx::OnOK();
        return TRUE;
	}
	verStatus = VerQueryValue(verData, _T("\\"), (LPVOID*)&verInfo, (PUINT)&dwLen);
    if (!verStatus)
    {
        delete[] verData;
        DrowErrorCode(GetLastError(), m_hWnd);
        CDialogEx::OnOK();
        return TRUE;
    }
	verString.Format(_T("%d.%d.%d.%d"), HIWORD(verInfo->dwFileVersionMS), LOWORD(verInfo->dwFileVersionMS), HIWORD(verInfo->dwFileVersionLS), LOWORD(verInfo->dwFileVersionLS));
	delete[] verData;
	CString TempString = AllLanguage->GetLanguageStruct()->ABOUT_VERSION;
	TempString.Replace(_T("[VERSION]"), verString);
	GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(TempString);
	GetDlgItem(IDC_STATIC_COPYRIGHT)->SetWindowText(AllLanguage->GetLanguageStruct()->ABOUT_COPYRIGHT);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CWindowsToolsDlg::OnNMRClickTreeWindowsTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	
	CMenu* pSubMenu = menu.GetSubMenu(1);
	CPoint pt;
	GetCursorPos(&pt);
	TreeWindowsTreeCtrl.ScreenToClient(&pt);   //将鼠标的屏幕坐标，转换成树形控件的客户区坐标
	UINT uFlags = 0;
	HTREEITEM hItem = TreeWindowsTreeCtrl.HitTest(pt, &uFlags); //然后做点击测试
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))     //如果点击的位置是在节点位置上面
	{
		TreeWindowsTreeCtrl.SelectItem(hItem);
		//根据不同类型的节点弹出菜单
		//int nData = TreeWindowsTreeCtrl.GetItemData(hItem);
		TreeWindowsTreeCtrl.ClientToScreen(&pt);
		pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}

void CWindowsToolsDlg::OnFileExit()
{
	// TODO: 在此添加命令处理程序代码
	//exit(0);
}

void CWindowsToolsDlg::OnWindowHighlight()
{
	// TODO: 在此添加命令处理程序代码
	CMenu* pSubMenu = menu.GetSubMenu(1);

	UINT state = pSubMenu->GetMenuState(ID_WINDOW_HIGHLIGHT, MF_CHECKED);
	if (state == MF_UNCHECKED)
	{
		MarkWindowHwnd = (HWND)TreeWindowsTreeCtrl.GetItemData(TreeWindowsTreeCtrl.GetSelectedItem());
		SetTreeViewBoldSelect(TreeWindowsTreeCtrl.GetRootItem(), MarkWindowHwnd);
		if (MarkWindowHwnd != NULL)
		{
			pSubMenu->CheckMenuItem(ID_WINDOW_HIGHLIGHT, MF_CHECKED);
		}
	}
	else
	{
		pSubMenu->CheckMenuItem(ID_WINDOW_HIGHLIGHT, MF_UNCHECKED);
		MarkWindowHwnd = NULL;
		SetTreeViewBoldSelect(TreeWindowsTreeCtrl.GetRootItem(), MarkWindowHwnd);
	}
}

void CWindowsToolsDlg::OnWindowSendMessage()
{
	// TODO: 在此添加命令处理程序代码
	DlalogSendMessage SendMessageDlg;
	// Windows hwnd save to SendMessageDlg
	CString HwndString;
	EditWindowHandleDEC.GetWindowText(HwndString);
	SendMessageDlg.OperateHWND = (HWND)_tstoll(HwndString);
	SendMessageDlg.DoModal();
}

void CWindowsToolsDlg::OnWindowGenerateFindCode()
{
	// TODO: 在此添加命令处理程序代码
	DlalogGenerateFindCode GenerateFindCodeDlg;
	// Windows hwnd save to SendMessageDlg
	CString HwndString;
	EditWindowHandleDEC.GetWindowText(HwndString);
	GenerateFindCodeDlg.OperateHWND = (HWND)_tstoll(HwndString);
	GenerateFindCodeDlg.DoModal();
}


void CWindowsToolsDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// Timer to update the progress

// 	int nPos = ProcessWindowsRefresh.GetPos();
// 	int nMin, nMax;
// 	ProcessWindowsRefresh.GetRange(nMin, nMax);
// 	nPos++;
// 	// if finished, kill timer and return
// 	if (nPos > nMax)
// 	{
// 		// reset the progress state
// 		m_pTaskBarlist->SetProgressState(m_hWnd, TBPF_NOPROGRESS);
// 		// just flash the window to notify user
// 		FlashWindow(true);
// 		// Stop the timer
// 		KillTimer(0);
// 		// You can release the pointer if necessary here. 
// 				  // But not a good practice
// 		return;
// 	}
// 	// set progress to taskbar overlay
// 	m_pTaskBarlist->SetProgressValue(m_hWnd, nPos, nMax);
// 	// set the control's progress state
// 	ProcessWindowsRefresh.SetPos(nPos);
	CDialogEx::OnTimer(nIDEvent);
}


void CWindowsToolsDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialogEx::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	
// 	static BOOL first = TRUE;
// 	MessageBox(_T(""));
// 	if (first)
// 	{
// 		first = FALSE;
// 		CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&m_pTaskBarlist);
// 		OnBnClickedButtonRefreshWindowsTree();
// 	}
}


int CWindowsToolsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


BOOL CWindowsToolsDlg::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&m_pTaskBarlist);
	//OnBnClickedButtonRefreshWindowsTree();
	return CDialogEx::OnChildNotify(message, wParam, lParam, pLResult);
}




void CWindowsToolsDlg::OnWindowControlWindow()
{
	// TODO: 在此添加命令处理程序代码
	DlalogControl ControlDlg;
	// Windows hwnd save to SendMessageDlg
	CString HwndString;
	EditWindowHandleDEC.GetWindowText(HwndString);
	ControlDlg.OperateHWND = (HWND)_tstoll(HwndString);
	ControlDlg.DoModal();
}


void CWindowsToolsDlg::OnEnKillfocusEditWindowStyle()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString;
	HWND hWnd = NULL;
	EditWindowHandleDEC.GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	LONG lStyle = NULL;
	EditWindowStyle.GetWindowText(TempString);
	_stscanf(TempString, _T("%lX"), &lStyle);
	if (::GetWindowLong(hWnd, GWL_STYLE) != lStyle)
	{
		::SetWindowLong(hWnd, GWL_STYLE, lStyle);
		::InvalidateRect(hWnd, NULL, TRUE);
		GetWindowInfoToWindow(hWnd);
	}
}


void CWindowsToolsDlg::OnEnKillfocusEditWindowStyleEx()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString;
	HWND hWnd = NULL;
	EditWindowHandleDEC.GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	LONG lStyle = NULL;
	EditWindowStyleEx.GetWindowText(TempString);
	_stscanf(TempString, _T("%lX"), &lStyle);
	if (::GetWindowLong(hWnd, GWL_EXSTYLE) != lStyle)
	{
		::SetWindowLong(hWnd, GWL_EXSTYLE, lStyle);
		::InvalidateRect(hWnd, NULL, TRUE);
		GetWindowInfoToWindow(hWnd);
	}
}


void CWindowsToolsDlg::OnBnClickedButtonWindowStyleAdvanced()
{
	// TODO: 在此添加控件通知处理程序代码
	DlalogWindowStyle WindowStyleDlg;
	CString HwndString;
	EditWindowHandleDEC.GetWindowText(HwndString);
	WindowStyleDlg.OperateHWND = (HWND)_tstoll(HwndString);

	WindowStyleDlg.DoModal();
}


void CWindowsToolsDlg::OnWindowGenerateFindCodeFast()
{
	// TODO: 在此添加命令处理程序代码
	DlalogCodeView CodeView;
	CString Codes[2];
	Codes[0] = _T("1");
	Codes[1] = _T("2");
	CString Titles[2];
	Titles[0] = _T("3");
	Titles[1] = _T("4");
	CodeView.Codes = Codes;
	CodeView.Titles = Titles;
	CodeView.CodesNumber = 2;
	CodeView.DoModal();
}


void CWindowsToolsDlg::OnEnChangeEditWindowStyle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CWindowsToolsDlg::OnBnClickedCheckDisabled()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString;
	HWND hWnd = NULL;
	EditWindowHandleDEC.GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (CheckDisabled.GetCheck() == BST_CHECKED)
	{
		::EnableWindow(hWnd, FALSE);
	}
	else
	{
		::EnableWindow(hWnd, TRUE);
	}
	if (::IsWindowEnabled(hWnd))
	{
		CheckDisabled.SetCheck(BST_UNCHECKED);
	}
	else
	{
		CheckDisabled.SetCheck(BST_CHECKED);
	}
}


void CWindowsToolsDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void CWindowsToolsDlg::OnBnClickedCheckShowHideWindows()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ShowHideWindows.GetCheck() == BST_CHECKED)
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ShowHideWindows"), _T("TRUE"));
	}
	else
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ShowHideWindows"), _T("FALSE"));
	}
}


void CWindowsToolsDlg::OnBnClickedCheckShowHideChildWindows()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ShowHideChildWindows.GetCheck() == BST_CHECKED)
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ShowHideChildWindows"), _T("TRUE"));
	}
	else
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ShowHideChildWindows"), _T("FALSE"));
	}
}


void CWindowsToolsDlg::OnBnClickedCheckReadFileIcon()
{
	// TODO: 在此添加控件通知处理程序代码
	if (ReadFileIcon.GetCheck() == BST_CHECKED)
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ReadFileIcon"), _T("TRUE"));
	}
	else
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("RefreshWindowsTree"), _T("ReadFileIcon"), _T("FALSE"));
	}
}


void CWindowsToolsDlg::OnBnClickedCheckGetHideWindow()
{
	// TODO: 在此添加控件通知处理程序代码
	if (GetHideWindow.GetCheck() == BST_CHECKED)
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("SniffingWindow"), _T("GetHideWindow"), _T("TRUE"));
	}
	else
	{
		G_WritePrivateProfileString(_T("./config.ini"), _T("SniffingWindow"), _T("GetHideWindow"), _T("FALSE"));
	}
}
