﻿// DialogWindowControl.cpp: 实现文件
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
	OnBnClickedButtonMoveGet();
}

void DlalogWindowControl::moveLock(int x, int y)
{
	MoveLockX = x;
	MoveLockY = y;
	CString TempString;
	CString TempString2;
	TempString = _T("lock\n[X]x[Y]");
	TempString2.Format(_T("%d"), MoveLockX);
	TempString.Replace(_T("[X]"), TempString2);
	TempString2.Format(_T("%d"), MoveLockY);
	TempString.Replace(_T("[Y]"), TempString2);
	CheckWindowControlMoveLock.SetWindowText(TempString);
}

void DlalogWindowControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_TRANSPARENT_COLOR, ColorTransparent);
	DDX_Control(pDX, IDC_SLIDER_TRANSPARENT_ALPHA, SliderTransparent);
	DDX_Control(pDX, IDC_CHECK_TRANSPARENT_COLOR, CheckTransparentColor);
	DDX_Control(pDX, IDC_CHECK_TRANSPARENT_ALPHA, CheckTransparentAlpha);
	DDX_Control(pDX, IDC_CHECK_CONTROL_WS_EX_LAYERED, CheckControlWsExLayered);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CONTROL_MOVE_LEFT, EditWindowControlMoveLeft);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CONTROL_MOVE_RIGHT, EditWindowControlMoveRight);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CONTROL_MOVE_TOP, EditWindowControlMoveTop);
	DDX_Control(pDX, IDC_EDIT_WINDOW_CONTROL_MOVE_BOTTOM, EditWindowControlMoveBottom);
	DDX_Control(pDX, IDC_CHECK_MOVE_REPAINT, CheckMoveRepaint);
	DDX_Control(pDX, IDC_CHECK_WINDOW_CONTROL_MOVE_LOCL, CheckWindowControlMoveLock);
}


BEGIN_MESSAGE_MAP(DlalogWindowControl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TRANSPARENT_GET, &DlalogWindowControl::OnBnClickedButtonTransparentGet)
	ON_BN_CLICKED(IDC_BUTTON_TRANSPARENT_SET, &DlalogWindowControl::OnBnClickedButtonTransparentSet)
	ON_BN_CLICKED(IDC_CHECK_CONTROL_WS_EX_LAYERED, &DlalogWindowControl::OnBnClickedCheckControlWsExLayered)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_GET, &DlalogWindowControl::OnBnClickedButtonMoveGet)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_SET, &DlalogWindowControl::OnBnClickedButtonMoveSet)
	ON_EN_CHANGE(IDC_EDIT_WINDOW_CONTROL_MOVE_LEFT, &DlalogWindowControl::OnEnChangeEditWindowControlMoveLeft)
	ON_EN_CHANGE(IDC_EDIT_WINDOW_CONTROL_MOVE_RIGHT, &DlalogWindowControl::OnEnChangeEditWindowControlMoveRight)
	ON_EN_CHANGE(IDC_EDIT_WINDOW_CONTROL_MOVE_TOP, &DlalogWindowControl::OnEnChangeEditWindowControlMoveTop)
	ON_EN_CHANGE(IDC_EDIT_WINDOW_CONTROL_MOVE_BOTTOM, &DlalogWindowControl::OnEnChangeEditWindowControlMoveBottom)
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


void DlalogWindowControl::OnBnClickedButtonMoveGet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	HWND phWnd = NULL;
	int lw = 0;
	int th = 0;
	RECT rect = { };
	RECT srect = { };
	RECT cltRect = { };
	RECT wndRect = { };
	OperateEdit->GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	phWnd = ::GetParent(hWnd);
	if (phWnd != NULL && ::IsChild(phWnd, hWnd) == TRUE)
	{
		::GetClientRect(phWnd, &cltRect);
		::GetWindowRect(phWnd, &wndRect);
		lw = ((wndRect.right - wndRect.left) - (cltRect.right - cltRect.left)) / 2;
		th = ((wndRect.bottom - wndRect.top) - (cltRect.bottom - cltRect.top)) - lw;
	}
	::GetWindowRect(hWnd, &rect);
	srect.left = rect.left - wndRect.left - lw;
	srect.right = rect.right - wndRect.left - lw;
	srect.top = rect.top - wndRect.top - th;
	srect.bottom = rect.bottom - wndRect.top - th;
	if (MoveLockAutoing == FALSE)
	{
		MoveLockAutoing = TRUE;
		TempString.Format(_T("%d"), srect.left);
		EditWindowControlMoveLeft.SetWindowText(TempString);
		TempString.Format(_T("%d"), srect.right);
		EditWindowControlMoveRight.SetWindowText(TempString);
		TempString.Format(_T("%d"), srect.top);
		EditWindowControlMoveTop.SetWindowText(TempString);
		TempString.Format(_T("%d"), srect.bottom);
		EditWindowControlMoveBottom.SetWindowText(TempString);
		moveLock(srect.right - srect.left, srect.bottom - srect.top);
		MoveLockAutoing = FALSE;
	}

}


void DlalogWindowControl::OnBnClickedButtonMoveSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	_stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	RECT rect = { };
	EditWindowControlMoveLeft.GetWindowText(TempString);
	_stscanf(TempString, _T("%d"), &rect.left);
	EditWindowControlMoveRight.GetWindowText(TempString);
	_stscanf(TempString, _T("%d"), &rect.right);
	EditWindowControlMoveTop.GetWindowText(TempString);
	_stscanf(TempString, _T("%d"), &rect.top);
	EditWindowControlMoveBottom.GetWindowText(TempString);
	_stscanf(TempString, _T("%d"), &rect.bottom);
	if (CheckMoveRepaint.GetCheck() == BST_CHECKED)
	{
		::MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
	}
	else
	{
		::MoveWindow(hWnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, FALSE);
	}
}


void DlalogWindowControl::OnEnChangeEditWindowControlMoveLeft()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (MoveLockAutoing == FALSE)
	{
		MoveLockAutoing = TRUE;
		if (CheckWindowControlMoveLock.GetCheck() == BST_CHECKED)
		{
			CString TempString;
			EditWindowControlMoveLeft.GetWindowText(TempString);
			int left = 0;
			_stscanf(TempString, _T("%d"), &left);
			TempString.Format(_T("%d"), left + MoveLockX);
			EditWindowControlMoveRight.SetWindowText(TempString);
		}
		else
		{
			CString TempString;
			RECT rect = { };
			EditWindowControlMoveLeft.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.left);
			EditWindowControlMoveRight.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.right);
			EditWindowControlMoveTop.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.top);
			EditWindowControlMoveBottom.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.bottom);
			moveLock(rect.right - rect.left, rect.bottom - rect.top);
		}
		MoveLockAutoing = FALSE;
	}
}


void DlalogWindowControl::OnEnChangeEditWindowControlMoveRight()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (MoveLockAutoing == FALSE)
	{
		MoveLockAutoing = TRUE;
		if (CheckWindowControlMoveLock.GetCheck() == BST_CHECKED)
		{
			CString TempString;
			EditWindowControlMoveRight.GetWindowText(TempString);
			int right = 0;
			_stscanf(TempString, _T("%d"), &right);
			TempString.Format(_T("%d"), right - MoveLockX);
			EditWindowControlMoveLeft.SetWindowText(TempString);
		}
		else
		{
			CString TempString;
			RECT rect = { };
			EditWindowControlMoveLeft.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.left);
			EditWindowControlMoveRight.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.right);
			EditWindowControlMoveTop.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.top);
			EditWindowControlMoveBottom.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.bottom);
			moveLock(rect.right - rect.left, rect.bottom - rect.top);
		}
		MoveLockAutoing = FALSE;
	}
}


void DlalogWindowControl::OnEnChangeEditWindowControlMoveTop()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (MoveLockAutoing == FALSE)
	{
		MoveLockAutoing = TRUE;
		if (CheckWindowControlMoveLock.GetCheck() == BST_CHECKED)
		{
			CString TempString;
			EditWindowControlMoveTop.GetWindowText(TempString);
			int top = 0;
			_stscanf(TempString, _T("%d"), &top);
			TempString.Format(_T("%d"), top + MoveLockY);
			EditWindowControlMoveBottom.SetWindowText(TempString);
		}
		else
		{
			CString TempString;
			RECT rect = { };
			EditWindowControlMoveLeft.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.left);
			EditWindowControlMoveRight.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.right);
			EditWindowControlMoveTop.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.top);
			EditWindowControlMoveBottom.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.bottom);
			moveLock(rect.right - rect.left, rect.bottom - rect.top);
		}
		MoveLockAutoing = FALSE;
	}

}


void DlalogWindowControl::OnEnChangeEditWindowControlMoveBottom()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (MoveLockAutoing == FALSE)
	{
		MoveLockAutoing = TRUE;
		if (CheckWindowControlMoveLock.GetCheck() == BST_CHECKED)
		{
			CString TempString;
			EditWindowControlMoveBottom.GetWindowText(TempString);
			int bottom = 0;
			_stscanf(TempString, _T("%d"), &bottom);
			TempString.Format(_T("%d"), bottom - MoveLockY);
			EditWindowControlMoveTop.SetWindowText(TempString);
		}
		else
		{
			CString TempString;
			RECT rect = { };
			EditWindowControlMoveLeft.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.left);
			EditWindowControlMoveRight.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.right);
			EditWindowControlMoveTop.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.top);
			EditWindowControlMoveBottom.GetWindowText(TempString);
			_stscanf(TempString, _T("%d"), &rect.bottom);
			moveLock(rect.right - rect.left, rect.bottom - rect.top);
		}
		MoveLockAutoing = FALSE;
	}
}
