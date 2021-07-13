#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// 将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。

#include <SDKDDKVer.h>

#include <vector>
struct tag_WINDOW_TYPE_LIST
{
	int STATIC;				//Static
	int COMPUTER;			//
	int CR;					//C SHARP
	int DESKTOP;			//root
	int EDIT;
	//int LINK;
	int MENU;
	int MFC;
	int PROCESS;			//Process
	int PROGRESSBAR;
	int WINDOW;
	int SYSTABCONTROL32;
	int GROUPBOX;
	int CHECKBOX;
	int RADIOBUTTON;
	int BUTTON;
	int SYSLINK;
	int SYSLISTVIEW32;
	int SYSHEADER32;
	int SCROLLBAR;
	int SYSTREEVIEW32;
	int STATUSBAR;
	int COMBOBOX;
	int TRACKBAR;
	int UPDOWN32;
	int LISTBOX;
	int TOOLBAR;
	int MDI;
	int DATA_TIME;			//SysDateTimePick32
	int ANIMATION;			//SysAnimate32
	int HOT_KEY;			//msctls_hotkey32
	int IP_ADDRESS;			//SysIPAddress32
	int MONTH_CALENDAR;		//SysMonthCal32
};

class Language;

extern Language* AllLanguage;

