// DlalogSendMessage.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogSendMessage.h"
#include "afxdialogex.h"
#include "Language.h"
#include <lmerr.h>


// DlalogSendMessage 对话框

IMPLEMENT_DYNAMIC(DlalogSendMessage, CDialogEx)

DlalogSendMessage::DlalogSendMessage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SEND_MESSAGE, pParent)
{

}

DlalogSendMessage::~DlalogSendMessage()
{
}

void DlalogSendMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SMSG_EDIT_HWND, EditHwnd);
	//DDX_Control(pDX, IDC_SMSG_EDIT_CLASS_NAME, EditClassName);
	//DDX_Control(pDX, IDC_SMSG_COMBO_WINDOW_TYPE, ComboWindowType);
	DDX_Control(pDX, IDC_SMSG_COMBO_MESSAGE, ComboMessage);
	DDX_Control(pDX, IDC_SMSG_BUTTON_SEND, ButtonSend);
	DDX_Control(pDX, IDC_SMSG_EDIT_CLASS_NAME, EditClassName);
	DDX_Control(pDX, IDC_SMSG_COMBO_WINDOW_TYPE, ComboWindowType);
	DDX_Control(pDX, IDC_SMSG_STATIC_WINDOW_HANDLE, StaticWindowHandle);
	DDX_Control(pDX, IDC_SMSG_STATIC_WINDOW_CLASS_NAME, StaticWindowClassName);
	DDX_Control(pDX, IDC_SMSG_STATIC_WINDOW_TYPE, StaticWindowType);
	DDX_Control(pDX, IDC_SMSG_STATIC_MESSAGE, StaticMessage);
}


BEGIN_MESSAGE_MAP(DlalogSendMessage, CDialogEx)
	//	ON_EN_CHANGE(IDC_SMSG_EDIT_HWND, &DlalogSendMessage::OnEnChangeSmsgEditHwnd)
		//ON_CBN_SELCHANGE(IDC_SMSG_COMBO_WINDOW_TYPE, &DlalogSendMessage::OnCbnSelchangeSmsgComboWindowType)
	ON_CBN_SELCHANGE(IDC_SMSG_COMBO_MESSAGE, &DlalogSendMessage::OnCbnSelchangeSmsgComboMessage)
	ON_BN_CLICKED(IDC_SMSG_BUTTON_SEND, &DlalogSendMessage::OnBnClickedSmsgButtonSend)
	ON_EN_CHANGE(IDC_SMSG_EDIT_HWND, &DlalogSendMessage::OnEnChangeSmsgEditHwnd)
	ON_CBN_SELCHANGE(IDC_SMSG_COMBO_WINDOW_TYPE, &DlalogSendMessage::OnCbnSelchangeSmsgComboWindowType)
END_MESSAGE_MAP()


// DlalogSendMessage 消息处理程序


void DlalogSendMessage::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL DlalogSendMessage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	SetWindowText(AllLanguage->GetLanguageStruct()->TITLE_SEND_MESSAGE);
	CString hWndStr;
#ifdef _WIN64
	hWndStr.Format(_T("%llu"), OperateHWND);
#else
	hWndStr.Format(_T("%u"), OperateHWND);
#endif // _WIN64


	EditHwnd.SetWindowText(hWndStr);

	StaticWindowHandle.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_WINDOW_HANDLE);
	StaticWindowClassName.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_WINDOW_CLASS_NAME);
	StaticWindowType.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_WINDOW_TYPE);
	StaticMessage.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_MESSAGE);
	ButtonSend.SetWindowText(AllLanguage->GetLanguageStruct()->SENDMESSAGE_SEND);

	//Init window type
	ControlType.STATIC = ComboWindowType.AddString(_T("Static"));
	ControlType.COMPUTER = ComboWindowType.AddString(_T("Computer"));
	ControlType.CR = ComboWindowType.AddString(_T("C Sharp"));
	ControlType.DESKTOP = ComboWindowType.AddString(_T("Root"));
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
	CString TempString;
	EditClassName.GetWindowText(TempString);
	ComboWindowType.SetCurSel(GetControlTypeID(OperateHWND, TempString, ControlType));
	OnCbnSelchangeSmsgComboWindowType();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlalogSendMessage::OnEnChangeSmsgEditHwnd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString TempString;
	HWND hWnd = NULL;
	EditHwnd.GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	TempString = _T("");
	::RealGetWindowClass(hWnd, TempString.GetBuffer(50), 50);
	TempString.ReleaseBuffer();
	EditClassName.SetWindowText(TempString);
}




void DlalogSendMessage::OnCbnSelchangeSmsgComboMessage()
{
	// TODO: 在此添加控件通知处理程序代码
	CString MessageName = _T("");
	ComboMessage.GetWindowText(MessageName);
	//clean all 
	ButtonSend.ShowWindow(SW_HIDE);
	if (mDemoEdit != NULL)
	{
		delete[] mDemoEdit;
		mDemoEdit = NULL;
	}
	if (mDemoStatic != NULL)
	{
		delete[] mDemoStatic;
		mDemoStatic = NULL;
	}
	if (mDemoComboBox != NULL)
	{
		delete[] mDemoComboBox;
		mDemoComboBox = NULL;
	}
	if (MessageName == _T("WM_NULL"))
	{
		//需要一个标签来显示提示
		mDemoStatic = new CStatic[2];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Performs no operation. An application sends the WM_NULL message if it wants to post a message that the recipient window will ignore.")), 1342308352, CRect(12, 70, 650, 170), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(_T(""), 1342308352, CRect(12, 180, 650, 200), this);
		mDemoStatic[1].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_CREATE"))
	{
	}
	else if (MessageName == _T("WM_DESTROY"))
	{
	}
	else if (MessageName == _T("WM_MOVE"))
	{
		mDemoStatic = new CStatic[4];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sent after a window has been moved.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("X:")), 1342308354, CRect(12, 90, 150, 110), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(AllLanguage->GetIniFileText(MessageName, _T("Static2"), _T("Y:")), 1342308354, CRect(12, 110, 150, 130), this);
		mDemoStatic[2].SetFont(GetFont());
		mDemoStatic[3].Create(_T(""), 1342308352, CRect(12, 140, 300, 160), this);
		mDemoStatic[3].SetFont(GetFont());
		mDemoEdit = new CEdit[2];
		mDemoEdit[0].CreateEx(516, _T("Edit"), _T("0"), 1342251136, CRect(155, 90, 300, 108), this, 0);
		mDemoEdit[0].SetFont(GetFont());
		mDemoEdit[1].CreateEx(516, _T("Edit"), _T("0"), 1342251136, CRect(155, 110, 300, 128), this, 0);
		mDemoEdit[1].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_SIZE"))
	{
		mDemoStatic = new CStatic[5];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sent to a window after its size has changed.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("Width:")), 1342308354, CRect(12, 90, 150, 110), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(AllLanguage->GetIniFileText(MessageName, _T("Static2"), _T("High:")), 1342308354, CRect(12, 110, 150, 130), this);
		mDemoStatic[2].SetFont(GetFont());
		mDemoStatic[3].Create(AllLanguage->GetIniFileText(MessageName, _T("Static3"), _T("Type of resizing:")), 1342308354, CRect(12, 130, 150, 150), this);
		mDemoStatic[3].SetFont(GetFont());
		mDemoStatic[4].Create(_T(""), 1342308352, CRect(12, 160, 300, 180), this);
		mDemoStatic[4].SetFont(GetFont());
		mDemoEdit = new CEdit[2];
		mDemoEdit[0].CreateEx(516, _T("Edit"), _T("0"), 1342251136, CRect(155, 90, 300, 108), this, 0);
		mDemoEdit[0].SetFont(GetFont());
		mDemoEdit[1].CreateEx(516, _T("Edit"), _T("0"), 1342251136, CRect(155, 110, 300, 128), this, 0);
		mDemoEdit[1].SetFont(GetFont());
		mDemoComboBox = new CComboBox[1];
		mDemoComboBox[0].Create(1342243331, CRect(155, 130, 300, 148), this, 0);
		mDemoComboBox[0].SetFont(GetFont());
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_0"), _T("SIZE_RESTORED")));
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_1"), _T("SIZE_MINIMIZED")));
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_2"), _T("SIZE_MAXIMIZED")));
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_3"), _T("SIZE_MAXSHOW")));
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_4"), _T("SIZE_MAXHIDE")));
		mDemoComboBox[0].SetCurSel(0);
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_SETFOCUS"))
	{
		mDemoStatic = new CStatic[4];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sent to a window after it has gained the keyboard focus.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("Window handle:")), 1342308354, CRect(12, 90, 150, 110), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(AllLanguage->GetIniFileText(MessageName, _T("Static2"), _T("A handle to the window that has lost the keyboard focus.")), 1342308352, CRect(327, 90, 650, 110), this);
		mDemoStatic[2].SetFont(GetFont());
		mDemoStatic[3].Create(_T(""), 1342308352, CRect(12, 150, 300, 170), this);
		mDemoStatic[3].SetFont(GetFont());
		//1342242944 516
		mDemoEdit = new CEdit[1];
		mDemoEdit[0].CreateEx(516, _T("Edit"), _T("0"), 1342242944, CRect(155, 90, 322, 108), this, 0);
		mDemoEdit[0].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_KILLFOCUS"))
	{
		mDemoStatic = new CStatic[4];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sent to a window immediately before it loses the keyboard focus.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("Window handle:")), 1342308354, CRect(12, 90, 150, 110), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(AllLanguage->GetIniFileText(MessageName, _T("Static2"), _T("A handle to the window that receives the keyboard focus.")), 1342308352, CRect(327, 90, 650, 110), this);
		mDemoStatic[2].SetFont(GetFont());
		mDemoStatic[3].Create(_T(""), 1342308352, CRect(12, 150, 300, 170), this);
		mDemoStatic[3].SetFont(GetFont());
		//1342242944 516
		mDemoEdit = new CEdit[1];
		mDemoEdit[0].CreateEx(516, _T("Edit"), _T("0"), 1342242944, CRect(155, 90, 322, 108), this, 0);
		mDemoEdit[0].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_ENABLE"))
	{
		mDemoStatic = new CStatic[3];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sent when an application changes the enabled state of a window. It is sent to the window whose enabled state is changing. This message is sent before the EnableWindow function returns, but after the enabled state (WS_DISABLED style bit) of the window has changed.")), 1342308352, CRect(12, 70, 650, 210), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("Enabled:")), 1342308354, CRect(12, 220, 150, 240), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(_T(""), 1342308352, CRect(12, 250, 650, 270), this);
		mDemoStatic[2].SetFont(GetFont());
		mDemoComboBox = new CComboBox[1];
		mDemoComboBox[0].Create(1342243331, CRect(155, 220, 300, 238), this, 0);
		mDemoComboBox[0].SetFont(GetFont());
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_0"), _T("False")));
		mDemoComboBox[0].AddString(AllLanguage->GetIniFileText(MessageName, _T("ComboBox0_1"), _T("True")));
		mDemoComboBox[0].SetCurSel(0);
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_SETREDRAW"))
	{

	}
	else if (MessageName == _T("WM_SETTEXT"))
	{
		mDemoStatic = new CStatic[3];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sets the text of a window.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("Window text:")), 1342308354, CRect(12, 90, 150, 110), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(_T(""), 1342308352, CRect(12, 120, 300, 140), this);
		mDemoStatic[2].SetFont(GetFont());
		//1342242944 516
		mDemoEdit = new CEdit[1];
		mDemoEdit[0].CreateEx(516, _T("Edit"), _T(""), 1342242944, CRect(155, 90, 650, 108), this, 0);
		mDemoEdit[0].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_GETTEXT"))
	{
		mDemoStatic = new CStatic[3];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Gets the text of a window.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(AllLanguage->GetIniFileText(MessageName, _T("Static1"), _T("Window text:")), 1342308354, CRect(12, 90, 150, 110), this);
		mDemoStatic[1].SetFont(GetFont());
		mDemoStatic[2].Create(_T(""), 1342308352, CRect(12, 120, 300, 140), this);
		mDemoStatic[2].SetFont(GetFont());
		mDemoEdit = new CEdit[1];
		mDemoEdit[0].CreateEx(516, _T("Edit"), _T(""), 1342244992, CRect(155, 90, 650, 108), this, 0);
		mDemoEdit[0].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_GETTEXTLENGTH"))
	{
		mDemoStatic = new CStatic[2];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Determines the length, in characters, of the text associated with a window.")), 1342308352, CRect(12, 70, 650, 90), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(_T(""), 1342308352, CRect(12, 120, 300, 140), this);
		mDemoStatic[1].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_PAINT"))
	{
		mDemoStatic = new CStatic[2];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("The WM_PAINT message is sent when the system or another application makes a request to paint a portion of an application's window. The message is sent when the UpdateWindow or RedrawWindow function is called, or by the DispatchMessage function when the application obtains a WM_PAINT message by using the GetMessage or PeekMessage function.")), 1342308352, CRect(12, 70, 650, 200), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(_T(""), 1342308352, CRect(12, 230, 300, 250), this);
		mDemoStatic[1].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_CLOSE"))
	{
		mDemoStatic = new CStatic[2];
		mDemoStatic[0].Create(AllLanguage->GetIniFileText(MessageName, _T("Static0"), _T("Sent as a signal that a window or an application should terminate.")), 1342308352, CRect(12, 70, 650, 200), this);
		mDemoStatic[0].SetFont(GetFont());
		mDemoStatic[1].Create(_T(""), 1342308352, CRect(12, 230, 300, 250), this);
		mDemoStatic[1].SetFont(GetFont());
		ButtonSend.MoveWindow(CRect(573, 429, 75 + 573, 23 + 429));
		ButtonSend.ShowWindow(SW_SHOW);
	}
	else if (MessageName == _T("WM_QUERYENDSESSION"))
	{
	
	}
	else if (MessageName == _T("WM_QUERYOPEN"))
	{

	}
	else if (MessageName == _T("WM_ENDSESSION"))
	{

	}
	else if (MessageName == _T("WM_QUIT"))
	{

	}
	else if (MessageName == _T("WM_ERASEBKGND"))
	{

	}
	else if (MessageName == _T("WM_SYSCOLORCHANGE"))
	{

	}
	else if (MessageName == _T("WM_SHOWWINDOW"))
	{

	}
	else if (MessageName == _T("WM_WININICHANGE"))
	{

	}
	else if (MessageName == _T("WM_SETTINGCHANGE"))
	{

	}
	else if (MessageName == _T("WM_DEVMODECHANGE"))
	{

	}
	else if (MessageName == _T("WM_ACTIVATEAPP"))
	{

	}
	else if (MessageName == _T("WM_FONTCHANGE"))
	{

	}
	else if (MessageName == _T("WM_TIMECHANGE"))
	{

	}
	else if (MessageName == _T("WM_CANCELMODE"))
	{

	}
	else if (MessageName == _T("WM_SETCURSOR"))
	{

	}
	else if (MessageName == _T("WM_MOUSEACTIVATE"))
	{

	}
	else if (MessageName == _T("WM_CHILDACTIVATE"))
	{

	}
	else if (MessageName == _T("WM_QUEUESYNC"))
	{

	}
	else if (MessageName == _T("WM_GETMINMAXINFO"))
	{

	}
	else if (MessageName == _T("WM_PAINTICON"))
	{

	}
	else if (MessageName == _T("WM_ICONERASEBKGND"))
	{

	}
	else if (MessageName == _T("WM_NEXTDLGCTL"))
	{

	}
	else if (MessageName == _T("WM_SPOOLERSTATUS"))
	{

	}
	else if (MessageName == _T("WM_DRAWITEM"))
	{

	}
	else if (MessageName == _T("WM_MEASUREITEM"))
	{

	}
	else if (MessageName == _T("WM_DELETEITEM"))
	{

	}
	else if (MessageName == _T("WM_VKEYTOITEM"))
	{

	}
	else if (MessageName == _T("WM_CHARTOITEM"))
	{

	}
	else if (MessageName == _T("WM_SETFONT"))
	{

	}
	else if (MessageName == _T("WM_GETFONT"))
	{

	}
	else if (MessageName == _T("WM_SETHOTKEY"))
	{

	}
	else if (MessageName == _T("WM_GETHOTKEY"))
	{

	}
}

void DlalogSendMessage::OnBnClickedSmsgButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	CString MessageName = _T("");
	ComboMessage.GetWindowText(MessageName);
	CString TempString;
	CString ValueString;
	HWND hWnd = NULL;
	EditHwnd.GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	if (MessageName == _T("WM_NULL"))
	{
		LRESULT r;
		mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_NULL, NULL, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64
			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[1].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[1]);
			}
		}
	}
	else if (MessageName == _T("WM_CREATE"))
	{
	}
	else if (MessageName == _T("WM_DESTROY"))
	{
	}
	else if (MessageName == _T("WM_MOVE"))
	{
		CString lTempStr = _T("");
		POINTS pos = { 0 };
		mDemoEdit[0].GetWindowText(lTempStr);
		pos.x = _tstoi(lTempStr);
		mDemoEdit[1].GetWindowText(lTempStr);
		pos.y = _tstoi(lTempStr);

		LRESULT r;
		mDemoStatic[3].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_MOVE, NULL, *((LPARAM*)&pos), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64
			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[3].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[3].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[3]);
			}
		}
	}
	else if (MessageName == _T("WM_SIZE"))
	{
		CString lTempStr = _T("");
		POINTS lsize = { 0 };
		mDemoEdit[0].GetWindowText(lTempStr);
		lsize.x = _tstoi(lTempStr);
		mDemoEdit[1].GetWindowText(lTempStr);
		lsize.y = _tstoi(lTempStr);

		LRESULT r;
		mDemoStatic[4].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_SIZE, mDemoComboBox[0].GetCurSel(), *((LPARAM*)&lsize), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64


			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[4].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[4].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[4]);
			}
		}
	}
	else if (MessageName == _T("WM_SETFOCUS"))
	{
		CString lTempStr = _T("");
		mDemoEdit[0].GetWindowText(lTempStr);
#ifdef _WIN64
		HWND lhWnd = (HWND)_tstoll(lTempStr);
#else
		HWND lhWnd = (HWND)_tstoi(lTempStr);
#endif // _WIN64
		LRESULT r;
		mDemoStatic[3].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_SETFOCUS, (LPARAM)lhWnd, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64


			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[3].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[3].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[3]);
			}
		}
	}
	else if (MessageName == _T("WM_KILLFOCUS"))
	{
		CString lTempStr = _T("");
		mDemoEdit[0].GetWindowText(lTempStr);
#ifdef _WIN64
		HWND lhWnd = (HWND)_tstoll(lTempStr);
#else
		HWND lhWnd = (HWND)_tstoi(lTempStr);
#endif // _WIN64
		LRESULT r;
		mDemoStatic[3].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_KILLFOCUS, (LPARAM)lhWnd, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64


			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[3].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[3].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[3]);
			}
		}
	}
	else if (MessageName == _T("WM_ENABLE"))
	{
		LRESULT r;
		mDemoStatic[2].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_ENABLE, mDemoComboBox[0].GetCurSel(), NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64


			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[2].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[2].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[2]);
			}
		}
	}
	else if (MessageName == _T("WM_SETREDRAW"))
	{

	}
	else if (MessageName == _T("WM_SETTEXT"))
	{
		CString lTempStr = _T("");
		mDemoEdit[0].GetWindowText(lTempStr);

		LRESULT r;
		mDemoStatic[2].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_SETTEXT, NULL, (LPARAM)(LPCTSTR)lTempStr, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64


			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[2].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[2].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[2]);
			}
		}
		}
	else if (MessageName == _T("WM_GETTEXT"))
	{
		CString lTempStr = _T("");
		//mDemoEdit[0].GetWindowText(lTempStr);

		LRESULT r;
		mDemoStatic[2].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStr.GetBuffer(MAX_PATH), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64
			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[2].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[2].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[2]);
			}
	}
		lTempStr.ReleaseBuffer();
		mDemoEdit[0].SetWindowText(lTempStr);
	}
	else if (MessageName == _T("WM_GETTEXTLENGTH"))
	{
		LRESULT r;
		mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetIniFileText(MessageName, _T("TEXTLENGTH"), _T("Text length: [VALUE]"));
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64
			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[1].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[1]);
			}
	}
}
	else if (MessageName == _T("WM_PAINT"))
	{
		LRESULT r;
		mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_PAINT, NULL, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64
			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[1].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[1]);
			}
		}
	}
	else if (MessageName == _T("WM_CLOSE"))
	{
			LRESULT r;
		mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->WAITING);
		//Invalidate();
		if (::SendMessageTimeout(hWnd, WM_CLOSE, NULL, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, (PDWORD_PTR)&r))
		{
			TempString = AllLanguage->GetLanguageStruct()->RETURNVALUE;
#ifdef _WIN64
			ValueString.Format(_T("%lld"), r);
#else
			ValueString.Format(_T("%d"), r);
#endif // _WIN64
			TempString.Replace(_T("[VALUE]"), ValueString);
			mDemoStatic[1].SetWindowText(TempString);
		}
		else
		{
			DWORD dwLastError = GetLastError();
			if (dwLastError == NULL)
			{
				mDemoStatic[1].SetWindowText(AllLanguage->GetLanguageStruct()->ERROR0);
			}
			else
			{
				DrowErrorCode(dwLastError, mDemoStatic[1]);
			}
		}
	}
	else if (MessageName == _T("WM_QUERYENDSESSION"))
	{

	}
	else if (MessageName == _T("WM_QUERYOPEN"))
	{

	}
	else if (MessageName == _T("WM_ENDSESSION"))
	{

	}
	else if (MessageName == _T("WM_QUIT"))
	{

	}
	else if (MessageName == _T("WM_ERASEBKGND"))
	{

	}
	else if (MessageName == _T("WM_SYSCOLORCHANGE"))
	{

	}
	else if (MessageName == _T("WM_SHOWWINDOW"))
	{

	}
	else if (MessageName == _T("WM_WININICHANGE"))
	{

	}
	else if (MessageName == _T("WM_SETTINGCHANGE"))
	{

	}
	else if (MessageName == _T("WM_DEVMODECHANGE"))
	{

	}
	else if (MessageName == _T("WM_ACTIVATEAPP"))
	{

	}
	else if (MessageName == _T("WM_FONTCHANGE"))
	{

	}
	else if (MessageName == _T("WM_TIMECHANGE"))
	{

	}
	else if (MessageName == _T("WM_CANCELMODE"))
	{

	}
	else if (MessageName == _T("WM_SETCURSOR"))
	{

	}
	else if (MessageName == _T("WM_MOUSEACTIVATE"))
	{

	}
	else if (MessageName == _T("WM_CHILDACTIVATE"))
	{

	}
	else if (MessageName == _T("WM_QUEUESYNC"))
	{

	}
	else if (MessageName == _T("WM_GETMINMAXINFO"))
	{

	}
	else if (MessageName == _T("WM_PAINTICON"))
	{

	}
	else if (MessageName == _T("WM_ICONERASEBKGND"))
	{

	}
	else if (MessageName == _T("WM_NEXTDLGCTL"))
	{

	}
	else if (MessageName == _T("WM_SPOOLERSTATUS"))
	{

	}
	else if (MessageName == _T("WM_DRAWITEM"))
	{

	}
	else if (MessageName == _T("WM_MEASUREITEM"))
	{

	}
	else if (MessageName == _T("WM_DELETEITEM"))
	{

	}
	else if (MessageName == _T("WM_VKEYTOITEM"))
	{

	}
	else if (MessageName == _T("WM_CHARTOITEM"))
	{

	}
	else if (MessageName == _T("WM_SETFONT"))
	{

	}
	else if (MessageName == _T("WM_GETFONT"))
	{

	}
	else if (MessageName == _T("WM_SETHOTKEY"))
	{

	}
	else if (MessageName == _T("WM_GETHOTKEY"))
	{

	}
}

void DlalogSendMessage::OnCbnSelchangeSmsgComboWindowType()
{
	// TODO: 在此添加控件通知处理程序代码
	int WindowType = ComboWindowType.GetCurSel();
	ComboMessage.ResetContent();
	if (WindowType == ControlType.WINDOW)//所有窗口消息
	{
		ComboMessage.AddString(_T("WM_NULL"));
		ComboMessage.AddString(_T("WM_CREATE"));
		ComboMessage.AddString(_T("WM_DESTROY"));
		ComboMessage.AddString(_T("WM_MOVE"));
		ComboMessage.AddString(_T("WM_SIZE"));
		ComboMessage.AddString(_T("WM_SETFOCUS"));
		ComboMessage.AddString(_T("WM_KILLFOCUS"));
		ComboMessage.AddString(_T("WM_ENABLE"));
		ComboMessage.AddString(_T("WM_SETREDRAW"));
		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
		ComboMessage.AddString(_T("WM_PAINT"));
		ComboMessage.AddString(_T("WM_CLOSE"));
		ComboMessage.AddString(_T("WM_QUERYENDSESSION"));
		ComboMessage.AddString(_T("WM_QUERYOPEN"));
		ComboMessage.AddString(_T("WM_ENDSESSION"));
		ComboMessage.AddString(_T("WM_QUIT"));
		ComboMessage.AddString(_T("WM_ERASEBKGND"));
		ComboMessage.AddString(_T("WM_SYSCOLORCHANGE"));
		ComboMessage.AddString(_T("WM_SHOWWINDOW"));
		ComboMessage.AddString(_T("WM_WININICHANGE"));
		ComboMessage.AddString(_T("WM_SETTINGCHANGE"));
		ComboMessage.AddString(_T("WM_DEVMODECHANGE"));
		ComboMessage.AddString(_T("WM_ACTIVATEAPP"));
		ComboMessage.AddString(_T("WM_FONTCHANGE"));
		ComboMessage.AddString(_T("WM_TIMECHANGE"));
		ComboMessage.AddString(_T("WM_CANCELMODE"));
		ComboMessage.AddString(_T("WM_SETCURSOR"));
		ComboMessage.AddString(_T("WM_MOUSEACTIVATE"));
		ComboMessage.AddString(_T("WM_CHILDACTIVATE"));
		ComboMessage.AddString(_T("WM_QUEUESYNC"));
		ComboMessage.AddString(_T("WM_GETMINMAXINFO"));
		ComboMessage.AddString(_T("WM_PAINTICON"));
		ComboMessage.AddString(_T("WM_ICONERASEBKGND"));
		ComboMessage.AddString(_T("WM_NEXTDLGCTL"));
		ComboMessage.AddString(_T("WM_SPOOLERSTATUS"));
		ComboMessage.AddString(_T("WM_DRAWITEM"));
		ComboMessage.AddString(_T("WM_MEASUREITEM"));
		ComboMessage.AddString(_T("WM_DELETEITEM"));
		ComboMessage.AddString(_T("WM_VKEYTOITEM"));
		ComboMessage.AddString(_T("WM_CHARTOITEM"));
		ComboMessage.AddString(_T("WM_SETFONT"));
		ComboMessage.AddString(_T("WM_GETFONT"));
		ComboMessage.AddString(_T("WM_SETHOTKEY"));
		ComboMessage.AddString(_T("WM_GETHOTKEY"));
		ComboMessage.AddString(_T("WM_QUERYDRAGICON"));
		ComboMessage.AddString(_T("WM_COMPAREITEM"));
		ComboMessage.AddString(_T("WM_GETOBJECT"));
		ComboMessage.AddString(_T("WM_COMPACTING"));
		ComboMessage.AddString(_T("WM_COMMNOTIFY"));
		ComboMessage.AddString(_T("WM_WINDOWPOSCHANGING"));
		ComboMessage.AddString(_T("WM_WINDOWPOSCHANGED"));
		ComboMessage.AddString(_T("WM_POWER"));
		ComboMessage.AddString(_T("WM_COPYDATA"));
		ComboMessage.AddString(_T("WM_CANCELJOURNAL"));
		ComboMessage.AddString(_T("WM_NOTIFY"));
		ComboMessage.AddString(_T("WM_INPUTLANGCHANGEREQUEST"));
		ComboMessage.AddString(_T("WM_INPUTLANGCHANGE"));
		ComboMessage.AddString(_T("WM_TCARD"));
		ComboMessage.AddString(_T("WM_HELP"));
		ComboMessage.AddString(_T("WM_USERCHANGED"));
		ComboMessage.AddString(_T("WM_NOTIFYFORMAT"));
		ComboMessage.AddString(_T("WM_CONTEXTMENU"));
		ComboMessage.AddString(_T("WM_STYLECHANGING"));
		ComboMessage.AddString(_T("WM_STYLECHANGED"));
		ComboMessage.AddString(_T("WM_DISPLAYCHANGE"));
		ComboMessage.AddString(_T("WM_GETICON"));
		ComboMessage.AddString(_T("WM_SETICON"));
		ComboMessage.AddString(_T("WM_NCCREATE"));
		ComboMessage.AddString(_T("WM_NCDESTROY"));
		ComboMessage.AddString(_T("WM_NCCALCSIZE"));
		ComboMessage.AddString(_T("WM_NCHITTEST"));
		ComboMessage.AddString(_T("WM_NCPAINT"));
		ComboMessage.AddString(_T("WM_NCACTIVATE"));
		ComboMessage.AddString(_T("WM_GETDLGCODE"));
		ComboMessage.AddString(_T("WM_SYNCPAINT"));
		ComboMessage.AddString(_T("WM_NCMOUSEMOVE"));
		ComboMessage.AddString(_T("WM_NCLBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_NCLBUTTONUP"));
		ComboMessage.AddString(_T("WM_NCLBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_NCRBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_NCRBUTTONUP"));
		ComboMessage.AddString(_T("WM_NCRBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_NCMBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_NCMBUTTONUP"));
		ComboMessage.AddString(_T("WM_NCMBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_NCXBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_INPUT_DEVICE_CHANGE"));
		ComboMessage.AddString(_T("WM_INPUT"));
		ComboMessage.AddString(_T("WM_KEYFIRST"));
		ComboMessage.AddString(_T("WM_KEYDOWN"));
		ComboMessage.AddString(_T("WM_KEYUP"));
		ComboMessage.AddString(_T("WM_CHAR"));
		ComboMessage.AddString(_T("WM_DEADCHAR"));
		ComboMessage.AddString(_T("WM_SYSKEYDOWN"));
		ComboMessage.AddString(_T("WM_SYSKEYUP"));
		ComboMessage.AddString(_T("WM_SYSCHAR"));
		ComboMessage.AddString(_T("WM_SYSDEADCHAR"));
		ComboMessage.AddString(_T("WM_UNICHAR"));
		ComboMessage.AddString(_T("WM_KEYLAST"));
		ComboMessage.AddString(_T("WM_IME_STARTCOMPOSITION"));
		ComboMessage.AddString(_T("WM_IME_ENDCOMPOSITION"));
		ComboMessage.AddString(_T("WM_IME_COMPOSITION"));
		ComboMessage.AddString(_T("WM_IME_KEYLAST"));
		ComboMessage.AddString(_T("WM_INITDIALOG"));
		ComboMessage.AddString(_T("WM_COMMAND"));
		ComboMessage.AddString(_T("WM_SYSCOMMAND"));
		ComboMessage.AddString(_T("WM_TIMER"));
		ComboMessage.AddString(_T("WM_HSCROLL"));
		ComboMessage.AddString(_T("WM_VSCROLL"));
		ComboMessage.AddString(_T("WM_INITMENU"));
		ComboMessage.AddString(_T("WM_INITMENUPOPUP"));
		ComboMessage.AddString(_T("WM_GESTURE"));
		ComboMessage.AddString(_T("WM_GESTURENOTIFY"));
		ComboMessage.AddString(_T("WM_MENUSELECT"));
		ComboMessage.AddString(_T("WM_MENUCHAR"));
		ComboMessage.AddString(_T("WM_ENTERIDLE"));
		ComboMessage.AddString(_T("WM_MENURBUTTONUP"));
		ComboMessage.AddString(_T("WM_MENUDRAG"));
		ComboMessage.AddString(_T("WM_MENUGETOBJECT"));
		ComboMessage.AddString(_T("WM_UNINITMENUPOPUP"));
		ComboMessage.AddString(_T("WM_MENUCOMMAND"));
		ComboMessage.AddString(_T("WM_CHANGEUISTATE"));
		ComboMessage.AddString(_T("WM_UPDATEUISTATE"));
		ComboMessage.AddString(_T("WM_QUERYUISTATE"));
		ComboMessage.AddString(_T("WM_CTLCOLORMSGBOX"));
		ComboMessage.AddString(_T("WM_CTLCOLOREDIT"));
		ComboMessage.AddString(_T("WM_CTLCOLORLISTBOX"));
		ComboMessage.AddString(_T("WM_CTLCOLORBTN"));
		ComboMessage.AddString(_T("WM_CTLCOLORDLG"));
		ComboMessage.AddString(_T("WM_CTLCOLORSCROLLBAR"));
		ComboMessage.AddString(_T("WM_CTLCOLORSTATIC"));
		ComboMessage.AddString(_T("MN_GETHMENU"));
		ComboMessage.AddString(_T("WM_MOUSEFIRST"));
		ComboMessage.AddString(_T("WM_MOUSEMOVE"));
		ComboMessage.AddString(_T("WM_LBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_LBUTTONUP"));
		ComboMessage.AddString(_T("WM_LBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_RBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_RBUTTONUP"));
		ComboMessage.AddString(_T("WM_RBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_MBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_MBUTTONUP"));
		ComboMessage.AddString(_T("WM_MBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_MOUSEWHEEL"));
		ComboMessage.AddString(_T("WM_XBUTTONDOWN"));
		ComboMessage.AddString(_T("WM_XBUTTONUP"));
		ComboMessage.AddString(_T("WM_XBUTTONDBLCLK"));
		ComboMessage.AddString(_T("WM_MOUSEHWHEEL"));
		ComboMessage.AddString(_T("WM_MOUSELAST"));
		ComboMessage.AddString(_T("WM_PARENTNOTIFY"));
		ComboMessage.AddString(_T("WM_ENTERMENULOOP"));
		ComboMessage.AddString(_T("WM_EXITMENULOOP"));
		ComboMessage.AddString(_T("WM_NEXTMENU"));
		ComboMessage.AddString(_T("WM_SIZING"));
		ComboMessage.AddString(_T("WM_CAPTURECHANGED"));
		ComboMessage.AddString(_T("WM_MOVING"));
		ComboMessage.AddString(_T("WM_POWERBROADCAST"));
		ComboMessage.AddString(_T("WM_DEVICECHANGE"));
		ComboMessage.AddString(_T("WM_MDICREATE"));
		ComboMessage.AddString(_T("WM_MDIDESTROY"));
		ComboMessage.AddString(_T("WM_MDIACTIVATE"));
		ComboMessage.AddString(_T("WM_MDIRESTORE"));
		ComboMessage.AddString(_T("WM_MDINEXT"));
		ComboMessage.AddString(_T("WM_MDIMAXIMIZE"));
		ComboMessage.AddString(_T("WM_MDITILE"));
		ComboMessage.AddString(_T("WM_MDICASCADE"));
		ComboMessage.AddString(_T("WM_MDIICONARRANGE"));
		ComboMessage.AddString(_T("WM_MDIGETACTIVE"));
		ComboMessage.AddString(_T("WM_MDISETMENU"));
		ComboMessage.AddString(_T("WM_ENTERSIZEMOVE"));
		ComboMessage.AddString(_T("WM_EXITSIZEMOVE"));
		ComboMessage.AddString(_T("WM_DROPFILES"));
		ComboMessage.AddString(_T("WM_MDIREFRESHMENU"));
		ComboMessage.AddString(_T("WM_POINTERDEVICECHANGE"));
		ComboMessage.AddString(_T("WM_POINTERDEVICEINRANGE"));
		ComboMessage.AddString(_T("WM_POINTERDEVICEOUTOFRANGE"));
		ComboMessage.AddString(_T("WM_TOUCH"));
		ComboMessage.AddString(_T("WM_NCPOINTERUPDATE"));
		ComboMessage.AddString(_T("WM_NCPOINTERDOWN"));
		ComboMessage.AddString(_T("WM_NCPOINTERUP"));
		ComboMessage.AddString(_T("WM_POINTERUPDATE"));
		ComboMessage.AddString(_T("WM_POINTERDOWN"));
		ComboMessage.AddString(_T("WM_POINTERUP"));
		ComboMessage.AddString(_T("WM_POINTERENTER"));
		ComboMessage.AddString(_T("WM_POINTERLEAVE"));
		ComboMessage.AddString(_T("WM_POINTERACTIVATE"));
		ComboMessage.AddString(_T("WM_POINTERCAPTURECHANGED"));
		ComboMessage.AddString(_T("WM_TOUCHHITTESTING"));
		ComboMessage.AddString(_T("WM_POINTERWHEEL"));
		ComboMessage.AddString(_T("WM_POINTERHWHEEL"));
		//ComboMessage.AddString(_T("DM_POINTERHITTEST"));
		ComboMessage.AddString(_T("WM_POINTERROUTEDTO"));
		ComboMessage.AddString(_T("WM_POINTERROUTEDAWAY"));
		ComboMessage.AddString(_T("WM_POINTERROUTEDRELEASED"));
		ComboMessage.AddString(_T("WM_IME_SETCONTEXT"));
		ComboMessage.AddString(_T("WM_IME_NOTIFY"));
		ComboMessage.AddString(_T("WM_IME_CONTROL"));
		ComboMessage.AddString(_T("WM_IME_COMPOSITIONFULL"));
		ComboMessage.AddString(_T("WM_IME_SELECT"));
		ComboMessage.AddString(_T("WM_IME_CHAR"));
		ComboMessage.AddString(_T("WM_IME_REQUEST"));
		ComboMessage.AddString(_T("WM_IME_KEYDOWN"));
		ComboMessage.AddString(_T("WM_IME_KEYUP"));
		ComboMessage.AddString(_T("WM_MOUSEHOVER"));
		ComboMessage.AddString(_T("WM_MOUSELEAVE"));
		ComboMessage.AddString(_T("WM_NCMOUSEHOVER"));
		ComboMessage.AddString(_T("WM_NCMOUSELEAVE"));
		ComboMessage.AddString(_T("WM_WTSSESSION_CHANGE"));
		ComboMessage.AddString(_T("WM_TABLET_FIRST"));
		ComboMessage.AddString(_T("WM_TABLET_LAST"));
		ComboMessage.AddString(_T("WM_DPICHANGED"));
		ComboMessage.AddString(_T("WM_DPICHANGED_BEFOREPARENT"));
		ComboMessage.AddString(_T("WM_DPICHANGED_AFTERPARENT"));
		ComboMessage.AddString(_T("WM_GETDPISCALEDSIZE"));
		ComboMessage.AddString(_T("WM_CUT"));
		ComboMessage.AddString(_T("WM_COPY"));
		ComboMessage.AddString(_T("WM_PASTE"));
		ComboMessage.AddString(_T("WM_CLEAR"));
		ComboMessage.AddString(_T("WM_UNDO"));
		ComboMessage.AddString(_T("WM_RENDERFORMAT"));
		ComboMessage.AddString(_T("WM_RENDERALLFORMATS"));
		ComboMessage.AddString(_T("WM_DESTROYCLIPBOARD"));
		ComboMessage.AddString(_T("WM_DRAWCLIPBOARD"));
		ComboMessage.AddString(_T("WM_PAINTCLIPBOARD"));
		ComboMessage.AddString(_T("WM_VSCROLLCLIPBOARD"));
		ComboMessage.AddString(_T("WM_SIZECLIPBOARD"));
		ComboMessage.AddString(_T("WM_ASKCBFORMATNAME"));
		ComboMessage.AddString(_T("WM_CHANGECBCHAIN"));
		ComboMessage.AddString(_T("WM_HSCROLLCLIPBOARD"));
		ComboMessage.AddString(_T("WM_QUERYNEWPALETTE"));
		ComboMessage.AddString(_T("WM_PALETTEISCHANGING"));
		ComboMessage.AddString(_T("WM_PALETTECHANGED"));
		ComboMessage.AddString(_T("WM_HOTKEY"));
		ComboMessage.AddString(_T("WM_PRINT"));
		ComboMessage.AddString(_T("WM_PRINTCLIENT"));
		ComboMessage.AddString(_T("WM_APPCOMMAND"));
		ComboMessage.AddString(_T("WM_THEMECHANGED"));
		ComboMessage.AddString(_T("WM_CLIPBOARDUPDATE"));
		ComboMessage.AddString(_T("WM_DWMCOMPOSITIONCHANGED"));
		ComboMessage.AddString(_T("WM_DWMNCRENDERINGCHANGED"));
		ComboMessage.AddString(_T("WM_DWMCOLORIZATIONCOLORCHANGED"));
		ComboMessage.AddString(_T("WM_DWMWINDOWMAXIMIZEDCHANGE"));
		ComboMessage.AddString(_T("WM_DWMSENDICONICTHUMBNAIL"));
		ComboMessage.AddString(_T("WM_DWMSENDICONICLIVEPREVIEWBITMAP"));
		ComboMessage.AddString(_T("WM_GETTITLEBARINFOEX"));
		ComboMessage.AddString(_T("WM_HANDHELDFIRST"));
		ComboMessage.AddString(_T("WM_HANDHELDLAST"));
		ComboMessage.AddString(_T("WM_AFXFIRST"));
		ComboMessage.AddString(_T("WM_AFXLAST"));
		ComboMessage.AddString(_T("WM_PENWINFIRST"));
		ComboMessage.AddString(_T("WM_PENWINLAST"));
		ComboMessage.AddString(_T("WM_APP"));
		ComboMessage.AddString(_T("WM_USER"));
	}
	else if (WindowType == ControlType.BUTTON || WindowType == ControlType.GROUPBOX || WindowType == ControlType.CHECKBOX || WindowType == ControlType.RADIOBUTTON)
	{
		ComboMessage.AddString(_T("BCM_FIRST"));
		ComboMessage.AddString(_T("BCM_GETIDEALSIZE"));
		ComboMessage.AddString(_T("BCM_SETIMAGELIST"));
		ComboMessage.AddString(_T("BCM_GETIMAGELIST"));
		ComboMessage.AddString(_T("BCM_SETTEXTMARGIN"));
		ComboMessage.AddString(_T("BCM_GETTEXTMARGIN"));
		ComboMessage.AddString(_T("BCM_SETDROPDOWNSTATE"));
		ComboMessage.AddString(_T("BCM_SETSPLITINFO"));
		ComboMessage.AddString(_T("BCM_GETSPLITINFO"));
		ComboMessage.AddString(_T("BCM_SETNOTE"));
		ComboMessage.AddString(_T("BCM_GETNOTE"));
		ComboMessage.AddString(_T("BCM_GETNOTELENGTH"));
		ComboMessage.AddString(_T("BCM_SETSHIELD"));
		ComboMessage.AddString(_T("BM_GETCHECK"));
		ComboMessage.AddString(_T("BM_SETCHECK"));
		ComboMessage.AddString(_T("BM_GETSTATE"));
		ComboMessage.AddString(_T("BM_SETSTATE"));
		ComboMessage.AddString(_T("BM_SETSTYLE"));
		ComboMessage.AddString(_T("BM_CLICK"));
		ComboMessage.AddString(_T("BM_GETIMAGE"));
		ComboMessage.AddString(_T("BM_SETIMAGE"));
		ComboMessage.AddString(_T("BM_SETDONTCLICK"));
		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
	}
	else if (WindowType == ControlType.COMBOBOX)
	{
		ComboMessage.AddString(_T("CB_GETEDITSEL"));
		ComboMessage.AddString(_T("CB_LIMITTEXT"));
		ComboMessage.AddString(_T("CB_SETEDITSEL"));
		ComboMessage.AddString(_T("CB_ADDSTRING"));
		ComboMessage.AddString(_T("CB_DELETESTRING"));
		ComboMessage.AddString(_T("CB_DIR"));
		ComboMessage.AddString(_T("CB_GETCOUNT"));
		ComboMessage.AddString(_T("CB_GETCURSEL"));
		ComboMessage.AddString(_T("CB_GETLBTEXT"));
		ComboMessage.AddString(_T("CB_GETLBTEXTLEN"));
		ComboMessage.AddString(_T("CB_INSERTSTRING"));
		ComboMessage.AddString(_T("CB_RESETCONTENT"));
		ComboMessage.AddString(_T("CB_FINDSTRING"));
		ComboMessage.AddString(_T("CB_SELECTSTRING"));
		ComboMessage.AddString(_T("CB_SETCURSEL"));
		ComboMessage.AddString(_T("CB_SHOWDROPDOWN"));
		ComboMessage.AddString(_T("CB_GETITEMDATA"));
		ComboMessage.AddString(_T("CB_SETITEMDATA"));
		ComboMessage.AddString(_T("CB_GETDROPPEDCONTROLRECT"));
		ComboMessage.AddString(_T("CB_SETITEMHEIGHT"));
		ComboMessage.AddString(_T("CB_GETITEMHEIGHT"));
		ComboMessage.AddString(_T("CB_SETEXTENDEDUI"));
		ComboMessage.AddString(_T("CB_GETEXTENDEDUI"));
		ComboMessage.AddString(_T("CB_GETDROPPEDSTATE"));
		ComboMessage.AddString(_T("CB_FINDSTRINGEXACT"));
		ComboMessage.AddString(_T("CB_SETLOCALE"));
		ComboMessage.AddString(_T("CB_GETLOCALE"));
		ComboMessage.AddString(_T("CB_GETTOPINDEX"));
		ComboMessage.AddString(_T("CB_SETTOPINDEX"));
		ComboMessage.AddString(_T("CB_GETHORIZONTALEXTENT"));
		ComboMessage.AddString(_T("CB_SETHORIZONTALEXTENT"));
		ComboMessage.AddString(_T("CB_GETDROPPEDWIDTH"));
		ComboMessage.AddString(_T("CB_SETDROPPEDWIDTH"));
		ComboMessage.AddString(_T("CB_INITSTORAGE"));
		ComboMessage.AddString(_T("CB_MULTIPLEADDSTRING"));
		ComboMessage.AddString(_T("CB_GETCOMBOBOXINFO"));
		ComboMessage.AddString(_T("CB_MSGMAX"));
		ComboMessage.AddString(_T("CBEM_INSERTITEMA"));
		ComboMessage.AddString(_T("CBEM_SETIMAGELIST"));
		ComboMessage.AddString(_T("CBEM_GETIMAGELIST"));
		ComboMessage.AddString(_T("CBEM_GETITEMA"));
		ComboMessage.AddString(_T("CBEM_SETITEMA"));
		ComboMessage.AddString(_T("CBEM_DELETEITEM"));
		ComboMessage.AddString(_T("CBEM_GETCOMBOCONTROL"));
		ComboMessage.AddString(_T("CBEM_GETEDITCONTROL"));
		ComboMessage.AddString(_T("CBEM_SETEXSTYLE"));
		ComboMessage.AddString(_T("CBEM_SETEXTENDEDSTYLE"));
		ComboMessage.AddString(_T("CBEM_GETEXSTYLE"));
		ComboMessage.AddString(_T("CBEM_GETEXTENDEDSTYLE"));
		ComboMessage.AddString(_T("CBEM_SETUNICODEFORMAT"));
		ComboMessage.AddString(_T("CBEM_GETUNICODEFORMAT"));
		ComboMessage.AddString(_T("CBEM_HASEDITCHANGED"));
		ComboMessage.AddString(_T("CBEM_INSERTITEMW"));
		ComboMessage.AddString(_T("CBEM_SETITEMW"));
		ComboMessage.AddString(_T("CBEM_GETITEMW"));
		ComboMessage.AddString(_T("CBEM_INSERTITEM"));
		ComboMessage.AddString(_T("CBEM_SETITEM"));
		ComboMessage.AddString(_T("CBEM_GETITEM"));
		ComboMessage.AddString(_T("CBEM_SETWINDOWTHEME"));


		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
	}
	else if (WindowType == ControlType.LISTBOX)
	{
		ComboMessage.AddString(_T("LB_ADDSTRING"));
		ComboMessage.AddString(_T("LB_INSERTSTRING"));
		ComboMessage.AddString(_T("LB_DELETESTRING"));
		ComboMessage.AddString(_T("LB_SELITEMRANGEEX"));
		ComboMessage.AddString(_T("LB_RESETCONTENT"));
		ComboMessage.AddString(_T("LB_SETSEL"));
		ComboMessage.AddString(_T("LB_SETCURSEL"));
		ComboMessage.AddString(_T("LB_GETSEL"));
		ComboMessage.AddString(_T("LB_GETCURSEL"));
		ComboMessage.AddString(_T("LB_GETTEXT"));
		ComboMessage.AddString(_T("LB_GETTEXTLEN"));
		ComboMessage.AddString(_T("LB_GETCOUNT"));
		ComboMessage.AddString(_T("LB_SELECTSTRING"));
		ComboMessage.AddString(_T("LB_DIR"));
		ComboMessage.AddString(_T("LB_GETTOPINDEX"));
		ComboMessage.AddString(_T("LB_FINDSTRING"));
		ComboMessage.AddString(_T("LB_GETSELCOUNT"));
		ComboMessage.AddString(_T("LB_GETSELITEMS"));
		ComboMessage.AddString(_T("LB_SETTABSTOPS"));
		ComboMessage.AddString(_T("LB_GETHORIZONTALEXTENT"));
		ComboMessage.AddString(_T("LB_SETHORIZONTALEXTENT"));
		ComboMessage.AddString(_T("LB_SETCOLUMNWIDTH"));
		ComboMessage.AddString(_T("LB_ADDFILE"));
		ComboMessage.AddString(_T("LB_SETTOPINDEX"));
		ComboMessage.AddString(_T("LB_GETITEMRECT"));
		ComboMessage.AddString(_T("LB_GETITEMDATA"));
		ComboMessage.AddString(_T("LB_SETITEMDATA"));
		ComboMessage.AddString(_T("LB_SELITEMRANGE"));
		ComboMessage.AddString(_T("LB_SETANCHORINDEX"));
		ComboMessage.AddString(_T("LB_GETANCHORINDEX"));
		ComboMessage.AddString(_T("LB_SETCARETINDEX"));
		ComboMessage.AddString(_T("LB_GETCARETINDEX"));
		ComboMessage.AddString(_T("LB_SETITEMHEIGHT"));
		ComboMessage.AddString(_T("LB_GETITEMHEIGHT"));
		ComboMessage.AddString(_T("LB_FINDSTRINGEXACT"));
		ComboMessage.AddString(_T("LB_SETLOCALE"));
		ComboMessage.AddString(_T("LB_GETLOCALE"));
		ComboMessage.AddString(_T("LB_SETCOUNT"));
		ComboMessage.AddString(_T("LB_INITSTORAGE"));
		ComboMessage.AddString(_T("LB_ITEMFROMPOINT"));
		ComboMessage.AddString(_T("LB_MULTIPLEADDSTRING"));
		ComboMessage.AddString(_T("LB_GETLISTBOXINFO"));
		ComboMessage.AddString(_T("LB_MSGMAX"));

		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
	}
	else if (WindowType == ControlType.SYSLISTVIEW32)
	{
		ComboMessage.AddString(_T("LVM_FIRST"));
		ComboMessage.AddString(_T("LVM_GETITEMA"));
		ComboMessage.AddString(_T("LVM_GETITEMW"));
		ComboMessage.AddString(_T("LVM_GETITEM"));
		ComboMessage.AddString(_T("LVM_SETITEMA"));
		ComboMessage.AddString(_T("LVM_SETITEMW"));
		ComboMessage.AddString(_T("LVM_SETITEM"));
		ComboMessage.AddString(_T("LVM_INSERTITEMA"));
		ComboMessage.AddString(_T("LVM_INSERTITEMW"));
		ComboMessage.AddString(_T("LVM_INSERTITEM"));
		ComboMessage.AddString(_T("LVM_DELETEITEM"));
		ComboMessage.AddString(_T("LVM_DELETEALLITEMS"));
		ComboMessage.AddString(_T("LVM_GETCALLBACKMASK"));
		ComboMessage.AddString(_T("LVM_SETCALLBACKMASK"));
		ComboMessage.AddString(_T("LVM_GETNEXTITEM"));
		ComboMessage.AddString(_T("LVM_FINDITEMA"));
		ComboMessage.AddString(_T("LVM_FINDITEMW"));
		ComboMessage.AddString(_T("LVM_FINDITEM"));
		ComboMessage.AddString(_T("LVM_GETITEMRECT"));
		ComboMessage.AddString(_T("LVM_SETITEMPOSITION"));
		ComboMessage.AddString(_T("LVM_GETITEMPOSITION"));
		ComboMessage.AddString(_T("LVM_GETSTRINGWIDTHA"));
		ComboMessage.AddString(_T("LVM_GETSTRINGWIDTHW"));
		ComboMessage.AddString(_T("LVM_GETSTRINGWIDTH"));
		ComboMessage.AddString(_T("LVM_HITTEST"));
		ComboMessage.AddString(_T("LVM_ENSUREVISIBLE"));
		ComboMessage.AddString(_T("LVM_SCROLL"));
		ComboMessage.AddString(_T("LVM_REDRAWITEMS"));
		ComboMessage.AddString(_T("LVM_ARRANGE"));
		ComboMessage.AddString(_T("LVM_EDITLABELA"));
		ComboMessage.AddString(_T("LVM_EDITLABELW"));
		ComboMessage.AddString(_T("LVM_EDITLABEL"));
		ComboMessage.AddString(_T("LVM_GETEDITCONTROL"));
		ComboMessage.AddString(_T("LVM_GETCOLUMNA"));
		ComboMessage.AddString(_T("LVM_GETCOLUMNW"));
		ComboMessage.AddString(_T("LVM_GETCOLUMN"));
		ComboMessage.AddString(_T("LVM_SETCOLUMNA"));
		ComboMessage.AddString(_T("LVM_SETCOLUMNW"));
		ComboMessage.AddString(_T("LVM_SETCOLUMN"));
		ComboMessage.AddString(_T("LVM_INSERTCOLUMNA"));
		ComboMessage.AddString(_T("LVM_INSERTCOLUMNW"));
		ComboMessage.AddString(_T("LVM_INSERTCOLUMN"));
		ComboMessage.AddString(_T("LVM_DELETECOLUMN"));
		ComboMessage.AddString(_T("LVM_GETCOLUMNWIDTH"));
		ComboMessage.AddString(_T("LVM_SETCOLUMNWIDTH"));
		ComboMessage.AddString(_T("LVM_GETHEADER"));
		ComboMessage.AddString(_T("LVM_CREATEDRAGIMAGE"));
		ComboMessage.AddString(_T("LVM_GETVIEWRECT"));
		ComboMessage.AddString(_T("LVM_GETTEXTCOLOR"));
		ComboMessage.AddString(_T("LVM_SETTEXTCOLOR"));
		ComboMessage.AddString(_T("LVM_GETTEXTBKCOLOR"));
		ComboMessage.AddString(_T("LVM_SETTEXTBKCOLOR"));
		ComboMessage.AddString(_T("LVM_GETTOPINDEX"));
		ComboMessage.AddString(_T("LVM_GETCOUNTPERPAGE"));
		ComboMessage.AddString(_T("LVM_GETORIGIN"));
		ComboMessage.AddString(_T("LVM_UPDATE"));
		ComboMessage.AddString(_T("LVM_SETITEMSTATE"));
		ComboMessage.AddString(_T("LVM_GETITEMSTATE"));
		ComboMessage.AddString(_T("LVM_GETITEMTEXTA"));
		ComboMessage.AddString(_T("LVM_GETITEMTEXTW"));
		ComboMessage.AddString(_T("LVM_GETITEMTEXT"));
		ComboMessage.AddString(_T("LVM_SETITEMTEXTA"));
		ComboMessage.AddString(_T("LVM_SETITEMTEXTW"));
		ComboMessage.AddString(_T("LVM_SETITEMTEXT"));
		ComboMessage.AddString(_T("LVM_SETITEMCOUNT"));
		ComboMessage.AddString(_T("LVM_SORTITEMS"));
		ComboMessage.AddString(_T("LVM_SETITEMPOSITION32"));
		ComboMessage.AddString(_T("LVM_GETSELECTEDCOUNT"));
		ComboMessage.AddString(_T("LVM_GETITEMSPACING"));
		ComboMessage.AddString(_T("LVM_GETISEARCHSTRINGA"));
		ComboMessage.AddString(_T("LVM_GETISEARCHSTRINGW"));
		ComboMessage.AddString(_T("LVM_GETISEARCHSTRING"));
		ComboMessage.AddString(_T("LVM_SETICONSPACING"));
		ComboMessage.AddString(_T("LVM_SETEXTENDEDLISTVIEWSTYLE"));
		ComboMessage.AddString(_T("LVM_GETEXTENDEDLISTVIEWSTYLE"));
		ComboMessage.AddString(_T("LVM_GETSUBITEMRECT"));
		ComboMessage.AddString(_T("LVM_SUBITEMHITTEST"));
		ComboMessage.AddString(_T("LVM_SETCOLUMNORDERARRAY"));
		ComboMessage.AddString(_T("LVM_GETCOLUMNORDERARRAY"));
		ComboMessage.AddString(_T("LVM_SETHOTITEM"));
		ComboMessage.AddString(_T("LVM_GETHOTITEM"));
		ComboMessage.AddString(_T("LVM_SETHOTCURSOR"));
		ComboMessage.AddString(_T("LVM_GETHOTCURSOR"));
		ComboMessage.AddString(_T("LVM_APPROXIMATEVIEWRECT"));
		ComboMessage.AddString(_T("LVM_SETWORKAREAS"));
		ComboMessage.AddString(_T("LVM_GETWORKAREAS"));
		ComboMessage.AddString(_T("LVM_GETNUMBEROFWORKAREAS"));
		ComboMessage.AddString(_T("LVM_GETSELECTIONMARK"));
		ComboMessage.AddString(_T("LVM_SETSELECTIONMARK"));
		ComboMessage.AddString(_T("LVM_SETHOVERTIME"));
		ComboMessage.AddString(_T("LVM_GETHOVERTIME"));
		ComboMessage.AddString(_T("LVM_SETTOOLTIPS"));
		ComboMessage.AddString(_T("LVM_GETTOOLTIPS"));
		ComboMessage.AddString(_T("LVM_SORTITEMSEX"));
		ComboMessage.AddString(_T("LVM_SETBKIMAGEA"));
		ComboMessage.AddString(_T("LVM_SETBKIMAGEW"));
		ComboMessage.AddString(_T("LVM_GETBKIMAGEA"));
		ComboMessage.AddString(_T("LVM_GETBKIMAGEW"));
		ComboMessage.AddString(_T("LVM_SETSELECTEDCOLUMN"));
		ComboMessage.AddString(_T("LVM_SETVIEW"));
		ComboMessage.AddString(_T("LVM_GETVIEW"));
		ComboMessage.AddString(_T("LVM_INSERTGROUP"));
		ComboMessage.AddString(_T("LVM_SETGROUPINFO"));
		ComboMessage.AddString(_T("LVM_GETGROUPINFO"));
		ComboMessage.AddString(_T("LVM_REMOVEGROUP"));
		ComboMessage.AddString(_T("LVM_MOVEGROUP"));
		ComboMessage.AddString(_T("LVM_GETGROUPCOUNT"));
		ComboMessage.AddString(_T("LVM_GETGROUPINFOBYINDEX"));
		ComboMessage.AddString(_T("LVM_MOVEITEMTOGROUP"));
		ComboMessage.AddString(_T("LVM_GETGROUPRECT"));
		ComboMessage.AddString(_T("LVM_SETGROUPMETRICS"));
		ComboMessage.AddString(_T("LVM_GETGROUPMETRICS"));
		ComboMessage.AddString(_T("LVM_ENABLEGROUPVIEW"));
		ComboMessage.AddString(_T("LVM_SORTGROUPS"));
		ComboMessage.AddString(_T("LVM_INSERTGROUPSORTED"));
		ComboMessage.AddString(_T("LVM_REMOVEALLGROUPS"));
		ComboMessage.AddString(_T("LVM_HASGROUP"));
		ComboMessage.AddString(_T("LVM_GETGROUPSTATE"));
		ComboMessage.AddString(_T("LVM_GETFOCUSEDGROUP"));
		ComboMessage.AddString(_T("LVM_SETTILEVIEWINFO"));
		ComboMessage.AddString(_T("LVM_GETTILEVIEWINFO"));
		ComboMessage.AddString(_T("LVM_SETTILEINFO"));
		ComboMessage.AddString(_T("LVM_GETTILEINFO"));
		ComboMessage.AddString(_T("LVM_SETINSERTMARK"));
		ComboMessage.AddString(_T("LVM_GETINSERTMARK"));
		ComboMessage.AddString(_T("LVM_INSERTMARKHITTEST"));
		ComboMessage.AddString(_T("LVM_GETINSERTMARKRECT"));
		ComboMessage.AddString(_T("LVM_SETINSERTMARKCOLOR"));
		ComboMessage.AddString(_T("LVM_GETINSERTMARKCOLOR"));
		ComboMessage.AddString(_T("LVM_SETINFOTIP"));
		ComboMessage.AddString(_T("LVM_GETSELECTEDCOLUMN"));
		ComboMessage.AddString(_T("LVM_ISGROUPVIEWENABLED"));
		ComboMessage.AddString(_T("LVM_GETOUTLINECOLOR"));
		ComboMessage.AddString(_T("LVM_SETOUTLINECOLOR"));
		ComboMessage.AddString(_T("LVM_CANCELEDITLABEL"));
		ComboMessage.AddString(_T("LVM_MAPINDEXTOID"));
		ComboMessage.AddString(_T("LVM_MAPIDTOINDEX"));
		ComboMessage.AddString(_T("LVM_ISITEMVISIBLE"));
		ComboMessage.AddString(_T("LVM_GETEMPTYTEXT"));
		ComboMessage.AddString(_T("LVM_GETFOOTERRECT"));
		ComboMessage.AddString(_T("LVM_GETFOOTERINFO"));
		ComboMessage.AddString(_T("LVM_GETFOOTERITEMRECT"));
		ComboMessage.AddString(_T("LVM_GETFOOTERITEM"));
		ComboMessage.AddString(_T("LVM_GETITEMINDEXRECT"));
		ComboMessage.AddString(_T("LVM_SETITEMINDEXSTATE"));
		ComboMessage.AddString(_T("LVM_GETNEXTITEMINDEX"));
		ComboMessage.AddString(_T("LVM_SETBKIMAGE"));
		ComboMessage.AddString(_T("LVM_GETBKIMAGE"));

		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
	}
	else if (WindowType == ControlType.PROGRESSBAR)
	{
		ComboMessage.AddString(_T("PBM_SETRANGE"));
		ComboMessage.AddString(_T("PBM_SETPOS"));
		ComboMessage.AddString(_T("PBM_DELTAPOS"));
		ComboMessage.AddString(_T("PBM_SETSTEP"));
		ComboMessage.AddString(_T("PBM_STEPIT"));
		ComboMessage.AddString(_T("PBM_SETRANGE32"));
		ComboMessage.AddString(_T("PBM_GETRANGE"));
		ComboMessage.AddString(_T("PBM_GETPOS"));
		ComboMessage.AddString(_T("PBM_SETBARCOLOR"));
		ComboMessage.AddString(_T("PBM_SETBKCOLOR"));
		ComboMessage.AddString(_T("PBM_SETMARQUEE"));
		ComboMessage.AddString(_T("PBM_GETSTEP"));
		ComboMessage.AddString(_T("PBM_GETBKCOLOR"));
		ComboMessage.AddString(_T("PBM_GETBARCOLOR"));
		ComboMessage.AddString(_T("PBM_SETSTATE"));
		ComboMessage.AddString(_T("PBM_GETSTATE"));

		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
	}
	else if (WindowType == ControlType.EDIT)
	{
		ComboMessage.AddString(_T("EM_CHARFROMPOS"));
		ComboMessage.AddString(_T("EM_GETLIMITTEXT"));
		ComboMessage.AddString(_T("EM_POSFROMCHAR"));
		ComboMessage.AddString(_T("EM_SCROLLCARET"));
		ComboMessage.AddString(_T("EM_CANPASTE"));
		ComboMessage.AddString(_T("EM_DISPLAYBAND"));
		ComboMessage.AddString(_T("EM_EXGETSEL"));
		ComboMessage.AddString(_T("EM_EXLIMITTEXT"));
		ComboMessage.AddString(_T("EM_EXLINEFROMCHAR"));
		ComboMessage.AddString(_T("EM_EXSETSEL"));
		ComboMessage.AddString(_T("EM_FINDTEXT"));
		ComboMessage.AddString(_T("EM_FORMATRANGE"));
		ComboMessage.AddString(_T("EM_GETCHARFORMAT"));
		ComboMessage.AddString(_T("EM_GETEVENTMASK"));
		ComboMessage.AddString(_T("EM_GETOLEINTERFACE"));
		ComboMessage.AddString(_T("EM_GETPARAFORMAT"));
		ComboMessage.AddString(_T("EM_GETSELTEXT"));
		ComboMessage.AddString(_T("EM_HIDESELECTION"));
		ComboMessage.AddString(_T("EM_PASTESPECIAL"));
		ComboMessage.AddString(_T("EM_REQUESTRESIZE"));
		ComboMessage.AddString(_T("EM_SELECTIONTYPE"));
		ComboMessage.AddString(_T("EM_SETBKGNDCOLOR"));
		ComboMessage.AddString(_T("EM_SETCHARFORMAT"));
		ComboMessage.AddString(_T("EM_SETEVENTMASK"));
		ComboMessage.AddString(_T("EM_SETOLECALLBACK"));
		ComboMessage.AddString(_T("EM_SETPARAFORMAT"));
		ComboMessage.AddString(_T("EM_SETTARGETDEVICE"));
		ComboMessage.AddString(_T("EM_STREAMIN"));
		ComboMessage.AddString(_T("EM_STREAMOUT"));
		ComboMessage.AddString(_T("EM_GETTEXTRANGE"));
		ComboMessage.AddString(_T("EM_FINDWORDBREAK"));
		ComboMessage.AddString(_T("EM_SETOPTIONS"));
		ComboMessage.AddString(_T("EM_GETOPTIONS"));
		ComboMessage.AddString(_T("EM_FINDTEXTEX"));
		ComboMessage.AddString(_T("EM_GETWORDBREAKPROCEX"));
		ComboMessage.AddString(_T("EM_SETWORDBREAKPROCEX"));
		ComboMessage.AddString(_T("EM_SETUNDOLIMIT"));
		ComboMessage.AddString(_T("EM_REDO"));
		ComboMessage.AddString(_T("EM_CANREDO"));
		ComboMessage.AddString(_T("EM_GETUNDONAME"));
		ComboMessage.AddString(_T("EM_GETREDONAME"));
		ComboMessage.AddString(_T("EM_STOPGROUPTYPING"));
		ComboMessage.AddString(_T("EM_SETTEXTMODE"));
		ComboMessage.AddString(_T("EM_GETTEXTMODE"));
		ComboMessage.AddString(_T("EM_GETAUTOURLDETECT"));
		ComboMessage.AddString(_T("EM_SETPALETTE"));
		ComboMessage.AddString(_T("EM_GETTEXTEX"));
		ComboMessage.AddString(_T("EM_GETTEXTLENGTHEX"));
		ComboMessage.AddString(_T("EM_SHOWSCROLLBAR"));
		ComboMessage.AddString(_T("EM_SETTEXTEX"));
		ComboMessage.AddString(_T("EM_SETPUNCTUATION"));
		ComboMessage.AddString(_T("EM_GETPUNCTUATION"));
		ComboMessage.AddString(_T("EM_SETWORDWRAPMODE"));
		ComboMessage.AddString(_T("EM_GETWORDWRAPMODE"));
		ComboMessage.AddString(_T("EM_SETIMECOLOR"));
		ComboMessage.AddString(_T("EM_GETIMECOLOR"));
		ComboMessage.AddString(_T("EM_SETIMEOPTIONS"));
		ComboMessage.AddString(_T("EM_GETIMEOPTIONS"));
		ComboMessage.AddString(_T("EM_CONVPOSITION"));
		ComboMessage.AddString(_T("EM_SETLANGOPTIONS"));
		ComboMessage.AddString(_T("EM_GETLANGOPTIONS"));
		ComboMessage.AddString(_T("EM_GETIMECOMPMODE"));
		ComboMessage.AddString(_T("EM_FINDTEXTW"));
		ComboMessage.AddString(_T("EM_FINDTEXTEXW"));
		ComboMessage.AddString(_T("EM_RECONVERSION"));
		ComboMessage.AddString(_T("EM_SETIMEMODEBIAS"));
		ComboMessage.AddString(_T("EM_GETIMEMODEBIAS"));
		ComboMessage.AddString(_T("EM_SETBIDIOPTIONS"));
		ComboMessage.AddString(_T("EM_GETBIDIOPTIONS"));
		ComboMessage.AddString(_T("EM_SETTYPOGRAPHYOPTIONS"));
		ComboMessage.AddString(_T("EM_GETTYPOGRAPHYOPTIONS"));
		ComboMessage.AddString(_T("EM_SETEDITSTYLE"));
		ComboMessage.AddString(_T("EM_GETEDITSTYLE"));
		ComboMessage.AddString(_T("EM_OUTLINE"));
		ComboMessage.AddString(_T("EM_GETSCROLLPOS"));
		ComboMessage.AddString(_T("EM_SETSCROLLPOS"));
		ComboMessage.AddString(_T("EM_SETFONTSIZE"));
		ComboMessage.AddString(_T("EM_GETZOOM"));
		ComboMessage.AddString(_T("EM_SETZOOM"));
		ComboMessage.AddString(_T("EM_GETVIEWKIND"));
		ComboMessage.AddString(_T("EM_SETVIEWKIND"));
		ComboMessage.AddString(_T("EM_GETPAGE"));
		ComboMessage.AddString(_T("EM_SETPAGE"));
		ComboMessage.AddString(_T("EM_GETHYPHENATEINFO"));
		ComboMessage.AddString(_T("EM_SETHYPHENATEINFO"));
		ComboMessage.AddString(_T("EM_GETPAGEROTATE"));
		ComboMessage.AddString(_T("EM_SETPAGEROTATE"));
		ComboMessage.AddString(_T("EM_GETCTFMODEBIAS"));
		ComboMessage.AddString(_T("EM_SETCTFMODEBIAS"));
		ComboMessage.AddString(_T("EM_GETCTFOPENSTATUS"));
		ComboMessage.AddString(_T("EM_SETCTFOPENSTATUS"));
		ComboMessage.AddString(_T("EM_GETIMECOMPTEXT"));
		ComboMessage.AddString(_T("EM_ISIME"));
		ComboMessage.AddString(_T("EM_GETIMEPROPERTY"));
		ComboMessage.AddString(_T("EM_GETQUERYRTFOBJ"));
		ComboMessage.AddString(_T("EM_SETQUERYRTFOBJ"));

		ComboMessage.AddString(_T("WM_SETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXT"));
		ComboMessage.AddString(_T("WM_GETTEXTLENGTH"));
	}
}


void DlalogSendMessage::DrowErrorCode(DWORD dwLastError, CStatic& _Static)
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
		_Static.SetWindowText(TempString);
	}
	else
	{
		TempString.Format(_T(" 0x%X(%d)"), dwLastError, dwLastError);
		TempString = AllLanguage->GetLanguageStruct()->ERROR_ + TempString;
		_Static.SetWindowText(TempString);
	}

	if (hModule != NULL)
		FreeLibrary(hModule);
}
