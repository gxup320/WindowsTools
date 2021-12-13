
// WindowsTools.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "WindowsTools.h"
#include "WindowsToolsDlg.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//dump
//#include <minidumpapiset.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp.lib")
int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{
    // 创建 dmp 文件件
    TCHAR szFileName[MAX_PATH] = { 0 };
    LPCTSTR szVersion = _T("DumpDemo_v1.0");
    SYSTEMTIME stLocalTime;
    GetLocalTime(&stLocalTime);
    wsprintf(szFileName, L"%s-%04d%02d%02d-%02d%02d%02d.dmp",
        szVersion, stLocalTime.wYear, stLocalTime.wMonth, stLocalTime.wDay,
        stLocalTime.wHour, stLocalTime.wMinute, stLocalTime.wSecond);
    HANDLE hDumpFile = CreateFile(szFileName, GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);
    if (INVALID_HANDLE_VALUE == hDumpFile)
    {
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    // 写入 dmp 文件
    MINIDUMP_EXCEPTION_INFORMATION expParam;
    expParam.ThreadId = GetCurrentThreadId();
    expParam.ExceptionPointers = pExceptionPointers;
    expParam.ClientPointers = FALSE;
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
        hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
    // 释放文件
    CloseHandle(hDumpFile);
    return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
    // 这里做一些异常的过滤或提示
    if (IsDebuggerPresent())
    {
        return EXCEPTION_CONTINUE_SEARCH;
    }
    return GenerateMiniDump(lpExceptionInfo);
}

Language* AllLanguage = NULL;


// CWindowsToolsApp

BEGIN_MESSAGE_MAP(CWindowsToolsApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWindowsToolsApp 构造

CWindowsToolsApp::CWindowsToolsApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CWindowsToolsApp 对象

CWindowsToolsApp theApp;


// CWindowsToolsApp 初始化

BOOL CWindowsToolsApp::InitInstance()
{
	//dump
	//SetUnhandledExceptionFilter(ExceptionFilter);
	//Load language
	AllLanguage = new Language;
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("GXUP320"));

	CWindowsToolsDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	//Clean language
	delete AllLanguage;
	return FALSE;
}



int CWindowsToolsApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类

	CWinApp::ExitInstance();
	//return 0;

	return CWinApp::ExitInstance();
}


CString G_ReadPrivateProfileString(CString FileName, CString AppName, CString KeyName, CString Default)
{
	CString buffer;
	GetPrivateProfileString(AppName, KeyName, Default, buffer.GetBuffer(10000), 10000, FileName);
	buffer.ReleaseBuffer();
	return buffer;
}

BOOL G_WritePrivateProfileString(CString FileName, CString AppName, CString KeyName, CString String)
{
	return WritePrivateProfileString(AppName, KeyName, String, FileName);
}

void DrowErrorCode(DWORD dwLastError, HWND hWnd)
{
	CString TempString = _T("");
	HMODULE hModule = NULL; // default to system source
	LPTSTR MessageBuffer;
	DWORD dwBufferLength;
	DWORD dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_FROM_SYSTEM;

	if (dwLastError >= NERR_BASE && dwLastError <= MAX_NERR) {
		hModule = LoadLibraryEx(
			TEXT("netmsg.dll"),
			NULL,
			LOAD_LIBRARY_AS_DATAFILE
		);

		if (hModule != NULL)
			dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
	}
	if (dwBufferLength = FormatMessage(
		dwFormatFlags,
		hModule, // module to get message from (NULL == system)
		dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
		(LPTSTR)&MessageBuffer,
		0,
		NULL
	))
	{
		TempString.Format(_T(" (0x%X,%d)"), dwLastError, dwLastError);
		TempString += MessageBuffer;
		LocalFree(MessageBuffer);
		TempString = AllLanguage->GetLanguageStruct()->ERROR_ + TempString;
		MessageBox(hWnd, TempString, AllLanguage->GetLanguageStruct()->TITLE_WINDOW_TOOLS, MB_OK);
	}
	else
	{
		TempString.Format(_T(" 0x%X(%d)"), dwLastError, dwLastError);
		TempString = AllLanguage->GetLanguageStruct()->ERROR_ + TempString;
		MessageBox(hWnd, TempString, AllLanguage->GetLanguageStruct()->TITLE_WINDOW_TOOLS, MB_OK);
	}

	if (hModule != NULL)
		FreeLibrary(hModule);
}

int GetControlTypeID(HWND hWnd, CString ClassName, const tag_WINDOW_TYPE_LIST& CintrolIDStruct)
{
	if (ClassName == _T("#32769"))
	{
		return CintrolIDStruct.DESKTOP;
	}
	if (ClassName == _T("Shell_TrayWnd") || ClassName == _T("Progman"))
	{
		return CintrolIDStruct.COMPUTER;
	}
	if (ClassName == _T("SysTabControl32") || ClassName == _T("CCustomTabCtrl"))
	{
		return CintrolIDStruct.SYSTABCONTROL32;
	}
	if (ClassName == _T("Button") || ClassName.Find(_T(".BUTTON.app")) != -1)
	{
		LONG STYLE = GetWindowLongA(hWnd, GWL_STYLE);
		if ((STYLE & BS_GROUPBOX) == BS_GROUPBOX)
		{
			return CintrolIDStruct.GROUPBOX;
		}
		if ((STYLE & BS_CHECKBOX) == BS_CHECKBOX)
		{
			return CintrolIDStruct.CHECKBOX;
		}
		if ((STYLE & BS_RADIOBUTTON) == BS_RADIOBUTTON)
		{
			return CintrolIDStruct.RADIOBUTTON;
		}
		if ((STYLE & (BS_USERBUTTON | BS_DEFPUSHBUTTON)) == (BS_USERBUTTON | BS_DEFPUSHBUTTON))
		{
			return CintrolIDStruct.RADIOBUTTON;
		}
		return CintrolIDStruct.BUTTON;
	}
	if (ClassName == _T("SysLink") || ClassName == _T("_EL_HyperLinker"))
	{
		return CintrolIDStruct.SYSLINK;
	}
	if (ClassName == _T("Edit") || ClassName == _T("ThunderRT6TextBox") || ClassName.Left(1) == _T("T") && ClassName.Right(4) == _T("Edit") || ClassName.Find(_T(".RICHEDIT50W.app")) != -1)
	{
		return CintrolIDStruct.EDIT;
	}
	if (ClassName == _T("Static"))
	{
		// 		LONG STYLE = GetWindowLongA(hWnd, GWL_STYLE);
		// 		if (STYLE & 65536 == 65536)
		// 		{
		// 			return CintrolIDStruct.SYSLINK;
		// 		}
		return CintrolIDStruct.STATIC;
	}
	if (ClassName == _T("SysListView32") || ClassName.Find(_T(".SysListView32.app.")) != -1)
	{
		return CintrolIDStruct.SYSLISTVIEW32;
	}
	if (ClassName == _T("SysHeader32"))
	{
		return CintrolIDStruct.SYSHEADER32;
	}
	if (ClassName == _T("ScrollBar") || ClassName.Left(1) == _T("T") && ClassName.Right(9) == _T("ScrollBar"))
	{
		return CintrolIDStruct.SCROLLBAR;
	}
	if (ClassName == _T("msctls_progress32") || ClassName.Find(_T(".msctls_progress32.app.")) != -1)
	{
		return CintrolIDStruct.PROGRESSBAR;
	}
	if (ClassName == _T("SysTreeView32") || ClassName.Find(_T(".SysTreeView32.app.")) != -1)
	{
		return CintrolIDStruct.SYSTREEVIEW32;
	}
	if (ClassName == _T("msctls_statusbar32") || ClassName == _T("TStatusBar"))
	{
		return CintrolIDStruct.STATUSBAR;
	}
	if (ClassName == _T("ComboBox") || ClassName == _T("ComboBoxEx32"))
	{
		return CintrolIDStruct.COMBOBOX;
	}
	if (ClassName == _T("msctls_trackbar32") || ClassName == _T("TGDITrackBar"))
	{
		return CintrolIDStruct.TRACKBAR;
	}
	if (ClassName == _T("msctls_updown32"))
	{
		return CintrolIDStruct.UPDOWN32;
	}
	if (ClassName == _T("ListBox") || ClassName.Find(_T(".LISTBOX.app.")) != -1)
	{
		return CintrolIDStruct.LISTBOX;
	}
	if (ClassName == _T("Menu"))
	{
		return CintrolIDStruct.MENU;
	}
	if (ClassName == _T("SysDateTimePick32"))
	{
		return CintrolIDStruct.DATA_TIME;
	}
	if (ClassName == _T("SysAnimate32"))
	{
		return CintrolIDStruct.ANIMATION;
	}
	if (ClassName == _T("msctls_hotkey32"))
	{
		return CintrolIDStruct.HOT_KEY;
	}
	if (ClassName == _T("SysIPAddress32"))
	{
		return CintrolIDStruct.IP_ADDRESS;
	}
	if (ClassName == _T("SysMonthCal32"))
	{
		return CintrolIDStruct.MONTH_CALENDAR;
	}
	if (ClassName.Find(_T("Tool")) != -1)
	{
		return CintrolIDStruct.TOOLBAR;
	}
	if (ClassName.Left(3) == _T("Afx"))
	{
		return CintrolIDStruct.MFC;
	}
	if (ClassName.Left(12) == _T("WindowsForms"))
	{
		return CintrolIDStruct.CR;
	}
	if (ClassName.Find(_T("MDI")) != -1)
	{
		return CintrolIDStruct.MDI;
	}
	return CintrolIDStruct.WINDOW;
}