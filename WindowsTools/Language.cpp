#include "pch.h"
#include "Language.h"
CString G_ReadPrivateProfileString(CString FileName, CString AppName, CString KeyName, CString Default);
BOOL G_WritePrivateProfileString(CString FileName, CString AppName, CString KeyName, CString String);

Language::Language()
{
	//MessageBox(NULL, _T("Load Language"), NULL, NULL);
	LanguageArr.resize(0);
	//Load lang file
	CString filepath = _T("./language");
	CString filename = _T("");
	CString fullname = _T("");

	CFileFind find;
	BOOL IsFind = find.FindFile(filepath + _T("/*.lang"));

	while (IsFind)
	{
		IsFind = find.FindNextFile();
		if (find.IsDots() || find.IsDirectory())
		{
			continue;
		}
		else
		{
			filename = find.GetFileName();
			fullname = filepath + "/" + filename;
			//MessageBox(NULL, fullname, NULL, NULL);
			//Load language
			LanguageStruct LanguageTemp;

			//Information
			LanguageTemp.TRANSLATORS = G_ReadPrivateProfileString(fullname, _T("Information"), _T("TRANSLATORS"), _T(""));
			LanguageTemp.VERSION = G_ReadPrivateProfileString(fullname, _T("Information"), _T("VERSION"), _T(""));
			//Language
			LanguageTemp.LANGUAGE = G_ReadPrivateProfileString(fullname, _T("Language"), _T("LANGUAGE"), LanguageTemp.LANGUAGE);
			LanguageTemp.CHARACTER_CODE = G_ReadPrivateProfileString(fullname, _T("Language"), _T("CHARACTER_CODE"), LanguageTemp.CHARACTER_CODE);
			CString TEMP_LOCALE_ID = G_ReadPrivateProfileString(fullname, _T("Language"), _T("LOCALE_ID"), _T("0"));
			if (_stscanf(TEMP_LOCALE_ID, _T("%d"), &(LanguageTemp.LOCALE_ID)) != 1)
			{
				LanguageTemp.LOCALE_ID = MAXLONG;
			}
			//SystemMenu
			LanguageTemp.SYSMENU_ABOUTBOX = G_ReadPrivateProfileString(fullname, _T("SystemMenu"), _T("SYSMENU_ABOUTBOX"), LanguageTemp.SYSMENU_ABOUTBOX);
			//Menu
			LanguageTemp.MENU_FILE = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_FILE"), LanguageTemp.MENU_FILE);
			LanguageTemp.MENU_FILE_EXIT = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_FILE_EXIT"), LanguageTemp.MENU_FILE_EXIT);
			LanguageTemp.MENU_WINDOW = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW"), LanguageTemp.MENU_WINDOW);
			LanguageTemp.MENU_WINDOW_REFRESH_WINDOW_TREE = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW_REFRESH_WINDOW_TREE"), LanguageTemp.MENU_WINDOW_REFRESH_WINDOW_TREE);
			LanguageTemp.MENU_WINDOW_HIGHLIGHT = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW_HIGHLIGHT"), LanguageTemp.MENU_WINDOW_HIGHLIGHT);
			LanguageTemp.MENU_WINDOW_SEND_MESSAGE = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW_SEND_MESSAGE"), LanguageTemp.MENU_WINDOW_SEND_MESSAGE);
			LanguageTemp.MENU_WINDOW_CONTROL_WINDOW = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW_CONTROL_WINDOW"), LanguageTemp.MENU_WINDOW_CONTROL_WINDOW);
			LanguageTemp.MENU_WINDOW_GENERATE_FIND_CODE = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW_GENERATE_FIND_CODE "), LanguageTemp.MENU_WINDOW_GENERATE_FIND_CODE);
			LanguageTemp.MENU_WINDOW_GENERATE_FIND_CODE_FAST = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_WINDOW_GENERATE_FIND_CODE_FAST "), LanguageTemp.MENU_WINDOW_GENERATE_FIND_CODE_FAST);
			LanguageTemp.MENU_LANGUAGE = G_ReadPrivateProfileString(fullname, _T("Menu"), _T("MENU_LANGUAGE"), LanguageTemp.MENU_LANGUAGE);
			//Title
			LanguageTemp.TITLE_WINDOW_TOOLS = G_ReadPrivateProfileString(fullname, _T("Title"), _T("TITLE_WINDOW_TOOLS"), LanguageTemp.TITLE_WINDOW_TOOLS);
			LanguageTemp.TITLE_ABOUT = G_ReadPrivateProfileString(fullname, _T("Title"), _T("TITLE_ABOUT"), LanguageTemp.TITLE_ABOUT);
			LanguageTemp.TITLE_SEND_MESSAGE = G_ReadPrivateProfileString(fullname, _T("Title"), _T("TITLE_SEND_MESSAGE"), LanguageTemp.TITLE_SEND_MESSAGE);
			LanguageTemp.TITLE_GENERATE_FIND_CODE = G_ReadPrivateProfileString(fullname, _T("Title"), _T("TITLE_GENERATE_FIND_CODE"), LanguageTemp.TITLE_GENERATE_FIND_CODE);
			LanguageTemp.TITLE_CONTROL = G_ReadPrivateProfileString(fullname, _T("Title"), _T("TITLE_CONTROL"), LanguageTemp.TITLE_CONTROL);
			LanguageTemp.TITLE_WINDOW_STYLE = G_ReadPrivateProfileString(fullname, _T("Title"), _T("TITLE_WINDOW_STYLE"), LanguageTemp.TITLE_WINDOW_STYLE);
			//About
			LanguageTemp.ABOUT_VERSION = G_ReadPrivateProfileString(fullname, _T("About"), _T("ABOUT_VERSION"), LanguageTemp.ABOUT_VERSION);
			LanguageTemp.ABOUT_COPYRIGHT = G_ReadPrivateProfileString(fullname, _T("About"), _T("ABOUT_COPYRIGHT"), LanguageTemp.ABOUT_COPYRIGHT);
			//Dialog
			LanguageTemp.DIALOG_WINDOW_HANDLE_DEC = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_HANDLE_DEC"), LanguageTemp.DIALOG_WINDOW_HANDLE_DEC);
			LanguageTemp.DIALOG_WINDOW_HANDLE_HEX = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_HANDLE_HEX"), LanguageTemp.DIALOG_WINDOW_HANDLE_HEX);
			LanguageTemp.DIALOG_PARENT_WINDOW_HANDLE = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_PARENT_WINDOW_HANDLE"), LanguageTemp.DIALOG_PARENT_WINDOW_HANDLE);
			LanguageTemp.DIALOG_WINDOW_TEXT = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_TEXT"), LanguageTemp.DIALOG_WINDOW_TEXT);
			LanguageTemp.DIALOG_WINDOW_CLASS_NAME = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_CLASS_NAME"), LanguageTemp.DIALOG_WINDOW_CLASS_NAME);
			LanguageTemp.DIALOG_WINDOW_CONTROL_ID = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_CONTROL_ID"), LanguageTemp.DIALOG_WINDOW_CONTROL_ID);
			LanguageTemp.DIALOG_THREAD_HANDLE = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_THREAD_HANDLE"), LanguageTemp.DIALOG_THREAD_HANDLE);
			LanguageTemp.DIALOG_PROCESS_ID = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_PROCESS_ID"), LanguageTemp.DIALOG_PROCESS_ID);
			LanguageTemp.DIALOG_PARENT_PROCESS_ID = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_PARENT_PROCESS_ID"), LanguageTemp.DIALOG_PARENT_PROCESS_ID);
			LanguageTemp.DIALOG_PROCESS_PATH = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_PROCESS_PATH"), LanguageTemp.DIALOG_PROCESS_PATH);
			LanguageTemp.DIALOG_PROCESS_NAME = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_PROCESS_NAME"), LanguageTemp.DIALOG_PROCESS_NAME);
			LanguageTemp.DIALOG_WINDOW_RECT = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RECT"), LanguageTemp.DIALOG_WINDOW_RECT);
			LanguageTemp.DIALOG_WINDOW_RECT_LEFT = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RECT_LEFT"), LanguageTemp.DIALOG_WINDOW_RECT_LEFT);
			LanguageTemp.DIALOG_WINDOW_RECT_RIGHT = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RECT_RIGHT"), LanguageTemp.DIALOG_WINDOW_RECT_RIGHT);
			LanguageTemp.DIALOG_WINDOW_RECT_TOP = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RECT_TOP"), LanguageTemp.DIALOG_WINDOW_RECT_TOP);
			LanguageTemp.DIALOG_WINDOW_RECT_BOTTOM = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RECT_BOTTOM"), LanguageTemp.DIALOG_WINDOW_RECT_BOTTOM);
			LanguageTemp.DIALOG_WINDOW_RELATIVE_POSITION = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RELATIVE_POSITION"), LanguageTemp.DIALOG_WINDOW_RELATIVE_POSITION);
			LanguageTemp.DIALOG_WINDOW_RELATIVE_POSITION_LEFT = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RELATIVE_POSITION_LEFT"), LanguageTemp.DIALOG_WINDOW_RELATIVE_POSITION_LEFT);
			LanguageTemp.DIALOG_WINDOW_RELATIVE_POSITION_TOP = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_RELATIVE_POSITION_TOP"), LanguageTemp.DIALOG_WINDOW_RELATIVE_POSITION_TOP);
			LanguageTemp.DIALOG_WIDTH = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WIDTH"), LanguageTemp.DIALOG_WIDTH);
			LanguageTemp.DIALOG_HIGTH = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_HIGTH"), LanguageTemp.DIALOG_HIGTH);
			LanguageTemp.DIALOG_SPECIFIES_SHOWN = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_SPECIFIES_SHOWN"), LanguageTemp.DIALOG_SPECIFIES_SHOWN);
			LanguageTemp.DIALOG_REFRESH = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_REFRESH"), LanguageTemp.DIALOG_REFRESH);
			LanguageTemp.DIALOG_SHOW_HIDE_WINDOWS = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_SHOW_HIDE_WINDOWS"), LanguageTemp.DIALOG_SHOW_HIDE_WINDOWS);
			LanguageTemp.DIALOG_SHOW_HIDE_CHILD_WINDOWS = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_SHOW_HIDE_CHILD_WINDOWS"), LanguageTemp.DIALOG_SHOW_HIDE_CHILD_WINDOWS);
			LanguageTemp.DIALOG_READ_FILE_ICON = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_READ_FILE_ICON"), LanguageTemp.DIALOG_READ_FILE_ICON);
			LanguageTemp.DIALOG_REFRESH_WINDOWS_TREE = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_REFRESH_WINDOWS_TREE"), LanguageTemp.DIALOG_REFRESH_WINDOWS_TREE);
			LanguageTemp.DIALOG_TREE_LOADING = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_TREE_LOADING"), LanguageTemp.DIALOG_TREE_LOADING);
			LanguageTemp.DIALOG_WINDOW_STYLE = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_STYLE"), LanguageTemp.DIALOG_WINDOW_STYLE);
			LanguageTemp.DIALOG_WINDOW_STYLE_EX = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_STYLE_EX"), LanguageTemp.DIALOG_WINDOW_STYLE_EX);
			LanguageTemp.DIALOG_WINDOW_STYLE_ADVANCED = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_WINDOW_STYLE_ADVANCED"), LanguageTemp.DIALOG_WINDOW_STYLE_ADVANCED);
			LanguageTemp.DIALOG_CHECK_DISABLED = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("DIALOG_CHECK_DISABLED"), LanguageTemp.DIALOG_CHECK_DISABLED);
			LanguageTemp.CHECK_GET_HIDE_WINDOW = G_ReadPrivateProfileString(fullname, _T("Dialog"), _T("CHECK_GET_HIDE_WINDOW"), LanguageTemp.CHECK_GET_HIDE_WINDOW);
			
			//Control
			LanguageTemp.CONTROL_WINDOW_HANDLE = G_ReadPrivateProfileString(fullname, _T("CONTROL"), _T("CONTROL_WINDOW_HANDLE"), LanguageTemp.CONTROL_WINDOW_HANDLE);
			LanguageTemp.CONTROL_TAB_COMMON = G_ReadPrivateProfileString(fullname, _T("CONTROL"), _T("CONTROL_TAB_COMMON"), LanguageTemp.CONTROL_TAB_COMMON);
			LanguageTemp.CONTROL_TAB_EDIT = G_ReadPrivateProfileString(fullname, _T("CONTROL"), _T("CONTROL_TAB_EDIT"), LanguageTemp.CONTROL_TAB_EDIT);
			//SendMessage
			LanguageTemp.SENDMESSAGE_WINDOW_HANDLE = G_ReadPrivateProfileString(fullname, _T("SENDMESSAGE"), _T("WINDOW_HANDLE"), LanguageTemp.SENDMESSAGE_WINDOW_HANDLE);
			LanguageTemp.SENDMESSAGE_WINDOW_CLASS_NAME = G_ReadPrivateProfileString(fullname, _T("SENDMESSAGE"), _T("WINDOW_CLASS_NAME"), LanguageTemp.SENDMESSAGE_WINDOW_CLASS_NAME);
			LanguageTemp.SENDMESSAGE_WINDOW_TYPE = G_ReadPrivateProfileString(fullname, _T("SENDMESSAGE"), _T("WINDOW_TYPE"), LanguageTemp.SENDMESSAGE_WINDOW_TYPE);
			LanguageTemp.SENDMESSAGE_MESSAGE = G_ReadPrivateProfileString(fullname, _T("SENDMESSAGE"), _T("MESSAGE"), LanguageTemp.SENDMESSAGE_MESSAGE);
			LanguageTemp.SENDMESSAGE_SEND = G_ReadPrivateProfileString(fullname, _T("SENDMESSAGE"), _T("SEND"), LanguageTemp.SENDMESSAGE_SEND);
			//Common
			LanguageTemp.ERROR_ = G_ReadPrivateProfileString(fullname, _T("COMMON"), _T("ERROR"), LanguageTemp.ERROR_);
			LanguageTemp.ERROR0 = G_ReadPrivateProfileString(fullname, _T("COMMON"), _T("ERROR0"), LanguageTemp.ERROR0);
			LanguageTemp.WAITING = G_ReadPrivateProfileString(fullname, _T("COMMON"), _T("WAITING"), LanguageTemp.WAITING);
			LanguageTemp.RETURNVALUE = G_ReadPrivateProfileString(fullname, _T("COMMON"), _T("RETURNVALUE"), LanguageTemp.RETURNVALUE);
			LanguageTemp.LangID = LanguageArr.size() + 1;
			LanguageTemp.FullFileName = fullname;
			LanguageArr.push_back(LanguageTemp);
		}
	}
	if (LanguageArr.size() == 0)
	{
		//MessageBox(NULL, _T("Load language error, no language file exist."), _T("Load language error"), MB_OK);
		LanguageStruct LanguageTemp;
		LanguageTemp.LangID = LanguageArr.size() + 1;
		LanguageTemp.LANGUAGE = _T("English(United States)");
		LanguageTemp.LOCALE_ID = 1033;
		LanguageArr.push_back(LanguageTemp);
	}
	SelectLanguage = LanguageArr.cbegin();
	LCID SYSTEM_LOCALE_ID = GetSystemDefaultLCID();
	SetLanguageLCID(SYSTEM_LOCALE_ID);
}

Language::~Language()
{

}

std::vector<LanguageStruct>::const_iterator Language::GetLanguageStruct()
{
	return SelectLanguage;
}

const std::vector<LanguageStruct>* Language::GetLanguageList()
{
	return &LanguageArr;
}

std::vector<LanguageStruct>::const_iterator Language::SetLanguageLCID(LCID lcid)
{
	for (std::vector<LanguageStruct>::const_iterator iter = LanguageArr.cbegin(); iter != LanguageArr.cend(); iter++)
	{
		if (iter->LOCALE_ID == lcid)
		{
			SelectLanguage = iter;
			break;
		}
		if (iter->LOCALE_ID < SelectLanguage->LOCALE_ID)
		{
			SelectLanguage = iter;
		}
	}
	return SelectLanguage;
}

std::vector<LanguageStruct>::const_iterator Language::SetLanguageID(UINT ID)
{
	for (std::vector<LanguageStruct>::const_iterator iter = LanguageArr.cbegin(); iter != LanguageArr.cend(); iter++)
	{
		if (iter->LangID == ID)
		{
			SelectLanguage = iter;
			break;
		}
		if (iter->LOCALE_ID < SelectLanguage->LOCALE_ID)
		{
			SelectLanguage = iter;
		}
	}
	return SelectLanguage;
}

CString Language::GetIniFileText(CString Section, CString KeyName, CString Default)
{
	return  G_ReadPrivateProfileString(SelectLanguage->FullFileName, Section, KeyName, Default);
}
