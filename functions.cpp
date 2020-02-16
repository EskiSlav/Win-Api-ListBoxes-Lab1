#include "functions.h"

int existInListBox(HWND hListBox, TCHAR* text)
{
	TCHAR *compareText = NULL;
	int itemCount = (int)SendMessage(hListBox, LB_GETCOUNT, 0, 0);
	if (itemCount == LB_ERR)
		return 0;
	for (int i = 0; i < itemCount; i++)
	{
		int itemLength = (int)SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM)i, 0);
		compareText = new TCHAR[itemLength + 1];

		SendMessage(hListBox, LB_GETTEXT, (WPARAM)i, (LPARAM)compareText);

		if (!_tcscmp(compareText, text))
		{
			return 1;
		}
		delete[] compareText;
		compareText = NULL;
	}
	return 0;
}

int toRightListBox(HWND hList1, HWND hList2, TCHAR * Buffer)
{
	int itemIndex = (int)SendMessage(hList1, LB_GETCURSEL, 0, 0);
	if (itemIndex == LB_ERR)
	{
		return 0;
	}

	int itemLength = (int)SendMessage(hList1, LB_GETTEXTLEN, (WPARAM)itemIndex, 0);

	Buffer = new TCHAR[itemLength + 1];

	SendMessage(hList1, LB_GETTEXT, (WPARAM)itemIndex, (LPARAM)Buffer);

	if (existInListBox(hList2, Buffer))
	{
		return 0;
	}

	SendMessage(hList2, LB_ADDSTRING, 0, (LPARAM)Buffer);

	delete[] Buffer;
	Buffer = NULL;
	return 1;
}
