// WindowsProject2.cpp : Определяет точку входа для приложения.
//

#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include "framework.h"
#include "WindowsProject2.h"
#include "functions.h"

#define ID_MAIN_WINDOW       999

#define ID_LISTBOX1          100
#define ID_LISTBOX2          101
#define ID_EDIT_INPUT        102

#define ID_ADD_BTN           110
#define ID_CLEAR_BTN         111
#define ID_DELETE_BTN        112
#define ID_TO_RIGHT_BTN      113

HWND hwndListBox1, hwndListBox2;
HWND hwndAddButton;
HWND hwndEditButton, 
	hwndToRightButton,
	hwndClearButton,
	hwndDeleteButton;
HWND hwndEdit;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLines, int nCmdShow)
{

	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = { };

	

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	
	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Hello World",
		WS_OVERLAPPEDWINDOW,

		500, 250, 700, 500,

		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL) 
		return 0;

	hwndListBox1 = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"LISTBOX",
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_MULTICOLUMN,
		10,  10, 200, 300,
		hwnd,
		(HMENU)ID_LISTBOX1,
		NULL,
		NULL
	);
	hwndListBox2 = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"LISTBOX",
		L"",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_MULTICOLUMN,
		400, 10, 200, 300,
		hwnd,
		(HMENU)ID_LISTBOX2,
		NULL,
		NULL
	);
	SendMessage(hwndListBox1, LB_ADDSTRING, 0, (LPARAM)L"Hello");
	SendMessage(hwndListBox1, LB_ADDSTRING, 0, (LPARAM)L"World");
	SendMessage(hwndListBox1, LB_ADDSTRING, 0, (LPARAM)L"My");
	SendMessage(hwndListBox1, LB_ADDSTRING, 0, (LPARAM)L"Dear");
	SendMessage(hwndListBox1, LB_ADDSTRING, 0, (LPARAM)L"Friend");

	ShowWindow(hwnd, nCmdShow);

	hwndAddButton = CreateWindow(
		L"BUTTON",
		L"Add",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		60, 330, 100, 30,
		hwnd,
		(HMENU)ID_ADD_BTN,
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL
	);

	hwndClearButton = CreateWindow(
		L"BUTTON",
		L"Clear",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		250, 200, 100, 30,
		hwnd,
		(HMENU)ID_CLEAR_BTN,
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL
	);

	hwndToRightButton = CreateWindow(
		L"BUTTON",
		L"To Right",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		250, 100, 100, 30,
		hwnd,
		(HMENU)ID_TO_RIGHT_BTN,
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL
	);

	hwndDeleteButton = CreateWindow(
		L"BUTTON",
		L"Delete",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		250, 150, 100, 30,
		hwnd,
		(HMENU)ID_DELETE_BTN,
		(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
		NULL
	);

	hwndEdit = CreateWindow(
		L"EDIT",
		L"Hi",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,
		10, 310, 300, 20,
		hwnd,
		(HMENU)ID_EDIT_INPUT,
		hInstance,
		NULL
	);

	std::cout << "Created Window!" << std::endl;

	MSG msg = { };

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) 
{
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == ID_TO_RIGHT_BTN)
		{	
			std::cout << SendMessage(hwndListBox1, LB_GETTEXTLEN, 1, NULL) << std::endl;
			return 0;
		}*/
		if (LOWORD(wParam) == ID_TO_RIGHT_BTN)
		{
			TCHAR Text;
			toRightListBox(hwndListBox1, hwndListBox2, &Text);
		}
		else if (LOWORD(wParam) == ID_ADD_BTN)
		{
			int textSize = 255;
			TCHAR * text = new TCHAR[textSize];	

			SendMessage(hwndEdit, WM_GETTEXT, (WPARAM)textSize, (LPARAM)text);

			if (existInListBox(hwndListBox1, text))
			{
				return 0;
			}
			SendMessage(hwndListBox1, LB_ADDSTRING, 0, (LPARAM)text);

			
		}
		else if (LOWORD(wParam) == ID_CLEAR_BTN)
		{
			SendMessage(hwndListBox1, LB_SETCURSEL, (WPARAM)-1, NULL);
			SendMessage(hwndListBox2, LB_SETCURSEL, (WPARAM)-1, NULL);

			
		}
		else if (LOWORD(wParam) == ID_DELETE_BTN)
		{
			int index = (int)SendMessage(hwndListBox1, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
				SendMessage(hwndListBox1, LB_DELETESTRING, (WPARAM)index, NULL);
				

			index = (int)SendMessage(hwndListBox2, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
				SendMessage(hwndListBox2, LB_DELETESTRING, (WPARAM)index, NULL);
		}
		break;
	}
	case WM_CLOSE:
	{
		// if (MessageBox(hwnd, L"Do you Really want to quit the application?", L"MyApp", MB_OKCANCEL) == IDOK)

		DestroyWindow(hwnd);
		return 0;
	}
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

