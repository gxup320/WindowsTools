// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "framework.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) BOOL __cdecl gx_SendMessageA(HWND _hWnd, char const* const _Message, PDWORD_PTR _Rev, ...)
{
    va_list argptr;
    CStringA MessageName = _Message + 1;
	if (MessageName == "WM_NULL")
	{
		if (::SendMessageTimeoutA(_hWnd, WM_NULL, NULL, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
            return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == "WM_CREATE")
	{
	}
	else if (MessageName == "WM_DESTROY")
	{
	}
	else if (MessageName == "WM_MOVE")
	{
		va_start(argptr, _Rev);
		POINTS pos = { 0 };
		if (_Message[0] == '@')
		{
			//字符串模式
			const char* lTempStrX = va_arg(argptr, const char*);
			const char* lTempStrY = va_arg(argptr, const char*);
			pos.x = atoi(lTempStrX);
			pos.y = atoi(lTempStrY);
		}
		else if (_Message[0] == '#')
		{
			//窗口模式
			HWND lWndStrX = va_arg(argptr, HWND);
			HWND lWndStrY = va_arg(argptr, HWND);
			char* lTempStrX = new char[MAX_PATH];
			char* lTempStrY = new char[MAX_PATH];
			lTempStrX[0] = 0;
			lTempStrY[0] = 0;
			::SendMessageTimeoutA(lWndStrX, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStrX, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev);
			::SendMessageTimeoutA(lWndStrY, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStrY, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev);
			pos.x = atoi(lTempStrX);
			pos.y = atoi(lTempStrY);
			delete[] lTempStrX;
			delete[] lTempStrY;
		}

		va_end(argptr);
		if (::SendMessageTimeoutA(_hWnd, WM_MOVE, NULL, *((LPARAM*)&pos), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == "WM_SIZE")
	{
		va_start(argptr, _Rev);
		POINTS lsize = { 0 };
		int Mod = 0;
		if (_Message[0] == '@')
		{
			//字符串模式
			const char* lTempStrI = va_arg(argptr, const char*);
			const char* lTempStrX = va_arg(argptr, const char*);
			const char* lTempStrY = va_arg(argptr, const char*);
			Mod = atoi(lTempStrI);
			lsize.x = atoi(lTempStrX);
			lsize.y = atoi(lTempStrY);
		}
		else if (_Message[0] == '#')
		{
			//窗口模式
			DWORD Rev;
			HWND lWndStrX = va_arg(argptr, HWND);
			HWND lWndStrY = va_arg(argptr, HWND);
			HWND lWndStrI = va_arg(argptr, HWND);
			char* lTempStrX = new char[MAX_PATH];
			char* lTempStrY = new char[MAX_PATH];
			char* lTempStrI = new char[MAX_PATH];
			lTempStrX[0] = 0;
			lTempStrY[0] = 0;
			lTempStrI[0] = 0;
			::SendMessageTimeoutA(lWndStrX, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStrX, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &Rev);
			::SendMessageTimeoutA(lWndStrY, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStrY, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &Rev);
			::SendMessageTimeoutA(lWndStrI, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStrI, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &Rev);
			Mod = atoi(lTempStrI);
			lsize.x = atoi(lTempStrX);
			lsize.y = atoi(lTempStrY);
			delete[] lTempStrX;
			delete[] lTempStrY;
			delete[] lTempStrI;
		}

		va_end(argptr);
		if (::SendMessageTimeoutA(_hWnd, WM_SIZE, Mod, *((LPARAM*)&lsize), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == "WM_SETTEXT")
	{
		va_start(argptr, _Rev);
		CStringA lTempStr = "";
		if (_Message[0] == '@')
		{
			//字符串模式
			lTempStr = va_arg(argptr, LPCSTR);
		}
		else if (_Message[0] == '#')
		{
			//窗口模式
			DWORD Rev;
			HWND lWndStr = va_arg(argptr, HWND);
			::SendMessageTimeoutA(lWndStr, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &Rev);
			::SendMessageTimeoutA(lWndStr, WM_GETTEXT, (int)Rev + 1, (LPARAM)lTempStr.GetBuffer((int)Rev + 1), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, &Rev);
			lTempStr.ReleaseBuffer();
		}
		va_end(argptr);
		if (::SendMessageTimeoutA(_hWnd, WM_SETTEXT, NULL, (LPARAM)(LPCSTR)lTempStr, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == "WM_GETTEXT")
	{
		va_start(argptr, _Rev);
		LPSTR lTempStr = va_arg(argptr, char*);
		va_end(argptr);
		if (::SendMessageTimeoutA(_hWnd, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStr, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == "WM_GETTEXTLENGTH")
	{
		if (::SendMessageTimeoutA(_hWnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}

	return FALSE;
}

extern "C" __declspec(dllexport) BOOL __cdecl gx_SendMessageW(HWND _hWnd, wchar_t const* const _Message, PDWORD_PTR _Rev, ...)
{
	va_list argptr;
	CStringW MessageName = _Message + 1;
	if (MessageName == L"WM_NULL")
	{
		if (::SendMessageTimeoutW(_hWnd, WM_NULL, NULL, NULL, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == L"WM_CREATE")
	{
	}
	else if (MessageName == L"WM_DESTROY")
	{
	}
	else if (MessageName == L"WM_MOVE")
	{
		va_start(argptr, _Rev);
		POINTS pos = { 0 };
		const wchar_t* lTempStrX = va_arg(argptr, const wchar_t*);
		const wchar_t* lTempStrY = va_arg(argptr, const wchar_t*);
		pos.x = _wtoi(lTempStrX);
		pos.y = _wtoi(lTempStrY);
		va_end(argptr);
		if (::SendMessageTimeoutW(_hWnd, WM_MOVE, NULL, *((LPARAM*)&pos), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
}
	else if (MessageName == L"WM_SIZE")
	{
		va_start(argptr, _Rev);
		POINTS lsize = { 0 };
		int Mod = 0;
		const wchar_t* lTempStrI = va_arg(argptr, const wchar_t*);
		const wchar_t* lTempStrX = va_arg(argptr, const wchar_t*);
		const wchar_t* lTempStrY = va_arg(argptr, const wchar_t*);
		Mod = _wtoi(lTempStrI);
		lsize.x = _wtoi(lTempStrX);
		lsize.y = _wtoi(lTempStrY);
		va_end(argptr);
		if (::SendMessageTimeoutW(_hWnd, WM_SIZE, Mod, *((LPARAM*)&lsize), SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == L"WM_SETTEXT")
	{
		va_start(argptr, _Rev);
		LPCWSTR lTempStr = va_arg(argptr, LPCWSTR);
		va_end(argptr);
		if (::SendMessageTimeoutW(_hWnd, WM_SETTEXT, NULL, (LPARAM)lTempStr, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == L"WM_GETTEXT")
	{
		va_start(argptr, _Rev);
		LPWSTR lTempStr = va_arg(argptr, LPWSTR);
		va_end(argptr);
		if (::SendMessageTimeoutW(_hWnd, WM_GETTEXT, MAX_PATH + 1, (LPARAM)lTempStr, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if (MessageName == L"WM_GETTEXTLENGTH")
	{
		if (::SendMessageTimeoutW(_hWnd, WM_GETTEXTLENGTH, 0, 0, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 3000, _Rev))
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
