// DlalogGenerateFindCode.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogGenerateFindCode.h"
#include "Language.h"
#include "afxdialogex.h"


// DlalogGenerateFindCode 对话框

struct WINDOWINFOSTRUCT
{
	CString Title;
	CString ClassName;
	CRect rect;
	int DlgCtrlID;
	LONG Style;
	LONG StyleEx;
	UINT showCmd;
	HWND PhWnd;
	DWORD ProcessID;
	BOOL IsWOW64;
	WINDOWINFOSTRUCT* Next;
	WINDOWINFOSTRUCT* Child;
};

IMPLEMENT_DYNAMIC(DlalogGenerateFindCode, CDialogEx)

DlalogGenerateFindCode::DlalogGenerateFindCode(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GENERATE_FIND_CODE, pParent)
{

}

DlalogGenerateFindCode::~DlalogGenerateFindCode()
{
}

void DlalogGenerateFindCode::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlalogGenerateFindCode, CDialogEx)
//	ON_COMMAND(IDOK, &DlalogGenerateFindCode::OnIdok)
END_MESSAGE_MAP()


// DlalogGenerateFindCode 消息处理程序


//void DlalogGenerateFindCode::OnIdok()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void DlalogGenerateFindCode::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL DlalogGenerateFindCode::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	SetWindowText(AllLanguage->GetLanguageStruct()->TITLE_GENERATE_FIND_CODE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
