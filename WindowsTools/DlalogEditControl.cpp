// DialogEditControl.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogEditControl.h"
#include "afxdialogex.h"


// DialogEditControl 对话框

IMPLEMENT_DYNAMIC(DlalogEditControl, CDialogEx)

DlalogEditControl::DlalogEditControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EDIT_CONTROL, pParent)
{

}

DlalogEditControl::~DlalogEditControl()
{
}

void DlalogEditControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EDIT_TEXT, EditEditText);
	DDX_Control(pDX, IDC_EDIT_EDIT_LIMIT_TEXT_LENGTH, EditEditLimitTextLength);
}


BEGIN_MESSAGE_MAP(DlalogEditControl, CDialogEx)
	ON_COMMAND(IDOK, &DlalogEditControl::OnIdok)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_TEXT_SET, &DlalogEditControl::OnBnClickedButtonEditTextSet)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_TEXT_GET, &DlalogEditControl::OnBnClickedButtonEditTextGet)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_SELECT, &DlalogEditControl::OnBnClickedButtonEditSelect)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_COPY, &DlalogEditControl::OnBnClickedButtonEditCopy)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_CUT, &DlalogEditControl::OnBnClickedButtonEditCut)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_PASTE, &DlalogEditControl::OnBnClickedButtonEditPaste)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_DELETE, &DlalogEditControl::OnBnClickedButtonEditDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_UNDO, &DlalogEditControl::OnBnClickedButtonEditUndo)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_LIMIT_SET, &DlalogEditControl::OnBnClickedButtonEditLimitSet)
END_MESSAGE_MAP()


// DialogEditControl 消息处理程序


void DlalogEditControl::OnIdok()
{
	// TODO: 在此添加命令处理程序代码
}


void DlalogEditControl::OnBnClickedButtonEditTextSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	EditEditText.GetWindowText(TempString);
	DWORD_PTR r;
	LRESULT re = ::SendMessageTimeout(hWnd, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)TempString, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &r);
	if (re)
	{
		//成功
		if (r == TRUE)
		{
			//设置成功
		}
		else if (r == FALSE)
		{
			MessageBox(_T("Error:FALSE"));
		}
		else if (r == LB_ERRSPACE)
		{
			MessageBox(_T("Error:LB_ERRSPACE"));
		}
		else if (r == CB_ERRSPACE)
		{
			MessageBox(_T("Error:CB_ERRSPACE"));
		}
		else if (r == CB_ERR)
		{
			MessageBox(_T("Error:CB_ERR"));
		}
		else
		{
#ifdef _WIN64
			TempString.Format(_T("Error:%lld"), r);
#else
			TempString.Format(_T("Error:%d"), r);
#endif // _WIN64
			
			MessageBox(TempString);
		}
	}
	else
	{
		//失败
		DWORD dwLastError = GetLastError();
		DrowErrorCode(dwLastError, m_hWnd);
	}
}


void DlalogEditControl::OnBnClickedButtonEditTextGet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);

	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	//EditEditText.GetWindowText(TempString);
	DWORD_PTR r;
	LRESULT TextLength = ::SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0);
	LRESULT re = ::SendMessageTimeout(hWnd, WM_GETTEXT, TextLength + 1, (LPARAM)TempString.GetBuffer((int)TextLength + 1), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &r);
	TempString.ReleaseBuffer();
	if (re)
	{
		//成功
		EditEditText.SetWindowText(TempString);
	}
	else
	{
		//失败
		DWORD dwLastError = GetLastError();
		DrowErrorCode(dwLastError, m_hWnd);
	}
}


void DlalogEditControl::OnBnClickedButtonEditSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	INT lStart = 0;
	INT lEnd = 0;
	GetDlgItem(IDC_EDIT_EDIT_SELECT_START)->GetWindowText(TempString);
	i_ret = _stscanf(TempString, _T("%d"), &lStart);
	if (i_ret == 0)
	{
		lStart = 0;
	}
	GetDlgItem(IDC_EDIT_EDIT_SELECT_END)->GetWindowText(TempString);
	i_ret = _stscanf(TempString, _T("%d"), &lEnd);
	if (i_ret == 0)
	{
		lEnd = 0;
	}
	::SendMessage(hWnd, EM_SETSEL, lStart, lEnd);
}


void DlalogEditControl::OnBnClickedButtonEditCopy()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SendMessage(hWnd, WM_COPY, 0, 0);
}


void DlalogEditControl::OnBnClickedButtonEditCut()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SendMessage(hWnd, WM_CUT, 0, 0);
}


void DlalogEditControl::OnBnClickedButtonEditPaste()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SendMessage(hWnd, WM_PASTE, 0, 0);
}


void DlalogEditControl::OnBnClickedButtonEditDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SendMessage(hWnd, WM_CLEAR, 0, 0);
}


void DlalogEditControl::OnBnClickedButtonEditUndo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	::SendMessage(hWnd, EM_UNDO, 0, 0);
}


void DlalogEditControl::OnBnClickedButtonEditLimitSet()
{
	// TODO: 在此添加控件通知处理程序代码
	CString TempString = _T("");
	HWND hWnd = NULL;
	int TextLength = 0;
	OperateEdit->GetWindowText(TempString);
	int i_ret = _stscanf(TempString, _T("%u"), (PUINT)&hWnd);
	if (i_ret == 0 || hWnd == NULL)
	{
		return;
	}
	EditEditLimitTextLength.GetWindowText(TempString);
	_stscanf(TempString, _T("%d"), &TextLength);
	::SendMessage(hWnd, EM_LIMITTEXT, TextLength, NULL);
}
