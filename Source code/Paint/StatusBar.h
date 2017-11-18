#pragma once

namespace MyPaint
{
	class StatusBar
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