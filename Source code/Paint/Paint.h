#pragma once

#include "CShapeCache.h"
#include "CShapeFactory.h"
#include "StatusBar.h"
#include "Convert.h"
#pragma comment(lib, "PaintDll.lib")

#include "GDIPlusSetup.h"
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include "Application.h"
#include "resource.h"
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#include <windowsx.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND								ghWndMain;
HDC									hdcMem = NULL;

std::vector<MyPaint::IShape*>		gShapes;
std::vector<MyPaint::IShape*>		gShapesUndoRedo;
BOOL								gDrawing = FALSE;

enum ShapeType
{
	LINE,
	RECTANGLE,
	ELLIPSE
};
ShapeType							gShapeType;

POINT								gLeftTop;
POINT								gRightBottom;

RECT								gDrawArea;

MyPaint::CShapeFactory				gShapeFact;
MyPaint::StatusBar					*gStatusBar = NULL;

UINT								ribbonHeight;

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Handle Message declarations of functions
void				OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void				OnPaint(HWND hwnd);
void				OnDestroy(HWND hwnd);
void				OnClose(HWND hwnd);
BOOL				OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void				OnSize(HWND hwnd, UINT state, int cx, int cy);
void				OnMove(HWND hwnd, int x, int y);
void				OnKey(HWND hwnd, UINT vk, BOOL fDown, int cRepeat, UINT flags);

void				OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
void				OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void				OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);

void				SaveFileDialog(HWND hwnd); 
void				OpenFileDialog(HWND hwnd);

HDC					GetHDCParent(HWND hwnd, SIZE size);