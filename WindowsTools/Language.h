
struct LanguageStruct
{
	size_t LangID = 0;
	CString FullFileName = _T("");

	//Information
	CString TRANSLATORS = _T("");
	CString VERSION = _T("");

	//Language
	CString LANGUAGE = _T("");
	CString CHARACTER_CODE = _T("");
	LCID LOCALE_ID = MAXLONG;//GetOEMCP

	//SystemMenu
	CString SYSMENU_ABOUTBOX = _T("About WindowsTools(&A)...");

	//Menu
	CString MENU_FILE = _T("File");
	CString MENU_FILE_EXIT = _T("Exit");

	CString MENU_WINDOW = _T("Window");
	CString MENU_WINDOW_REFRESH_WINDOW_TREE = _T("Refresh window tree");
	CString MENU_WINDOW_HIGHLIGHT = _T("Highlight");
	CString MENU_WINDOW_SEND_MESSAGE = _T("Send message");
	CString MENU_WINDOW_CONTROL_WINDOW = _T("Control window");
	CString MENU_WINDOW_GENERATE_FIND_CODE = _T("Generate find code");
	CString MENU_WINDOW_GENERATE_FIND_CODE_FAST = _T("Generate find code (fast)");

	CString MENU_LANGUAGE = _T("Language");

	//Title
	CString TITLE_WINDOW_TOOLS = _T("Windows tools");
	CString TITLE_ABOUT = _T("About Window tools");
	CString TITLE_SEND_MESSAGE = _T("Send message");
	CString TITLE_GENERATE_FIND_CODE = _T("Generate find code");
	CString TITLE_CONTROL = _T("Control window");
	CString TITLE_WINDOW_STYLE = _T("Window style");

	//About
	CString ABOUT_VERSION = _T("Window tools, Version 1.0");
	CString ABOUT_COPYRIGHT = _T("Copyright (C) GXUP320");

	//Dialog
	CString DIALOG_WINDOW_HANDLE_DEC = _T("Window handle DEC:");
	CString DIALOG_WINDOW_HANDLE_HEX = _T("Window handle HEX:");
	CString DIALOG_PARENT_WINDOW_HANDLE = _T("Parent window handle:");
	CString DIALOG_WINDOW_TEXT = _T("Window text:");
	CString DIALOG_WINDOW_CLASS_NAME = _T("Window class name:");
	CString DIALOG_WINDOW_CONTROL_ID = _T("Window control ID:");
	CString DIALOG_THREAD_HANDLE = _T("Thread handle:");
	CString DIALOG_PROCESS_ID = _T("Process ID:");
	CString DIALOG_PARENT_PROCESS_ID = _T("Parent process ID:");
	CString DIALOG_PROCESS_PATH = _T("Process path:");
	CString DIALOG_PROCESS_NAME = _T("Process name:");
	CString DIALOG_WINDOW_RECT = _T("Window RECT");
	CString DIALOG_WINDOW_RECT_LEFT = _T("Left:");
	CString DIALOG_WINDOW_RECT_RIGHT = _T("Right:");
	CString DIALOG_WINDOW_RECT_TOP = _T("Top:");
	CString DIALOG_WINDOW_RECT_BOTTOM = _T("Bottom:");
	CString DIALOG_WINDOW_RELATIVE_POSITION = _T("Window relative position");
	CString DIALOG_WINDOW_RELATIVE_POSITION_LEFT = _T("Left:");
	CString DIALOG_WINDOW_RELATIVE_POSITION_TOP = _T("Top:");
	CString DIALOG_WIDTH = _T("Width:");
	CString DIALOG_HIGTH = _T("Higth:");
	CString DIALOG_SPECIFIES_SHOWN = _T("Specifies shown:");
	CString DIALOG_SHOW_HIDE_WINDOWS = _T("Show hide windows");
	CString DIALOG_REFRESH_WINDOWS_TREE = _T("Refresh windows tree");
	CString DIALOG_TREE_LOADING = _T("Loading...");
	CString DIALOG_WINDOW_STYLE = _T("Style:");
	CString DIALOG_WINDOW_STYLE_EX = _T("Extended style:");
	CString DIALOG_WINDOW_STYLE_ADVANCED = _T("Advanced");

	//Contol
	CString CONTROL_WINDOW_HANDLE = _T("Window handle:");
	CString CONTROL_TAB_COMMON = _T("Common");
	CString CONTROL_TAB_EDIT = _T("Edit");

	//SendMessage
	CString SENDMESSAGE_WINDOW_HANDLE = _T("Window handle:");
	CString SENDMESSAGE_WINDOW_CLASS_NAME = _T("Window class name:");
	CString SENDMESSAGE_WINDOW_TYPE = _T("Window type:");
	CString SENDMESSAGE_MESSAGE = _T("Message:");
	CString SENDMESSAGE_SEND = _T("Send");

	//COMMON
	CString ERROR_ = _T("ERROR:");
	CString ERROR0 = _T("Window is destroyed or its owning thread dies.");
	CString WAITING = _T("Waiting...");
	CString RETURNVALUE = _T("Return value: [VALUE]");

};

class Language
{
public:
	Language();
	~Language();
	std::vector<LanguageStruct>::const_iterator GetLanguageStruct();
	const std::vector<LanguageStruct>* GetLanguageList();
	std::vector<LanguageStruct>::const_iterator SetLanguageLCID(LCID lcid);
	std::vector<LanguageStruct>::const_iterator SetLanguageID(UINT ID);
	CString GetIniFileText(CString Section, CString KeyName, CString Default);

private:

	std::vector<LanguageStruct> LanguageArr;
	std::vector<LanguageStruct>::const_iterator SelectLanguage;

};


