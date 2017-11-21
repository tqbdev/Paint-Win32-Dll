// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "stdafx.h"
#include "RibbonFramework.h"
#include "Application.h"
#include "RibbonIDs.h"

IUIFramework *g_pFramework = NULL;  // Reference to the Ribbon framework.
IUIApplication *g_pApplication = NULL;  // Reference to the Application object.

										//
										//  FUNCTION: InitializeFramework(HWND)
										//
										//  PURPOSE:  Initialize the Ribbon framework and bind a Ribbon to the application.
										//
										//  COMMENTS:
										//
										//    To get a Ribbon to display, the Ribbon framework must be initialized. 
										//    This involves three important steps:
										//      1) Instantiating the Ribbon framework object (CLSID_UIRibbonFramework).
										//      2) Passing the host HWND and IUIApplication object to the framework.
										//      3) Loading the binary markup compiled by UICC.exe.
										//
										//
bool InitializeFramework(HWND hWnd)
{
	// Here we instantiate the Ribbon framework object.
	HRESULT hr = CoCreateInstance(CLSID_UIRibbonFramework, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&g_pFramework));
	if (FAILED(hr))
	{
		return false;
	}

	// Next, we create the application object (IUIApplication) and call the framework Initialize method, 
	// passing the application object and the host HWND that the Ribbon will attach itself to.
	hr = CApplication::CreateInstance(&g_pApplication);
	if (FAILED(hr))
	{
		return false;
	}

	hr = g_pFramework->Initialize(hWnd, g_pApplication);
	if (FAILED(hr))
	{
		return false;
	}

	// Finally, we load the binary markup.  This will initiate callbacks to the IUIApplication object 
	// that was provided to the framework earlier, allowing command handlers to be bound to individual
	// commands.
	hr = g_pFramework->LoadUI(GetModuleHandle(NULL), L"APPLICATION_RIBBON");
	if (FAILED(hr))
	{
		return false;
	}
	
	return true;
}

//
//  FUNCTION: DestroyFramework()
//
//  PURPOSE:  Tears down the Ribbon framework.
//
//
void DestroyFramework()
{
	if (g_pFramework)
	{
		g_pFramework->Destroy();
		g_pFramework->Release();
		g_pFramework = NULL;
	}

	if (g_pApplication)
	{
		g_pApplication->Release();
		g_pApplication = NULL;
	}
}

//
//  FUNCTION: GetRibbonHeight()
//
//  PURPOSE:  Get the ribbon height.
//
//
HRESULT GetRibbonHeight(UINT* ribbonHeight)
{
	HRESULT hr = S_OK;

	if (g_pFramework)
	{
		IUIRibbon* pRibbon = NULL;

		if (SUCCEEDED(g_pFramework->GetView(0, IID_PPV_ARGS(&pRibbon))))
		{
			hr = pRibbon->GetHeight(ribbonHeight);
			pRibbon->Release();
		}
	}

	return hr;
}

HRESULT ChangeStateRedo(bool state)
{
	HRESULT hr = S_OK;

	PROPVARIANT enable; 
	enable.vt = VT_BOOL;

	if (state) enable.boolVal = -1;
	else enable.boolVal = 0;

	if (g_pFramework)
	{
		hr = g_pFramework->SetUICommandProperty(ID_CMD_REDO, UI_PKEY_Enabled, enable);
	}

	return hr;
}

HRESULT ChangeStateUndo(bool state)
{
	HRESULT hr = S_OK;

	PROPVARIANT enable;
	enable.vt = VT_BOOL;

	if (state) enable.boolVal = -1;
	else enable.boolVal = 0;

	if (g_pFramework)
	{
		hr = g_pFramework->SetUICommandProperty(ID_CMD_UNDO, UI_PKEY_Enabled, enable);
	}

	return hr;
}

HRESULT ChangeStateFillColorPicker(bool state)
{
	HRESULT hr = S_OK;

	PROPVARIANT enable;
	enable.vt = VT_BOOL;

	if (state) enable.boolVal = -1;
	else enable.boolVal = 0;

	if (g_pFramework)
	{
		hr = g_pFramework->SetUICommandProperty(cmdColorFillPicker, UI_PKEY_Enabled, enable);
	}

	return hr;
}

HRESULT ChangeToggleBtnValue(UINT32 id, bool state)
{
	HRESULT hr = S_OK;

	PROPVARIANT enable;
	enable.vt = VT_BOOL;

	if (state) enable.boolVal = -1;
	else enable.boolVal = 0;

	if (g_pFramework)
	{
		hr = g_pFramework->SetUICommandProperty(id, UI_PKEY_BooleanValue, enable);
	}

	return hr;
}