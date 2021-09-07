// DlalogWindowStyle.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogWindowStyle.h"
#include "afxdialogex.h"
#include "Language.h"


// DlalogWindowStyle 对话框

IMPLEMENT_DYNAMIC(DlalogWindowStyle, CDialogEx)

DlalogWindowStyle::DlalogWindowStyle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WINDOW_STYLE, pParent)
{

}

DlalogWindowStyle::~DlalogWindowStyle()
{
}

void DlalogWindowStyle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STYLE_EDIT_HWND, EditHwnd);
	DDX_Control(pDX, IDC_STYLE_STATIC_WINDOW_HANDLE, StaticWindowHandle);
	DDX_Control(pDX, IDC_STYLE_STATIC_WINDOW_CLASS_NAME, StaticWindowClassName);
	DDX_Control(pDX, IDC_STYLE_STATIC_WINDOW_TYPE, StaticWindowType);
	DDX_Control(pDX, IDC_STYLE_COMBO_WINDOW_TYPE, ComboWindowType);
	DDX_Control(pDX, IDC_STYLE_EDIT_CLASS_NAME, EditClassName);
	//DDX_Control(pDX, IDC_LIST_STYLE_STYLE, ListStyle);
	//DDX_Control(pDX, IDC_LIST_STYLE_STYLE, ListStyle);
	DDX_Control(pDX, IDC_SYTLE_LIST_SYTLE, ListStyle);
	DDX_Control(pDX, IDC_SYTLE_LIST_SYTLE_EX, ListStyleEx);
	DDX_Control(pDX, IDC_STYLE_EDIT_STYLE, EditStyle);
	DDX_Control(pDX, IDC_STYLE_EDIT_STYLE_EX, EditStyleEx);
}


BEGIN_MESSAGE_MAP(DlalogWindowStyle, CDialogEx)
	ON_COMMAND(IDOK, &DlalogWindowStyle::OnIdok)
	ON_CBN_SELCHANGE(IDC_STYLE_COMBO_WINDOW_TYPE, &DlalogWindowStyle::OnCbnSelchangeStyleComboWindowType)
	ON_EN_CHANGE(IDC_STYLE_EDIT_HWND, &DlalogWindowStyle::OnEnChangeStyleEditHwnd)
	ON_BN_CLICKED(IDC_STYLE_BUTTON_STYLE_GET, &DlalogWindowStyle::OnBnClickedStyleButtonStyleGet)
	ON_EN_KILLFOCUS(IDC_STYLE_EDIT_STYLE, &DlalogWindowStyle::OnEnKillfocusStyleEditStyle)
//	ON_LBN_SELCHANGE(IDC_SYTLE_LIST_SYTLE, &DlalogWindowStyle::OnLbnSelchangeSytleListSytle)
	//ON_CONTROL(CLBN_CHKCHANGE, IDC_SYTLE_LIST_SYTLE, OnCheckChangeSytleListSytle)
	ON_CLBN_CHKCHANGE(IDC_SYTLE_LIST_SYTLE, &DlalogWindowStyle::OnCheckChangeSytleListSytle)
	ON_BN_CLICKED(IDC_STYLE_BUTTON_STYLE_SET, &DlalogWindowStyle::OnBnClickedStyleButtonStyleSet)
	ON_BN_CLICKED(IDC_STYLE_BUTTON_STYLE_EX_GET, &DlalogWindowStyle::OnBnClickedStyleButtonStyleExGet)
	ON_EN_KILLFOCUS(IDC_STYLE_EDIT_STYLE_EX, &DlalogWindowStyle::OnEnKillfocusStyleEditStyleEx)
	ON_CLBN_CHKCHANGE(IDC_SYTLE_LIST_SYTLE_EX, &DlalogWindowStyle::OnCheckChangeSytleListSytleEx)
	ON_BN_CLICKED(IDC_STYLE_BUTTON_STYLE_EX_SET, &DlalogWindowStyle::OnBnClickedStyleButtonStyleExSet)
	ON_EN_CHANGE(IDC_STYLE_EDIT_STYLE, &DlalogWindowStyle::OnEnChangeStyleEditStyle)
	ON_EN_CHANGE(IDC_STYLE_EDIT_STYLE_EX, &DlalogWindowStyle::OnEnChangeStyleEditStyleEx)
END_MESSAGE_MAP()


// DlalogWindowStyle 消息处理程序


void DlalogWindowStyle::OnIdok()
{
	// TODO: 在此添加命令处理程序代码
}


BOOL DlalogWindowStyle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(AllLanguage->GetLanguageStruct()->TITLE_WINDOW_STYLE);

	StaticWindowHandle.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_WINDOW_HANDLE);
	StaticWindowClassName.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_WINDOW_CLASS_NAME);
	StaticWindowType.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_WINDOW_TYPE);

	GetDlgItem(IDC_STYLE_STATIC_WINDOW_STYLE)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_STYLE);
	GetDlgItem(IDC_STYLE_STATIC_WINDOW_STYLE_EX)->SetWindowText(AllLanguage->GetLanguageStruct()->DIALOG_WINDOW_STYLE_EX);

	ListStyle.SetFont(GetFont());
	ListStyleEx.SetFont(GetFont());

	//Init window type
	ControlType.STATIC = ComboWindowType.AddString(_T("Static"));
	ControlType.COMPUTER = ComboWindowType.AddString(_T("Computer"));
	ControlType.CR = ComboWindowType.AddString(_T("C Sharp"));
	//ControlType.LINK = ComboWindowType.AddString(_T("Root"));
	ControlType.EDIT = ComboWindowType.AddString(_T("Edit"));
	//ControlType.LINK = ComboWindowType.AddString(_T("Link"));
	ControlType.MENU = ComboWindowType.AddString(_T("Menu"));
	ControlType.MFC = ComboWindowType.AddString(_T("MFC"));
	//ControlType.PROCESS = ComboWindowType.AddString(_T("Process"));
	ControlType.PROGRESSBAR = ComboWindowType.AddString(_T("Progress"));
	ControlType.WINDOW = ComboWindowType.AddString(_T("Dialog"));
	ControlType.SYSTABCONTROL32 = ComboWindowType.AddString(_T("Tab control"));
	ControlType.GROUPBOX = ComboWindowType.AddString(_T("Group box"));
	ControlType.CHECKBOX = ComboWindowType.AddString(_T("Check box"));
	ControlType.RADIOBUTTON = ComboWindowType.AddString(_T("Radio button"));
	ControlType.BUTTON = ComboWindowType.AddString(_T("Button"));
	ControlType.SYSLINK = ComboWindowType.AddString(_T("Sys link"));
	ControlType.SYSLISTVIEW32 = ComboWindowType.AddString(_T("List view"));
	ControlType.SYSHEADER32 = ComboWindowType.AddString(_T("Sys header"));
	ControlType.SCROLLBAR = ComboWindowType.AddString(_T("Scrollbar"));
	ControlType.SYSTREEVIEW32 = ComboWindowType.AddString(_T("Tree view"));
	ControlType.STATUSBAR = ComboWindowType.AddString(_T("Status bar"));
	ControlType.COMBOBOX = ComboWindowType.AddString(_T("Combo box"));
	ControlType.TRACKBAR = ComboWindowType.AddString(_T("Track bar"));
	ControlType.UPDOWN32 = ComboWindowType.AddString(_T("up/down"));
	ControlType.LISTBOX = ComboWindowType.AddString(_T("List box"));
	ControlType.TOOLBAR = ComboWindowType.AddString(_T("Tool bar"));
	ControlType.MDI = ComboWindowType.AddString(_T("MDI"));
	ControlType.DATA_TIME = ComboWindowType.AddString(_T("Data/Time Picker"));
	ControlType.ANIMATION = ComboWindowType.AddString(_T("Animation"));
	ControlType.HOT_KEY = ComboWindowType.AddString(_T("Hot Key"));
	ControlType.IP_ADDRESS = ComboWindowType.AddString(_T("IP Address"));
	ControlType.MONTH_CALENDAR = ComboWindowType.AddString(_T("Month Calendar"));

	CString hWndStr;

#ifdef _WIN64
	hWndStr.Format(_T("%llu"), OperateHWND);
#else
	hWndStr.Format(_T("%u"), OperateHWND);
#endif // _WIN64
	EditHwnd.SetWindowText(hWndStr);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlalogWindowStyle::OnCbnSelchangeStyleComboWindowType()
{
	// TODO: 在此添加控件通知处理程序代码
	int WindowType = ComboWindowType.GetCurSel();
	while (ListStyle.GetCount() > 0)
	{
		ListStyle.DeleteString(0);
	}
	while (ListStyleEx.GetCount() > 0)
	{
		ListStyleEx.DeleteString(0);
	}
	int tempInt = 0;
	if (WindowType == ControlType.WINDOW)//普通窗口样式
	{

	}
	else if (WindowType == ControlType.BUTTON || WindowType == ControlType.GROUPBOX || WindowType == ControlType.CHECKBOX || WindowType == ControlType.RADIOBUTTON)
	{
		tempInt = ListStyle.AddString(_T("BS_PUSHBUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_PUSHBUTTON);
		tempInt = ListStyle.AddString(_T("BS_DEFPUSHBUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_DEFPUSHBUTTON);
		tempInt = ListStyle.AddString(_T("BS_CHECKBOX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_CHECKBOX);
		tempInt = ListStyle.AddString(_T("BS_AUTOCHECKBOX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_AUTOCHECKBOX);
		tempInt = ListStyle.AddString(_T("BS_RADIOBUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_RADIOBUTTON);
		tempInt = ListStyle.AddString(_T("BS_3STATE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_3STATE);
		tempInt = ListStyle.AddString(_T("BS_AUTO3STATE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_AUTO3STATE);
		tempInt = ListStyle.AddString(_T("BS_GROUPBOX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_GROUPBOX);
		tempInt = ListStyle.AddString(_T("BS_USERBUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_USERBUTTON);
		tempInt = ListStyle.AddString(_T("BS_AUTORADIOBUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_AUTORADIOBUTTON);
		tempInt = ListStyle.AddString(_T("BS_PUSHBOX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_PUSHBOX);
		tempInt = ListStyle.AddString(_T("BS_OWNERDRAW"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_OWNERDRAW);
		tempInt = ListStyle.AddString(_T("BS_TYPEMASK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_TYPEMASK);
		tempInt = ListStyle.AddString(_T("BS_LEFTTEXT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_LEFTTEXT);
		tempInt = ListStyle.AddString(_T("BS_TEXT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_TEXT);
		tempInt = ListStyle.AddString(_T("BS_ICON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_ICON);
		tempInt = ListStyle.AddString(_T("BS_BITMAP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_BITMAP);
		tempInt = ListStyle.AddString(_T("BS_LEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_LEFT);
		tempInt = ListStyle.AddString(_T("BS_RIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_RIGHT);
		tempInt = ListStyle.AddString(_T("BS_CENTER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_CENTER);
		tempInt = ListStyle.AddString(_T("BS_TOP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_TOP);
		tempInt = ListStyle.AddString(_T("BS_BOTTOM"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_BOTTOM);
		tempInt = ListStyle.AddString(_T("BS_VCENTER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_VCENTER);
		tempInt = ListStyle.AddString(_T("BS_PUSHLIKE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_PUSHLIKE);
		tempInt = ListStyle.AddString(_T("BS_MULTILINE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_MULTILINE);
		tempInt = ListStyle.AddString(_T("BS_NOTIFY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_NOTIFY);
		tempInt = ListStyle.AddString(_T("BS_FLAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_FLAT);
		tempInt = ListStyle.AddString(_T("BS_RIGHTBUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)BS_RIGHTBUTTON);

	}
	else if (WindowType == ControlType.COMBOBOX)
	{
		tempInt = ListStyle.AddString(_T("CBS_SIMPLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_SIMPLE);
		tempInt = ListStyle.AddString(_T("CBS_DROPDOWN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_DROPDOWN);
		tempInt = ListStyle.AddString(_T("CBS_DROPDOWNLIST"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_DROPDOWNLIST);
		tempInt = ListStyle.AddString(_T("CBS_OWNERDRAWFIXED"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_OWNERDRAWFIXED);
		tempInt = ListStyle.AddString(_T("CBS_OWNERDRAWVARIABLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_OWNERDRAWVARIABLE);
		tempInt = ListStyle.AddString(_T("CBS_AUTOHSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_AUTOHSCROLL);
		tempInt = ListStyle.AddString(_T("CBS_OEMCONVERT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_OEMCONVERT);
		tempInt = ListStyle.AddString(_T("CBS_SORT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_SORT);
		tempInt = ListStyle.AddString(_T("CBS_HASSTRINGS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_HASSTRINGS);
		tempInt = ListStyle.AddString(_T("CBS_NOINTEGRALHEIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_NOINTEGRALHEIGHT);
		tempInt = ListStyle.AddString(_T("CBS_DISABLENOSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_DISABLENOSCROLL);
		tempInt = ListStyle.AddString(_T("CBS_UPPERCASE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_UPPERCASE);
		tempInt = ListStyle.AddString(_T("CBS_LOWERCASE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)CBS_LOWERCASE);
	}
	else if (WindowType == ControlType.LISTBOX)
	{
		tempInt = ListStyle.AddString(_T("LBS_NOTIFY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_NOTIFY);
		tempInt = ListStyle.AddString(_T("LBS_SORT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_SORT);
		tempInt = ListStyle.AddString(_T("LBS_NOREDRAW"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_NOREDRAW);
		tempInt = ListStyle.AddString(_T("LBS_MULTIPLESEL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_MULTIPLESEL);
		tempInt = ListStyle.AddString(_T("LBS_OWNERDRAWFIXED"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_OWNERDRAWFIXED);
		tempInt = ListStyle.AddString(_T("LBS_OWNERDRAWVARIABLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_OWNERDRAWVARIABLE);
		tempInt = ListStyle.AddString(_T("LBS_HASSTRINGS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_HASSTRINGS);
		tempInt = ListStyle.AddString(_T("LBS_USETABSTOPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_USETABSTOPS);
		tempInt = ListStyle.AddString(_T("LBS_NOINTEGRALHEIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_NOINTEGRALHEIGHT);
		tempInt = ListStyle.AddString(_T("LBS_MULTICOLUMN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_MULTICOLUMN);
		tempInt = ListStyle.AddString(_T("LBS_WANTKEYBOARDINPUT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_WANTKEYBOARDINPUT);
		tempInt = ListStyle.AddString(_T("LBS_EXTENDEDSEL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_EXTENDEDSEL);
		tempInt = ListStyle.AddString(_T("LBS_DISABLENOSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_DISABLENOSCROLL);
		tempInt = ListStyle.AddString(_T("LBS_NODATA"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_NODATA);
		tempInt = ListStyle.AddString(_T("LBS_NOSEL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_NOSEL);
		tempInt = ListStyle.AddString(_T("LBS_COMBOBOX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_COMBOBOX);
		tempInt = ListStyle.AddString(_T("LBS_STANDARD"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LBS_STANDARD);
	}
	else if (WindowType == ControlType.SYSLISTVIEW32)
	{
		tempInt = ListStyle.AddString(_T("LVS_ICON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_ICON);
		tempInt = ListStyle.AddString(_T("LVS_REPORT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_REPORT);
		tempInt = ListStyle.AddString(_T("LVS_SMALLICON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_SMALLICON);
		tempInt = ListStyle.AddString(_T("LVS_LIST"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_LIST);
		tempInt = ListStyle.AddString(_T("LVS_TYPEMASK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_TYPEMASK);
		tempInt = ListStyle.AddString(_T("LVS_SINGLESEL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_SINGLESEL);
		tempInt = ListStyle.AddString(_T("LVS_SHOWSELALWAYS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_SHOWSELALWAYS);
		tempInt = ListStyle.AddString(_T("LVS_SORTASCENDING"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_SORTASCENDING);
		tempInt = ListStyle.AddString(_T("LVS_SORTDESCENDING"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_SORTDESCENDING);
		tempInt = ListStyle.AddString(_T("LVS_SHAREIMAGELISTS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_SHAREIMAGELISTS);
		tempInt = ListStyle.AddString(_T("LVS_NOLABELWRAP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_NOLABELWRAP);
		tempInt = ListStyle.AddString(_T("LVS_AUTOARRANGE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_AUTOARRANGE);
		tempInt = ListStyle.AddString(_T("LVS_EDITLABELS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_EDITLABELS);
		tempInt = ListStyle.AddString(_T("LVS_OWNERDATA"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_OWNERDATA);
		tempInt = ListStyle.AddString(_T("LVS_NOSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_NOSCROLL);
		tempInt = ListStyle.AddString(_T("LVS_TYPESTYLEMASK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_TYPESTYLEMASK);
		tempInt = ListStyle.AddString(_T("LVS_ALIGNTOP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_ALIGNTOP);
		tempInt = ListStyle.AddString(_T("LVS_ALIGNLEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_ALIGNLEFT);
		tempInt = ListStyle.AddString(_T("LVS_ALIGNMASK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_ALIGNMASK);
		tempInt = ListStyle.AddString(_T("LVS_OWNERDRAWFIXED"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_OWNERDRAWFIXED);
		tempInt = ListStyle.AddString(_T("LVS_NOCOLUMNHEADER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_NOCOLUMNHEADER);
		tempInt = ListStyle.AddString(_T("LVS_NOSORTHEADER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LVS_NOSORTHEADER);
		tempInt = ListStyle.AddString(_T("TVS_HASBUTTONS"));
	}
	else if (WindowType == ControlType.PROGRESSBAR)
	{
		tempInt = ListStyle.AddString(_T("PBS_SMOOTH"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)PBS_SMOOTH);
		tempInt = ListStyle.AddString(_T("PBS_VERTICAL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)PBS_VERTICAL);
		tempInt = ListStyle.AddString(_T("PBS_MARQUEE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)PBS_MARQUEE);
		tempInt = ListStyle.AddString(_T("PBS_SMOOTHREVERSE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)PBS_SMOOTHREVERSE);
	}
	else if (WindowType == ControlType.EDIT)
	{
		tempInt = ListStyle.AddString(_T("ES_LEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_LEFT);
		tempInt = ListStyle.AddString(_T("ES_CENTER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_CENTER);
		tempInt = ListStyle.AddString(_T("ES_RIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_RIGHT);
		tempInt = ListStyle.AddString(_T("ES_MULTILINE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_MULTILINE);
		tempInt = ListStyle.AddString(_T("ES_UPPERCASE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_UPPERCASE);
		tempInt = ListStyle.AddString(_T("ES_LOWERCASE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_LOWERCASE);
		tempInt = ListStyle.AddString(_T("ES_PASSWORD"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_PASSWORD);
		tempInt = ListStyle.AddString(_T("ES_AUTOVSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_AUTOVSCROLL);
		tempInt = ListStyle.AddString(_T("ES_AUTOHSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_AUTOHSCROLL);
		tempInt = ListStyle.AddString(_T("ES_NOHIDESEL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_NOHIDESEL);
		tempInt = ListStyle.AddString(_T("ES_OEMCONVERT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_OEMCONVERT);
		tempInt = ListStyle.AddString(_T("ES_READONLY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_READONLY);
		tempInt = ListStyle.AddString(_T("ES_WANTRETURN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_WANTRETURN);
		tempInt = ListStyle.AddString(_T("ES_NUMBER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ES_NUMBER);
	}
	else if (WindowType == ControlType.ANIMATION)
	{
		tempInt = ListStyle.AddString(_T("ACS_CENTER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ACS_CENTER);
		tempInt = ListStyle.AddString(_T("ACS_TRANSPARENT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ACS_TRANSPARENT);
		tempInt = ListStyle.AddString(_T("ACS_AUTOPLAY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ACS_AUTOPLAY);
		tempInt = ListStyle.AddString(_T("ACS_TIMER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)ACS_TIMER);
	}
	else if (WindowType == ControlType.DATA_TIME)
	{
		tempInt = ListStyle.AddString(_T("DTS_UPDOWN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_UPDOWN);
		tempInt = ListStyle.AddString(_T("DTS_SHOWNONE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_SHOWNONE);
		tempInt = ListStyle.AddString(_T("DTS_SHORTDATEFORMAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_SHORTDATEFORMAT);
		tempInt = ListStyle.AddString(_T("DTS_LONGDATEFORMAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_LONGDATEFORMAT);
		tempInt = ListStyle.AddString(_T("DTS_SHORTDATECENTURYFORMAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_SHORTDATECENTURYFORMAT);
		tempInt = ListStyle.AddString(_T("DTS_TIMEFORMAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_TIMEFORMAT);
		tempInt = ListStyle.AddString(_T("DTS_APPCANPARSE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_APPCANPARSE);
		tempInt = ListStyle.AddString(_T("DTS_RIGHTALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)DTS_RIGHTALIGN);
	}
	else if (WindowType == ControlType.HOT_KEY)
	{

	}
	else if (WindowType == ControlType.SYSTREEVIEW32)
	{
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_HASBUTTONS);
		tempInt = ListStyle.AddString(_T("TVS_HASLINES"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_HASLINES);
		tempInt = ListStyle.AddString(_T("TVS_LINESATROOT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_LINESATROOT);
		tempInt = ListStyle.AddString(_T("TVS_EDITLABELS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_EDITLABELS);
		tempInt = ListStyle.AddString(_T("TVS_DISABLEDRAGDROP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_DISABLEDRAGDROP);
		tempInt = ListStyle.AddString(_T("TVS_SHOWSELALWAYS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_SHOWSELALWAYS);
		tempInt = ListStyle.AddString(_T("TVS_RTLREADING"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_RTLREADING);
		tempInt = ListStyle.AddString(_T("TVS_NOTOOLTIPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_NOTOOLTIPS);
		tempInt = ListStyle.AddString(_T("TVS_CHECKBOXES"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_CHECKBOXES);
		tempInt = ListStyle.AddString(_T("TVS_TRACKSELECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_TRACKSELECT);
		tempInt = ListStyle.AddString(_T("TVS_SINGLEEXPAND"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_SINGLEEXPAND);
		tempInt = ListStyle.AddString(_T("TVS_INFOTIP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_INFOTIP);
		tempInt = ListStyle.AddString(_T("TVS_FULLROWSELECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_FULLROWSELECT);
		tempInt = ListStyle.AddString(_T("TVS_NOSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_NOSCROLL);
		tempInt = ListStyle.AddString(_T("TVS_NONEVENHEIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_NONEVENHEIGHT);
		tempInt = ListStyle.AddString(_T("TVS_NOHSCROLL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TVS_NOHSCROLL); // TVS_NOSCROLL overrides this

		tempInt = ListStyleEx.AddString(_T("TVS_EX_MULTISELECT"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_MULTISELECT);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_DOUBLEBUFFER"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_DOUBLEBUFFER);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_NOINDENTSTATE"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_NOINDENTSTATE);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_RICHTOOLTIP"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_RICHTOOLTIP);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_AUTOHSCROLL"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_AUTOHSCROLL);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_FADEINOUTEXPANDOS"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_FADEINOUTEXPANDOS);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_PARTIALCHECKBOXES"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_PARTIALCHECKBOXES);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_EXCLUSIONCHECKBOXES"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_EXCLUSIONCHECKBOXES);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_DIMMEDCHECKBOXES"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_DIMMEDCHECKBOXES);
		tempInt = ListStyleEx.AddString(_T("TVS_EX_DRAWIMAGEASYNC"));
		ListStyleEx.SetItemData(tempInt, (DWORD_PTR)TVS_EX_DRAWIMAGEASYNC);
	}
	else if (WindowType == ControlType.SCROLLBAR)
	{
		tempInt = ListStyle.AddString(_T("SBS_HORZ"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_HORZ);
		tempInt = ListStyle.AddString(_T("SBS_VERT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_VERT);
		tempInt = ListStyle.AddString(_T("SBS_TOPALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_TOPALIGN);
		tempInt = ListStyle.AddString(_T("SBS_LEFTALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_LEFTALIGN);
		tempInt = ListStyle.AddString(_T("SBS_BOTTOMALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_BOTTOMALIGN);
		tempInt = ListStyle.AddString(_T("SBS_RIGHTALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_RIGHTALIGN);
		tempInt = ListStyle.AddString(_T("SBS_SIZEBOXTOPLEFTALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_SIZEBOXTOPLEFTALIGN);
		tempInt = ListStyle.AddString(_T("SBS_SIZEBOXBOTTOMRIGHTALIGN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_SIZEBOXBOTTOMRIGHTALIGN);
		tempInt = ListStyle.AddString(_T("SBS_SIZEBOX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_SIZEBOX);
		tempInt = ListStyle.AddString(_T("SBS_SIZEGRIP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBS_SIZEGRIP);
	}
	else if (WindowType == ControlType.STATIC)
	{
		tempInt = ListStyle.AddString(_T("SS_LEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_LEFT);
		tempInt = ListStyle.AddString(_T("SS_CENTER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_CENTER);
		tempInt = ListStyle.AddString(_T("SS_RIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_RIGHT);
		tempInt = ListStyle.AddString(_T("SS_ICON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ICON);
		tempInt = ListStyle.AddString(_T("SS_BLACKRECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_BLACKRECT);
		tempInt = ListStyle.AddString(_T("SS_GRAYRECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_GRAYRECT);
		tempInt = ListStyle.AddString(_T("SS_WHITERECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_WHITERECT);
		tempInt = ListStyle.AddString(_T("SS_BLACKFRAME"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_BLACKFRAME);
		tempInt = ListStyle.AddString(_T("SS_GRAYFRAME"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_GRAYFRAME);
		tempInt = ListStyle.AddString(_T("SS_WHITEFRAME"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_WHITEFRAME);
		tempInt = ListStyle.AddString(_T("SS_USERITEM"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_USERITEM);
		tempInt = ListStyle.AddString(_T("SS_SIMPLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_SIMPLE);
		tempInt = ListStyle.AddString(_T("SS_LEFTNOWORDWRAP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_LEFTNOWORDWRAP);
		tempInt = ListStyle.AddString(_T("SS_OWNERDRAW"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_OWNERDRAW);
		tempInt = ListStyle.AddString(_T("SS_BITMAP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_BITMAP);
		tempInt = ListStyle.AddString(_T("SS_ENHMETAFILE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ENHMETAFILE);
		tempInt = ListStyle.AddString(_T("SS_ETCHEDHORZ"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ETCHEDHORZ);
		tempInt = ListStyle.AddString(_T("SS_ETCHEDVERT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ETCHEDVERT);
		tempInt = ListStyle.AddString(_T("SS_ETCHEDFRAME"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ETCHEDFRAME);
		tempInt = ListStyle.AddString(_T("SS_TYPEMASK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_TYPEMASK);
		tempInt = ListStyle.AddString(_T("SS_REALSIZECONTROL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_REALSIZECONTROL);
		tempInt = ListStyle.AddString(_T("SS_NOPREFIX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_NOPREFIX);
		tempInt = ListStyle.AddString(_T("SS_NOTIFY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_NOTIFY);
		tempInt = ListStyle.AddString(_T("SS_CENTERIMAGE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_CENTERIMAGE);
		tempInt = ListStyle.AddString(_T("SS_RIGHTJUST"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_RIGHTJUST);
		tempInt = ListStyle.AddString(_T("SS_REALSIZEIMAGE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_REALSIZEIMAGE);
		tempInt = ListStyle.AddString(_T("SS_SUNKEN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_SUNKEN);
		tempInt = ListStyle.AddString(_T("SS_EDITCONTROL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_EDITCONTROL);
		tempInt = ListStyle.AddString(_T("SS_ENDELLIPSIS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ENDELLIPSIS);
		tempInt = ListStyle.AddString(_T("SS_PATHELLIPSIS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_PATHELLIPSIS);
		tempInt = ListStyle.AddString(_T("SS_WORDELLIPSIS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_WORDELLIPSIS);
		tempInt = ListStyle.AddString(_T("SS_ELLIPSISMASK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SS_ELLIPSISMASK);
	}
	else if (WindowType == ControlType.COMPUTER)
	{
	
	}
	else if (WindowType == ControlType.CR)
	{
	
	}
	else if (WindowType == ControlType.DESKTOP)
	{
	
	}
	//	else if (WindowType == ControlType.LINK)
	//	{
	//	
	//	}
	else if (WindowType == ControlType.MENU)
	{
	
	}
	else if (WindowType == ControlType.MFC)
	{
	
	}
	else if (WindowType == ControlType.PROCESS)
	{
	
	}
	else if (WindowType == ControlType.WINDOW)
	{
	
	}
	else if (WindowType == ControlType.SYSTABCONTROL32)
	{
		tempInt = ListStyle.AddString(_T("TCS_SCROLLOPPOSITE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_SCROLLOPPOSITE);
		tempInt = ListStyle.AddString(_T("TCS_BOTTOM"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_BOTTOM);
		tempInt = ListStyle.AddString(_T("TCS_RIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_RIGHT);
		tempInt = ListStyle.AddString(_T("TCS_MULTISELECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_MULTISELECT);
		tempInt = ListStyle.AddString(_T("TCS_FLATBUTTONS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_FLATBUTTONS);
		tempInt = ListStyle.AddString(_T("TCS_FORCEICONLEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_FORCEICONLEFT);
		tempInt = ListStyle.AddString(_T("TCS_FORCELABELLEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_FORCELABELLEFT);
		tempInt = ListStyle.AddString(_T("TCS_HOTTRACK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_HOTTRACK);
		tempInt = ListStyle.AddString(_T("TCS_VERTICAL"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_VERTICAL);
		tempInt = ListStyle.AddString(_T("TCS_TABS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_TABS);
		tempInt = ListStyle.AddString(_T("TCS_BUTTONS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_BUTTONS);
		tempInt = ListStyle.AddString(_T("TCS_SINGLELINE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_SINGLELINE);
		tempInt = ListStyle.AddString(_T("TCS_MULTILINE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_MULTILINE);
		tempInt = ListStyle.AddString(_T("TCS_RIGHTJUSTIFY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_RIGHTJUSTIFY);
		tempInt = ListStyle.AddString(_T("TCS_FIXEDWIDTH"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_FIXEDWIDTH);
		tempInt = ListStyle.AddString(_T("TCS_RAGGEDRIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_RAGGEDRIGHT);
		tempInt = ListStyle.AddString(_T("TCS_FOCUSONBUTTONDOWN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_FOCUSONBUTTONDOWN);
		tempInt = ListStyle.AddString(_T("TCS_OWNERDRAWFIXED"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_OWNERDRAWFIXED);
		tempInt = ListStyle.AddString(_T("TCS_TOOLTIPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_TOOLTIPS);
		tempInt = ListStyle.AddString(_T("TCS_FOCUSNEVER"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TCS_FOCUSNEVER);
	}
	else if (WindowType == ControlType.SYSLINK)
	{
		tempInt = ListStyle.AddString(_T("LWS_TRANSPARENT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LWS_TRANSPARENT);
		tempInt = ListStyle.AddString(_T("LWS_IGNORERETURN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LWS_IGNORERETURN);
		tempInt = ListStyle.AddString(_T("LWS_NOPREFIX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LWS_NOPREFIX);
		tempInt = ListStyle.AddString(_T("LWS_USEVISUALSTYLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LWS_USEVISUALSTYLE);
		tempInt = ListStyle.AddString(_T("LWS_USECUSTOMTEXT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LWS_USECUSTOMTEXT);
		tempInt = ListStyle.AddString(_T("LWS_RIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)LWS_RIGHT);
	}
	else if (WindowType == ControlType.SYSHEADER32)
	{
		tempInt = ListStyle.AddString(_T("HDS_HORZ"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_HORZ);
		tempInt = ListStyle.AddString(_T("HDS_BUTTONS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_BUTTONS);
		tempInt = ListStyle.AddString(_T("HDS_HOTTRACK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_HOTTRACK);
		tempInt = ListStyle.AddString(_T("HDS_HIDDEN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_HIDDEN);
		tempInt = ListStyle.AddString(_T("HDS_DRAGDROP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_DRAGDROP);
		tempInt = ListStyle.AddString(_T("HDS_FULLDRAG"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_FULLDRAG);
		tempInt = ListStyle.AddString(_T("HDS_FILTERBAR"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_FILTERBAR);
		tempInt = ListStyle.AddString(_T("HDS_FLAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_FLAT);
		tempInt = ListStyle.AddString(_T("HDS_CHECKBOXES"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_CHECKBOXES);
		tempInt = ListStyle.AddString(_T("HDS_NOSIZING"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_NOSIZING);
		tempInt = ListStyle.AddString(_T("HDS_OVERFLOW"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)HDS_OVERFLOW);
	}
	else if (WindowType == ControlType.STATUSBAR)
	{
		tempInt = ListStyle.AddString(_T("SBARS_SIZEGRIP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBARS_SIZEGRIP);
		tempInt = ListStyle.AddString(_T("SBARS_TOOLTIPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBARS_TOOLTIPS);
		tempInt = ListStyle.AddString(_T("SBT_TOOLTIPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)SBT_TOOLTIPS);
	}
	else if (WindowType == ControlType.TRACKBAR)
	{
		tempInt = ListStyle.AddString(_T("TBS_AUTOTICKS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_AUTOTICKS);
		tempInt = ListStyle.AddString(_T("TBS_VERT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_VERT);
		tempInt = ListStyle.AddString(_T("TBS_HORZ"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_HORZ);
		tempInt = ListStyle.AddString(_T("TBS_TOP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_TOP);
		tempInt = ListStyle.AddString(_T("TBS_BOTTOM"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_BOTTOM);
		tempInt = ListStyle.AddString(_T("TBS_LEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_LEFT);
		tempInt = ListStyle.AddString(_T("TBS_RIGHT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_RIGHT);
		tempInt = ListStyle.AddString(_T("TBS_BOTH"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_BOTH);
		tempInt = ListStyle.AddString(_T("TBS_NOTICKS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_NOTICKS);
		tempInt = ListStyle.AddString(_T("TBS_ENABLESELRANGE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_ENABLESELRANGE);
		tempInt = ListStyle.AddString(_T("TBS_FIXEDLENGTH"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_FIXEDLENGTH);
		tempInt = ListStyle.AddString(_T("TBS_NOTHUMB"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_NOTHUMB);
		tempInt = ListStyle.AddString(_T("TBS_TOOLTIPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_TOOLTIPS);
		tempInt = ListStyle.AddString(_T("TBS_REVERSED"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_REVERSED);
		tempInt = ListStyle.AddString(_T("TBS_DOWNISLEFT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_DOWNISLEFT);
		tempInt = ListStyle.AddString(_T("TBS_NOTIFYBEFOREMOVE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_NOTIFYBEFOREMOVE);
		tempInt = ListStyle.AddString(_T("TBS_TRANSPARENTBKGND"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBS_TRANSPARENTBKGND);
	}
	else if (WindowType == ControlType.UPDOWN32)
	{
		tempInt = ListStyle.AddString(_T("TBSTYLE_BUTTON"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_BUTTON);
		tempInt = ListStyle.AddString(_T("TBSTYLE_SEP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_SEP);
		tempInt = ListStyle.AddString(_T("TBSTYLE_CHECK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_CHECK);
		tempInt = ListStyle.AddString(_T("TBSTYLE_GROUP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_GROUP);
		tempInt = ListStyle.AddString(_T("TBSTYLE_CHECKGROUP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_CHECKGROUP);
		tempInt = ListStyle.AddString(_T("TBSTYLE_DROPDOWN"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_DROPDOWN);
		tempInt = ListStyle.AddString(_T("TBSTYLE_AUTOSIZE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_AUTOSIZE);
		tempInt = ListStyle.AddString(_T("TBSTYLE_NOPREFIX"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_NOPREFIX);
		tempInt = ListStyle.AddString(_T("TBSTYLE_TOOLTIPS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_TOOLTIPS);
		tempInt = ListStyle.AddString(_T("TBSTYLE_WRAPABLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_WRAPABLE);
		tempInt = ListStyle.AddString(_T("TBSTYLE_ALTDRAG"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_ALTDRAG);
		tempInt = ListStyle.AddString(_T("TBSTYLE_FLAT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_FLAT);
		tempInt = ListStyle.AddString(_T("TBSTYLE_LIST"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_LIST);
		tempInt = ListStyle.AddString(_T("TBSTYLE_CUSTOMERASE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_CUSTOMERASE);
		tempInt = ListStyle.AddString(_T("TBSTYLE_REGISTERDROP"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_REGISTERDROP);
		tempInt = ListStyle.AddString(_T("TBSTYLE_TRANSPARENT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)TBSTYLE_TRANSPARENT);
	}
	else if (WindowType == ControlType.TOOLBAR)
	{
	
	}
	else if (WindowType == ControlType.MDI)
	{
	
	}
	else if (WindowType == ControlType.IP_ADDRESS)
	{
	
	}
	else if (WindowType == ControlType.MONTH_CALENDAR)
	{
		tempInt = ListStyle.AddString(_T("MCS_DAYSTATE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_DAYSTATE);
		tempInt = ListStyle.AddString(_T("MCS_MULTISELECT"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_MULTISELECT);
		tempInt = ListStyle.AddString(_T("MCS_WEEKNUMBERS"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_WEEKNUMBERS);
		tempInt = ListStyle.AddString(_T("MCS_NOTODAYCIRCLE"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_NOTODAYCIRCLE);
		tempInt = ListStyle.AddString(_T("MCS_NOTODAY"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_NOTODAY);
		tempInt = ListStyle.AddString(_T("MCS_NOTRAILINGDATES"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_NOTRAILINGDATES);
		tempInt = ListStyle.AddString(_T("MCS_SHORTDAYSOFWEEK"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_SHORTDAYSOFWEEK);
		tempInt = ListStyle.AddString(_T("MCS_NOSELCHANGEONNAV"));
		ListStyle.SetItemData(tempInt, (DWORD_PTR)MCS_NOSELCHANGEONNAV);
	}
	else if (WindowType == ControlType.COMPUTER)
	{
	
	}
	//COMMON
	tempInt = ListStyle.AddString(_T("WS_OVERLAPPED"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_OVERLAPPED);
	tempInt = ListStyle.AddString(_T("WS_POPUP"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_POPUP);
	tempInt = ListStyle.AddString(_T("WS_CHILD"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_CHILD);
	tempInt = ListStyle.AddString(_T("WS_MINIMIZE"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_MINIMIZE);
	tempInt = ListStyle.AddString(_T("WS_VISIBLE"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_VISIBLE);
	tempInt = ListStyle.AddString(_T("WS_DISABLED"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_DISABLED);
	tempInt = ListStyle.AddString(_T("WS_CLIPSIBLINGS"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_CLIPSIBLINGS);
	tempInt = ListStyle.AddString(_T("WS_CLIPCHILDREN"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_CLIPCHILDREN);
	tempInt = ListStyle.AddString(_T("WS_MAXIMIZE"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_MAXIMIZE);
	tempInt = ListStyle.AddString(_T("WS_CAPTION"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_CAPTION); /* WS_BORDER | WS_DLGFRAME  */
	tempInt = ListStyle.AddString(_T("WS_BORDER"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_BORDER);
	tempInt = ListStyle.AddString(_T("WS_DLGFRAME"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_DLGFRAME);
	tempInt = ListStyle.AddString(_T("WS_VSCROLL"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_VSCROLL);
	tempInt = ListStyle.AddString(_T("WS_HSCROLL"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_HSCROLL);
	tempInt = ListStyle.AddString(_T("WS_SYSMENU"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_SYSMENU);
	tempInt = ListStyle.AddString(_T("WS_THICKFRAME"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_THICKFRAME);
	tempInt = ListStyle.AddString(_T("WS_GROUP"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_GROUP);
	tempInt = ListStyle.AddString(_T("WS_TABSTOP"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_TABSTOP);
	tempInt = ListStyle.AddString(_T("WS_MINIMIZEBOX"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_MINIMIZEBOX);
	tempInt = ListStyle.AddString(_T("WS_MAXIMIZEBOX"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_MAXIMIZEBOX);
	tempInt = ListStyle.AddString(_T("WS_TILED"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_TILED);
	tempInt = ListStyle.AddString(_T("WS_ICONIC"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_ICONIC);
	tempInt = ListStyle.AddString(_T("WS_SIZEBOX"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_SIZEBOX);
	tempInt = ListStyle.AddString(_T("WS_TILEDWINDOW"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_TILEDWINDOW);
	tempInt = ListStyle.AddString(_T("WS_OVERLAPPEDWINDOW"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_OVERLAPPEDWINDOW);
	tempInt = ListStyle.AddString(_T("WS_POPUPWINDOW"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_POPUPWINDOW);
	tempInt = ListStyle.AddString(_T("WS_CHILDWINDOW"));
	ListStyle.SetItemData(tempInt, (DWORD_PTR)WS_CHILDWINDOW);

	tempInt = ListStyleEx.AddString(_T("WS_EX_DLGMODALFRAME"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_DLGMODALFRAME);
	tempInt = ListStyleEx.AddString(_T("WS_EX_NOPARENTNOTIFY"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_NOPARENTNOTIFY);
	tempInt = ListStyleEx.AddString(_T("WS_EX_TOPMOST"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_TOPMOST);
	tempInt = ListStyleEx.AddString(_T("WS_EX_ACCEPTFILES"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_ACCEPTFILES);
	tempInt = ListStyleEx.AddString(_T("WS_EX_TRANSPARENT"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_TRANSPARENT);
	tempInt = ListStyleEx.AddString(_T("WS_EX_MDICHILD"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_MDICHILD);
	tempInt = ListStyleEx.AddString(_T("WS_EX_TOOLWINDOW"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_TOOLWINDOW);
	tempInt = ListStyleEx.AddString(_T("WS_EX_WINDOWEDGE"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_WINDOWEDGE);
	tempInt = ListStyleEx.AddString(_T("WS_EX_CLIENTEDGE"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_CLIENTEDGE);
	tempInt = ListStyleEx.AddString(_T("WS_EX_CONTEXTHELP"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_CONTEXTHELP);
	tempInt = ListStyleEx.AddString(_T("WS_EX_RIGHT"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_RIGHT);
	tempInt = ListStyleEx.AddString(_T("WS_EX_LEFT"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_LEFT);
	tempInt = ListStyleEx.AddString(_T("WS_EX_RTLREADING"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_RTLREADING);
	tempInt = ListStyleEx.AddString(_T("WS_EX_LTRREADING"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_LTRREADING);
	tempInt = ListStyleEx.AddString(_T("WS_EX_LEFTSCROLLBAR"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_LEFTSCROLLBAR);
	tempInt = ListStyleEx.AddString(_T("WS_EX_RIGHTSCROLLBAR"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_RIGHTSCROLLBAR);
	tempInt = ListStyleEx.AddString(_T("WS_EX_CONTROLPARENT"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_CONTROLPARENT);
	tempInt = ListStyleEx.AddString(_T("WS_EX_STATICEDGE"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_STATICEDGE);
	tempInt = ListStyleEx.AddString(_T("WS_EX_APPWINDOW"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_APPWINDOW);
	tempInt = ListStyleEx.AddString(_T("WS_EX_OVERLAPPEDWINDOW"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_OVERLAPPEDWINDOW);
	tempInt = ListStyleEx.AddString(_T("WS_EX_PALETTEWINDOW"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_PALETTEWINDOW);
	tempInt = ListStyleEx.AddString(_T("WS_EX_LAYERED"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_LAYERED);
	tempInt = ListStyleEx.AddString(_T("WS_EX_NOINHERITLAYOUT"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_NOINHERITLAYOUT);
#if(WINVER >= 0x0602)
	tempInt = ListStyleEx.AddString(_T("WS_EX_NOREDIRECTIONBITMAP"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_NOREDIRECTIONBITMAP);
#endif /* WINVER >= 0x0602 */
	tempInt = ListStyleEx.AddString(_T("WS_EX_LAYOUTRTL"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_LAYOUTRTL);
	tempInt = ListStyleEx.AddString(_T("WS_EX_COMPOSITED"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_COMPOSITED);
	tempInt = ListStyleEx.AddString(_T("WS_EX_NOACTIVATE"));
	ListStyleEx.SetItemData(tempInt, (DWORD_PTR)WS_EX_NOACTIVATE);

	//Get window style
	OnBnClickedStyleButtonStyleGet();
	OnBnClickedStyleButtonStyleExGet();
}


void DlalogWindowStyle::OnEnChangeStyleEditHwnd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString TempString;
	HWND hWnd = NULL;
	EditHwnd.GetWindowText(TempString);
#ifdef _WIN64
	int i_ret = _stscanf(TempString, _T("%llu"), (ULONG_PTR)&hWnd);
#else
	int i_ret = _stscanf(TempString, _T("%u"), (ULONG_PTR)&hWnd);
#endif // _WIN64
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	TempString = _T("");
	::RealGetWindowClass(hWnd, TempString.GetBuffer(50), 50);
	TempString.ReleaseBuffer();
	EditClassName.SetWindowText(TempString);

	ComboWindowType.SetCurSel(GetControlTypeID(OperateHWND, TempString, ControlType));
	//init style list
	OnCbnSelchangeStyleComboWindowType();
}

//Style
void DlalogWindowStyle::OnBnClickedStyleButtonStyleGet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!OnEnChangeStyleEditStyleIng)
	{
		CString TempString;
		HWND hWnd = NULL;
		EditHwnd.GetWindowText(TempString);
#ifdef _WIN64
		int i_ret = _stscanf(TempString, _T("%llu"), (ULONG_PTR)&hWnd);
#else
		int i_ret = _stscanf(TempString, _T("%u"), (ULONG_PTR)&hWnd);
#endif // _WIN64
		if (i_ret == 0 || hWnd == NULL)
		{
			OnEnChangeStyleEditStyle();
			return;
		}
		LONG WindowLong = ::GetWindowLong(hWnd, GWL_STYLE);
		TempString.Format(_T("%08lX"), WindowLong);
		EditStyle.SetWindowText(TempString);
		OnEnChangeStyleEditStyle();
	}
}


void DlalogWindowStyle::OnEnKillfocusStyleEditStyle()
{
	// TODO: 在此添加控件通知处理程序代码
// 	CString TempString;
// 	EditStyle.GetWindowText(TempString);
// 	LONG WindowLong = 0;
// 	int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
// 	if (i_ret == 0)
// 	{
// 		WindowLong = 0;
// 	}
// 	for (int i = 0; i < ListStyle.GetCount(); i++)
// 	{
// 		LONG LocalLong = (LONG)ListStyle.GetItemData(i);
// 		if ((WindowLong & LocalLong) == LocalLong)
// 		{
// 			ListStyle.SetCheck(i, BST_CHECKED);
// 		}
// 		else
// 		{
// 			ListStyle.SetCheck(i, BST_UNCHECKED);
// 		}
// 	}
}

void DlalogWindowStyle::OnCheckChangeSytleListSytle()
{
	CString TempString;
	EditStyle.GetWindowText(TempString);
	LONG WindowLong = 0;
	int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
	if (i_ret == 0)
	{
		WindowLong = 0;
	}

	int sel = ListStyle.GetCurSel();
	if (ListStyle.GetCheck(sel) == BST_CHECKED)
	{
		WindowLong |= (LONG)ListStyle.GetItemData(sel);
	}
	else
	{
		LONG temptest = (LONG)ListStyle.GetItemData(sel);
		WindowLong &= ~temptest;
	}
	TempString.Format(_T("%08lX"), WindowLong);
	EditStyle.SetWindowText(TempString);
	OnEnKillfocusStyleEditStyle();
}


void DlalogWindowStyle::OnBnClickedStyleButtonStyleSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString;
	EditStyle.GetWindowText(TempString);
	LONG WindowLong = 0;
	int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
	if (i_ret == 0)
	{
		WindowLong = 0;
	}
	HWND hWnd = NULL;
	EditHwnd.GetWindowText(TempString);
#ifdef _WIN64
	i_ret = _stscanf(TempString, _T("%llu"), (ULONG_PTR)&hWnd);
#else
	i_ret = _stscanf(TempString, _T("%u"), (ULONG_PTR)&hWnd);
#endif // _WIN64
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SetWindowLong(hWnd, GWL_STYLE, WindowLong);
	::InvalidateRect(hWnd, NULL, TRUE);
	OnBnClickedStyleButtonStyleGet();
}


//StyleEx
void DlalogWindowStyle::OnBnClickedStyleButtonStyleExGet()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!OnEnChangeStyleEditStyleExIng)
	{
		CString TempString;
		HWND hWnd = NULL;
		EditHwnd.GetWindowText(TempString);
#ifdef _WIN64
		int i_ret = _stscanf(TempString, _T("%llu"), (ULONG_PTR)&hWnd);
#else
		int i_ret = _stscanf(TempString, _T("%u"), (ULONG_PTR)&hWnd);
#endif // _WIN64
		if (i_ret == 0 || hWnd == NULL)
		{
			OnEnChangeStyleEditStyleEx();
			return;
		}
		LONG WindowLong = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		TempString.Format(_T("%08lX"), WindowLong);
		EditStyleEx.SetWindowText(TempString);
		OnEnChangeStyleEditStyleEx();
	}
}


void DlalogWindowStyle::OnEnKillfocusStyleEditStyleEx()
{
	// TODO: 在此添加控件通知处理程序代码
// 	CString TempString;
// 	EditStyleEx.GetWindowText(TempString);
// 	LONG WindowLong = 0;
// 	int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
// 	if (i_ret == 0)
// 	{
// 		WindowLong = 0;
// 	}
// 	for (int i = 0; i < ListStyleEx.GetCount(); i++)
// 	{
// 		LONG LocalLong = (LONG)ListStyleEx.GetItemData(i);
// 		if ((WindowLong & LocalLong) == LocalLong)
// 		{
// 			ListStyleEx.SetCheck(i, BST_CHECKED);
// 		}
// 		else
// 		{
// 			ListStyleEx.SetCheck(i, BST_UNCHECKED);
// 		}
// 	}
}

void DlalogWindowStyle::OnCheckChangeSytleListSytleEx()
{
	CString TempString;
	EditStyleEx.GetWindowText(TempString);
	LONG WindowLong = 0;
	int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
	if (i_ret == 0)
	{
		WindowLong = 0;
	}

	int sel = ListStyleEx.GetCurSel();
	if (ListStyleEx.GetCheck(sel) == BST_CHECKED)
	{
		WindowLong |= (LONG)ListStyleEx.GetItemData(sel);
	}
	else
	{
		LONG temptest = (LONG)ListStyleEx.GetItemData(sel);
		WindowLong &= ~temptest;
	}
	TempString.Format(_T("%08lX"), WindowLong);
	EditStyleEx.SetWindowText(TempString);
	OnEnKillfocusStyleEditStyleEx();
}

void DlalogWindowStyle::OnBnClickedStyleButtonStyleExSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString;
	EditStyleEx.GetWindowText(TempString);
	LONG WindowLong = 0;
	int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
	if (i_ret == 0)
	{
		WindowLong = 0;
	}
	HWND hWnd = NULL;
	EditHwnd.GetWindowText(TempString);
#ifdef _WIN64
	i_ret = _stscanf(TempString, _T("%llu"), (ULONG_PTR)&hWnd);
#else
	i_ret = _stscanf(TempString, _T("%u"), (ULONG_PTR)&hWnd);
#endif // _WIN64
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SetWindowLong(hWnd, GWL_EXSTYLE, WindowLong);
	::InvalidateRect(hWnd, NULL, TRUE);
	OnBnClickedStyleButtonStyleExGet();
}


void DlalogWindowStyle::OnEnChangeStyleEditStyle()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (!OnEnChangeStyleEditStyleIng)
	{
		OnEnChangeStyleEditStyleIng = TRUE;
		CString TempString;
		EditStyle.GetWindowText(TempString);
		LONG WindowLong = 0;
		int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
		if (i_ret == 0)
		{
			WindowLong = 0;
		}
		for (int i = 0; i < ListStyle.GetCount(); i++)
		{
			LONG LocalLong = (LONG)ListStyle.GetItemData(i);
			if ((WindowLong & LocalLong) == LocalLong)
			{
				ListStyle.SetCheck(i, BST_CHECKED);
			}
			else
			{
				ListStyle.SetCheck(i, BST_UNCHECKED);
			}
		}
		OnEnChangeStyleEditStyleIng = FALSE;
	}
}


void DlalogWindowStyle::OnEnChangeStyleEditStyleEx()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (!OnEnChangeStyleEditStyleExIng)
	{
		OnEnChangeStyleEditStyleExIng = TRUE;
		CString TempString;
		EditStyleEx.GetWindowText(TempString);
		LONG WindowLong = 0;
		int i_ret = _stscanf(TempString, _T("%lx"), &WindowLong);
		if (i_ret == 0)
		{
			WindowLong = 0;
		}
		for (int i = 0; i < ListStyleEx.GetCount(); i++)
		{
			LONG LocalLong = (LONG)ListStyleEx.GetItemData(i);
			if ((WindowLong & LocalLong) == LocalLong)
			{
				ListStyleEx.SetCheck(i, BST_CHECKED);
			}
			else
			{
				ListStyleEx.SetCheck(i, BST_UNCHECKED);
			}
		}
		OnEnChangeStyleEditStyleExIng = FALSE;
	}
}
