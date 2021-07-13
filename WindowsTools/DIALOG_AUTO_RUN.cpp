// DIALOG_AUTO_RUN.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DIALOG_AUTO_RUN.h"
#include "afxdialogex.h"


// DIALOG_AUTO_RUN 对话框

IMPLEMENT_DYNAMIC(DIALOG_AUTO_RUN, CDialogEx)

DIALOG_AUTO_RUN::DIALOG_AUTO_RUN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AUTO_RUN, pParent)
{

}

DIALOG_AUTO_RUN::~DIALOG_AUTO_RUN()
{
}

void DIALOG_AUTO_RUN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DIALOG_AUTO_RUN, CDialogEx)
END_MESSAGE_MAP()


// DIALOG_AUTO_RUN 消息处理程序
