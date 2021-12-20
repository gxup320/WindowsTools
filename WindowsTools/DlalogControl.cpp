// DialogControl.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogControl.h"
#include "afxdialogex.h"
#include "Language.h"


// DialogControl 对话框

IMPLEMENT_DYNAMIC(DlalogControl, CDialogEx)

DlalogControl::DlalogControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CONTROL, pParent)
{

}

DlalogControl::~DlalogControl()
{
}

void DlalogControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CONTROL_EDIT_HWND, EditHwnd);
	DDX_Control(pDX, IDC_TAB_CONTROL, TabControl);
}


BEGIN_MESSAGE_MAP(DlalogControl, CDialogEx)
	ON_EN_CHANGE(IDC_CONTROL_EDIT_HWND, &DlalogControl::OnEnChangeControlEditHwnd)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &DlalogControl::OnTcnSelchangeTabControl)
END_MESSAGE_MAP()


// DialogControl 消息处理程序


void DlalogControl::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL DlalogControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(AllLanguage->GetLanguageStruct()->TITLE_CONTROL);

	GetDlgItem(IDC_CONTROL_STATIC_WINDOW_HANDLE)->SetWindowText(AllLanguage->GetLanguageStruct()->CONTROL_WINDOW_HANDLE);

	CString hWndStr;
#ifdef _WIN64
	hWndStr.Format(_T("%llu"), OperateHWND);
#else
	hWndStr.Format(_T("%u"), OperateHWND);
#endif // _WIN64

	
	EditHwnd.SetWindowText(hWndStr);
	//CDC* pDc = TabControl.GetDC();
	//COLORREF crBkgnd = pDc->GetBkColor();
	//ReleaseDC(pDc);
	
	m_ControlCommon.Create(IDD_DIALOG_WINDOW_CONTROL, &TabControl);
	//m_ControlCommon.SetBackgroundColor(crBkgnd);
	m_ControlCommon.OperateEdit = &EditHwnd;
	m_ControlEdit.Create(IDD_DIALOG_EDIT_CONTROL, &TabControl);
	//m_ControlEdit.SetBackgroundColor(crBkgnd);
	m_ControlEdit.OperateEdit = &EditHwnd;

	//Init window type
	ControlType.WINDOW = TabControl.InsertItem(0,AllLanguage->GetLanguageStruct()->CONTROL_TAB_COMMON);
	ControlType.EDIT = TabControl.InsertItem(1,AllLanguage->GetLanguageStruct()->CONTROL_TAB_EDIT);

	CString TempString;
	::RealGetWindowClass(OperateHWND, TempString.GetBuffer(MAX_PATH), MAX_PATH);
	TempString.ReleaseBuffer();
	TabControl.SetCurSel(GetControlTypeID(OperateHWND, TempString, ControlType));

	OnTcnSelchangeTabControlShowTab();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlalogControl::OnEnChangeControlEditHwnd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void DlalogControl::OnTcnSelchangeTabControlShowTab()
{
	m_ControlCommon.ShowWindow(SW_HIDE);
	m_ControlEdit.ShowWindow(SW_HIDE);
	switch (TabControl.GetCurSel())
	{
	case 0:
		m_ControlCommon.ShowWindow(SW_SHOW);
		m_ControlCommon.initData();
		break;
	case 1:
		m_ControlEdit.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}


void DlalogControl::OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnTcnSelchangeTabControlShowTab();
}
