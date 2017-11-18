#include "stdafx.h"
#include "StatusBar.h"

namespace MyPaint
{
	StatusBar::StatusBar()
	{
		this->hInst_ = NULL;
		this->hParent_ = NULL;
		this->hStatusBar_ = NULL;
		this->ID_ = -1;
	}


	StatusBar::~StatusBar()
	{

	}

	void StatusBar::Create(HWND parentWnd, long ID, HINSTANCE hParentInst, long lStyle)
	{
		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES;
		InitCommonControlsEx(&icex);

		this->hInst_ = hParentInst;
		this->hParent_ = parentWnd;
		this->ID_ = ID;
		this->hStatusBar_ = CreateWindow(STATUSCLASSNAME, NULL, lStyle, 0, 0, CW_USEDEFAULT, 100, this->hParent_, (HMENU)ID, this->hInst_, NULL);
	}

	HWND StatusBar::GetThisHandle()
	{
		return this->hStatusBar_;
	}

	int StatusBar::GetThisID()
	{
		return this->ID_;
	}

	void StatusBar::Resize()
	{
		RECT main;
		GetWindowRect(this->hParent_, &main);

		int nStatusSize[] = { main.right * 6 / 10, main.right * 6 / 10 + main.right / 12 , -1 };
		SendMessage(this->hStatusBar_, SB_SETPARTS, 3, (LPARAM)&nStatusSize);
		MoveWindow(this->hStatusBar_, 0, 0, main.right, main.bottom, TRUE);
	}
}