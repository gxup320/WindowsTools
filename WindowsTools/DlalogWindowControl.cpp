// DialogWindowControl.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogWindowControl.h"
#include "afxdialogex.h"
#include <lmerr.h>
#include "Language.h"


// DialogWindowControl 对话框

IMPLEMENT_DYNAMIC(DlalogWindowControl, CDialogEx)

DlalogWindowControl::DlalogWindowControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WINDOW_CONTROL, pParent)
{

}

DlalogWindowControl::~DlalogWindowControl()
{
}

void DlalogWindowControl::initData()
{
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	LONG lWindowLong = ::GetWindowLong(hWnd, GWL_EXSTYLE);
	if ((lWindowLong & WS_EX_LAYERED) == WS_EX_LAYERED)
	{
		CheckControlWsExLayered.SetCheck(BST_CHECKED);
		Unattended = TRUE;
		OnBnClickedButtonTransparentGet();
		Unattended = FALSE;
	}
	else
	{
		CheckControlWsExLayered.SetCheck(BST_UNCHECKED);
	}

}

void DlalogWindowControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_TRANSPARENT_COLOR, ColorTransparent);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT_ALPHA, SliderTransparent);
	DDX_Control(pDX, IDC_CHECK_TRANSPARENT_COLOR, CheckTransparentColor);
	DDX_Control(pDX, IDC_CHECK_TRANSPARENT_ALPHA, CheckTransparentAlpha);
	DDX_Control(pDX, IDC_CHECK_CONTROL_WS_EX_LAYERED, CheckControlWsExLayered);
}


BEGIN_MESSAGE_MAP(DlalogWindowControl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TRANSPARENT_GET, &DlalogWindowControl::OnBnClickedButtonTransparentGet)
	ON_BN_CLICKED(IDC_BUTTON_TRANSPARENT_SET, &DlalogWindowControl::OnBnClickedButtonTransparentSet)
	ON_BN_CLICKED(IDC_CHECK_CONTROL_WS_EX_LAYERED, &DlalogWindowControl::OnBnClickedCheckControlWsExLayered)
END_MESSAGE_MAP()


BOOL DlalogWindowControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SliderTransparent.SetRange(0, 255);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


// DialogWindowControl 消息处理程序


void DlalogWindowControl::OnBnClickedButtonTransparentGet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	COLORREF color;
	DWORD Flags = 0;
	BYTE Alpha = 0;
	OperateEdit->GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	BOOL re = ::GetLayeredWindowAttributes(hWnd, &color, &Alpha, &Flags);
	if (re)
	{
		//成功
		if (Flags & LWA_COLORKEY)
		{
			CheckTransparentColor.SetCheck(BST_CHECKED);
		}
		else
		{
			CheckTransparentColor.SetCheck(BST_UNCHECKED);
		}
		if (Flags & LWA_ALPHA)
		{
			CheckTransparentAlpha.SetCheck(BST_CHECKED);
		}
		else
		{
			CheckTransparentAlpha.SetCheck(BST_UNCHECKED);
		}
		ColorTransparent.SetColor(color);
		SliderTransparent.SetPos(Alpha);
	}
	else if(!Unattended)
	{
		//失败
		DWORD dwLastError = GetLastError();
		DrowErrorCode(dwLastError, m_hWnd);
	}
}




void DlalogWindowControl::OnBnClickedButtonTransparentSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	COLORREF color;
	DWORD Flags = 0;
	BYTE Alpha = 0;
	OperateEdit->GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	color = ColorTransparent.GetColor();
	if (CheckTransparentColor.GetCheck() == BST_CHECKED)
	{
		Flags |= LWA_COLORKEY;
	}
	if (CheckTransparentAlpha.GetCheck() == BST_CHECKED)
	{
		Flags |= LWA_ALPHA;
	}
	Alpha = SliderTransparent.GetPos();
	BOOL re = ::SetLayeredWindowAttributes(hWnd, color, Alpha, Flags);
	if (!re && !Unattended)
	{
		//失败
		DWORD dwLastError = GetLastError();
		DrowErrorCode(dwLastError, m_hWnd);
	}
}


void DlalogWindowControl::OnBnClickedCheckControlWsExLayered()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (CheckControlWsExLayered.GetCheck() == BST_CHECKED)
	{
		//add WsExLayered
		LONG lWindowLong = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		::SetWindowLong(hWnd, GWL_EXSTYLE, lWindowLong | WS_EX_LAYERED);
	}
	else
	{
		LONG lWindowLong = ::GetWindowLong(hWnd, GWL_EXSTYLE);
		::SetWindowLong(hWnd, GWL_EXSTYLE, lWindowLong & ~ WS_EX_LAYERED);
	}
	LONG lWindowLong = ::GetWindowLong(hWnd, GWL_EXSTYLE);
	if (lWindowLong & WS_EX_LAYERED)
	{
		CheckControlWsExLayered.SetCheck(BST_CHECKED);
	}
	else
	{
		CheckControlWsExLayered.SetCheck(BST_UNCHECKED);
	}
}
