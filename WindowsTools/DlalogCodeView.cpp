// DlalogCodeView.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogCodeView.h"
#include "afxdialogex.h"
#include <Mshtml.h>


// DlalogCodeView 对话框

IMPLEMENT_DYNAMIC(DlalogCodeView, CDialogEx)

DlalogCodeView::DlalogCodeView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CODEVIEW, pParent)
{

}

DlalogCodeView::~DlalogCodeView()
{
}

void DlalogCodeView::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_SOLUTION, ComboSolution);
}


BEGIN_MESSAGE_MAP(DlalogCodeView, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_SOLUTION, &DlalogCodeView::OnCbnSelchangeComboSolution)
END_MESSAGE_MAP()


// DlalogCodeView 消息处理程序


BOOL DlalogCodeView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (CodesNumber > 0)
	{
        for (int i = 0; i < CodesNumber; i++)
        {
            ComboSolution.AddString(Titles[i]);
        }
	}
	//COleVariant loc(_T("about:blank"));
	//ExplorerCode.Navigate2(loc, NULL, NULL, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlalogCodeView::OnCbnSelchangeComboSolution()
{
	// TODO: 在此添加控件通知处理程序代码
	int CurSel = ComboSolution.GetCurSel();
    WriteHTMLcode(Codes[CurSel]);
}

void DlalogCodeView::WriteHTMLcode(LPCTSTR html)
{
//     IDispatch* pHtmlDoc = ExplorerCode.get_Document();
//     if (!pHtmlDoc)
//         return;
//     CComPtr<IHTMLDocument2> doc2;
//     doc2.Attach((IHTMLDocument2*)pHtmlDoc);
//     if (!doc2)
//         return;
//     // Creates a new one-dimensional array
//     SAFEARRAY* psaStrings = SafeArrayCreateVector(VT_VARIANT, 0, 1);
//     if (!psaStrings)
//         return;
//     BSTR bstr = SysAllocString(html);
//     if (bstr)
//     {
//         VARIANT* param;
//         HRESULT hr = SafeArrayAccessData(psaStrings, (LPVOID*)&param);
//         if (SUCCEEDED(hr))
//         {
//             param->vt = VT_BSTR;
//             param->bstrVal = bstr;
//             hr = SafeArrayUnaccessData(psaStrings);
//             if (SUCCEEDED(hr))
//             {
//                 doc2->write(psaStrings);
//                 doc2->close();
//             }
//         }
//     }
//     // SafeArrayDestroy calls SysFreeString for each BSTR!
//     if (psaStrings)
//         SafeArrayDestroy(psaStrings);
}
