
// WindowsTools.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号

// CWindowsToolsApp:
// 有关此类的实现，请参阅 WindowsTools.cpp
//
int GetControlTypeID(HWND hWnd, CString ClassName, const tag_WINDOW_TYPE_LIST& CintrolIDStruct);
class CWindowsToolsApp : public CWinApp
{
public:
	CWindowsToolsApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
#include <lmerr.h>

extern CWindowsToolsApp theApp;
void DrowErrorCode(DWORD dwLastError, HWND hWnd);
void DoEvents();
