#pragma once

#ifndef STATUSBAR_H
#define PAINTDLL __declspec(dllexport)
#else
#define PAINTDLL __declspec(dllimport)
#endif

#include <Windows.h>
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")

#include <CommonControls.h>
#include <Commdlg.h>

namespace MyPaint
{
	class PAINTDLL StatusBar
	{
	private:
		HINSTANCE		hInst_;
		HWND			hParent_;
		HWND			hStatusBar_;
		long			ID_;
	public:
		StatusBar();
		~StatusBar();

		void			Create(HWND parentWnd, long ID, HINSTANCE hParentInst,
			long lStyle = WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP | SBARS_TOOLTIPS);

		HWND			GetThisHandle();
		int				GetThisID();

		void			Resize();
	};
}