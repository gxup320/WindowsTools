// DialogSelectWindow.cpp: 实现文件
//

#include "pch.h"
#include "WindowsTools.h"
#include "DlalogSelectWindow.h"
#include "afxdialogex.h"

// DialogSelectWindow 对话框

IMPLEMENT_DYNAMIC(DlalogSelectWindow, CDialogEx)

DlalogSelectWindow::DlalogSelectWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECT_WINDOW, pParent)
	, pDC(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

DlalogSelectWindow::~DlalogSelectWindow()
{
}

void DlalogSelectWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DlalogSelectWindow, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CLOSE()
//	ON_WM_GETDLGCODE()
END_MESSAGE_MAP()


// DialogSelectWindow 消息处理程序


void DlalogSelectWindow::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// create and select a solid blue brush
		CBrush brushBlue(RGB(0, 0, 255));
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(pDC);
		CBrush* pOldBrush = dcMemory.SelectObject(&brushBlue);

		// create and select a thick, black pen
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		CPen* pOldPen = dcMemory.SelectObject(&penBlack);
		CBitmap bmp;

		// get our client rectangle
		CRect rect;
		GetClientRect(rect);

		// shrink our rect 20 pixels in each direction
		rect.DeflateRect(0, 0);

		bmp.CreateBitmap(rect.right, rect.bottom, 1, 32, NULL);
		CBitmap* pOldBitmap = dcMemory.SelectObject(&bmp);


		// draw a thick black rectangle filled with blue
		dcMemory.Rectangle(rect);
		pDC->BitBlt(0, 0, rect.right, rect.bottom, &dcMemory,
			0, 0, SRCCOPY);
		// put back the old objects
		dcMemory.SelectObject(pOldBrush);
		dcMemory.SelectObject(pOldPen);

		dcMemory.SelectObject(pOldBitmap);
		CDialogEx::OnPaint();
	}
}

DWORD MarkWindows(DlalogSelectWindow* MarksDlg)
{
	extern HWND MarkWindowHwnd;
	RECT Rect_temp = { 0 };
	int SW_Temp = SW_HIDE;
	while (!MarksDlg->ALL_EXITING)
	{
		if (IsWindow(MarkWindowHwnd))
		{
			RECT Rect;
			::GetWindowRect(MarkWindowHwnd, &Rect);
			Rect.left -= 3;
			Rect.top -= 3;
			Rect.right += 3;
			Rect.bottom += 3;
			if (Rect.left < 0)
			{
				Rect.left = 0;
			}
			if (Rect.top < 0)
			{
				Rect.top = 0;
			}
			int  cx = GetSystemMetrics(SM_CXSCREEN);
			int  cy = GetSystemMetrics(SM_CYSCREEN);
			if (Rect.right > cx)
			{
				Rect.right = cx;
			}
			if (Rect.bottom > cy)
			{
				Rect.bottom = cy;
			}
			if (memcmp(&Rect, &Rect_temp, sizeof(RECT)) != 0)
			{
				Rect_temp = Rect;
				MarksDlg->SetWindowPos(&CWnd::wndTopMost, Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOACTIVATE);
			}
			else
			{
				MarksDlg->SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
			}
			if (SW_Temp != SW_SHOWNA)
			{
				SW_Temp = SW_SHOWNA;
				MarksDlg->ShowWindow(SW_SHOWNA);

			}
		}
		else
		{
			if (SW_Temp != SW_HIDE)
			{
				SW_Temp = SW_HIDE;
				MarksDlg->ShowWindow(SW_HIDE);
			}
		}
		Sleep(100);
	}
	return 0;
}

BOOL DlalogSelectWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	SetBackgroundColor(RGB(0, 0, 255));
	pDC = GetDC();
	LONG temp = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	SetWindowLong(m_hWnd, GWL_EXSTYLE, temp | WS_EX_TRANSPARENT | WS_EX_LAYERED);
	SetLayeredWindowAttributes(RGB(0, 0, 255), 255, LWA_COLORKEY);
	//创建死循环，监控窗口
	hThread_MarkWindows = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MarkWindows, this, 0, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlalogSelectWindow::OnClose()
{
	return;
	CDialogEx::OnClose();
}



BOOL DlalogSelectWindow::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	ALL_EXITING = TRUE;
	DWORD TexitCode;
	if (hThread_MarkWindows != NULL)
	{
		TexitCode = STILL_ACTIVE;
		while (TexitCode == STILL_ACTIVE)
		{
			DoEvents();
			Sleep(1);
			GetExitCodeThread(hThread_MarkWindows, &TexitCode);
		}
		TRACE("hThread_MarkWindows:%u\n", TexitCode);
		CloseHandle(hThread_MarkWindows);
	}
	return CDialogEx::DestroyWindow();
}
