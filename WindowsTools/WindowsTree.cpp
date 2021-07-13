// WindowsTree.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "WindowsTree.h"
#include "afxdialogex.h"


// WindowsTree 对话框

IMPLEMENT_DYNAMIC(WindowsTree, CDialogEx)

WindowsTree::WindowsTree(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDOWSTOOLS_DIALOG, pParent)
{

}

WindowsTree::~WindowsTree()
{
}

void WindowsTree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WindowsTree, CDialogEx)
END_MESSAGE_MAP()


// WindowsTree 消息处理程序
