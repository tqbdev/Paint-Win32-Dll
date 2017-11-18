// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "stdafx.h"
#include <Propvarutil.h>
#pragma comment(lib, "Propsys.lib")
#include <UIRibbon.h>

#include "CommandHandler.h"
#include "RibbonIDs.h"
#include "RibbonFramework.h"

#include "resource.h" // For ID of Main Window

COLORREF gColor = RGB(0,0,0);
short gDashStyle = 0;
float gPenWidth = 1.0F;


static UINT32 lastIDShape = ID_CMD_LINE;
static UINT32 lastIDStyle = ID_CMD_STYLE_SOLID;
static UINT32 lastIDWidth = ID_CMD_SIZE_1;

static bool fCheck[3] = { true };

// Static method to create an instance of the object.
HRESULT CCommandHandler::CreateInstance(IUICommandHandler **ppCommandHandler)
{
	if (!ppCommandHandler)
	{
		return E_POINTER;
	}

	*ppCommandHandler = NULL;

	HRESULT hr = S_OK;

	CCommandHandler* pCommandHandler = new CCommandHandler();

	if (pCommandHandler != NULL)
	{
		*ppCommandHandler = static_cast<IUICommandHandler *>(pCommandHandler);
	}
	else
	{
		hr = E_OUTOFMEMORY;
	}
	
	return hr;
}

// IUnknown method implementations.
STDMETHODIMP_(ULONG) CCommandHandler::AddRef()
{
	return InterlockedIncrement(&m_cRef);
}

STDMETHODIMP_(ULONG) CCommandHandler::Release()
{
	LONG cRef = InterlockedDecrement(&m_cRef);
	if (cRef == 0)
	{
		delete this;
	}

	return cRef;
}

STDMETHODIMP CCommandHandler::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == __uuidof(IUnknown))
	{
		*ppv = static_cast<IUnknown*>(this);
	}
	else if (iid == __uuidof(IUICommandHandler))
	{
		*ppv = static_cast<IUICommandHandler*>(this);
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}

	AddRef();
	return S_OK;
}

//
//  FUNCTION: UpdateProperty()
//
//  PURPOSE: Called by the Ribbon framework when a command property (PKEY) needs to be updated.
//
//  COMMENTS:
//
//    This function is used to provide new command property values, such as labels, icons, or
//    tooltip information, when requested by the Ribbon framework.  
//    
//    In this SimpleRibbon sample, the method is not implemented.  
//
STDMETHODIMP CCommandHandler::UpdateProperty(
	UINT nCmdID,
	REFPROPERTYKEY key,
	const PROPVARIANT* ppropvarCurrentValue,
	PROPVARIANT* ppropvarNewValue)
{
	UNREFERENCED_PARAMETER(nCmdID);
	UNREFERENCED_PARAMETER(key);
	UNREFERENCED_PARAMETER(ppropvarCurrentValue);
	UNREFERENCED_PARAMETER(ppropvarNewValue);

	if (/*nCmdID == ID_CMD_STYLE && */lastIDStyle == ID_CMD_STYLE_SOLID) ChangeToggleBtnValue(ID_CMD_STYLE_SOLID, true);
	if (/*nCmdID == ID_CMD_WIDTH && */lastIDWidth == ID_CMD_SIZE_1)ChangeToggleBtnValue(ID_CMD_SIZE_1, true);
	return E_NOTIMPL;
}

//
//  FUNCTION: Execute()
//
//  PURPOSE: Called by the Ribbon framework when a command is executed by the user.  For example, when
//           a button is pressed.
//
STDMETHODIMP CCommandHandler::Execute(
	UINT nCmdID,
	UI_EXECUTIONVERB verb,
	const PROPERTYKEY* key,
	const PROPVARIANT* ppropvarValue,
	IUISimplePropertySet* pCommandExecutionProperties)
{
	//UNREFERENCED_PARAMETER(pCommandExecutionProperties);
	//UNREFERENCED_PARAMETER(ppropvarValue);
	//UNREFERENCED_PARAMETER(key);
	//UNREFERENCED_PARAMETER(verb);

	HRESULT hr = E_NOTIMPL;
	if (key && *key == UI_PKEY_ColorType)
	{
		UI_SWATCHCOLORTYPE uType =
			(UI_SWATCHCOLORTYPE)PropVariantToUInt32WithDefault(
				*ppropvarValue,
				UI_SWATCHCOLORTYPE_NOCOLOR);

		COLORREF color;
		switch (uType)
		{
		case UI_SWATCHCOLORTYPE_RGB:
			PROPVARIANT var;
			pCommandExecutionProperties->GetValue(UI_PKEY_Color, &var);
			color = PropVariantToUInt32WithDefault(var, 0);
			break;
		case UI_SWATCHCOLORTYPE_AUTOMATIC:
			color = COLOR_WINDOWTEXT;
			break;
		case UI_SWATCHCOLORTYPE_NOCOLOR:
			//color = MSONoFill;
			break;
		}

		// do with your color what you will...
		gColor = color;
		hr = S_OK;
	}
	
	HWND hwnd = GetForegroundWindow();

	switch (nCmdID)
	{
	case ID_CMD_EXIT:
		SendMessage(hwnd, WM_CLOSE, 0, 0);
		break;
	case ID_CMD_NEW:
		SendMessage(hwnd, WM_COMMAND, ID_FILE_NEW, 0);
		break;
	case ID_CMD_SAVE:
		SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
		break;
	case ID_CMD_OPEN:
		SendMessage(hwnd, WM_COMMAND, ID_FILE_OPEN, 0);
		break;
	case ID_CMD_HELP:
		SendMessage(hwnd, WM_COMMAND, IDM_ABOUT, 0);
		break;
	case ID_CMD_REDO:
		SendMessage(hwnd, WM_COMMAND, ID_EDIT_REDO, 0);
		break;
	case ID_CMD_UNDO:
		SendMessage(hwnd, WM_COMMAND, ID_EDIT_UNDO, 0);
		break;

	case ID_CMD_LINE:
	case ID_CMD_RECTANGLE:
	case ID_CMD_ELLIPSE:
		if (lastIDShape == nCmdID) ChangeToggleBtnValue(lastIDShape, true);
		else ChangeToggleBtnValue(lastIDShape, false);
		lastIDShape = nCmdID;
		SendMessage(hwnd, WM_COMMAND, ID_SHAPE_LINE + nCmdID - ID_CMD_LINE, 0);
		break;

	case ID_CMD_STYLE_SOLID:
	case ID_CMD_STYLE_DASH:
	case ID_CMD_STYLE_DOT:
	case ID_CMD_STYLE_DASHDOT:
	case ID_CMD_STYLE_DASHDOTDOT:
		if (lastIDStyle == nCmdID) ChangeToggleBtnValue(lastIDStyle, true);
		else ChangeToggleBtnValue(lastIDStyle, false);
		lastIDStyle = nCmdID;
		gDashStyle = nCmdID - ID_CMD_STYLE_SOLID;
		break;

	case ID_CMD_SIZE_1:
	case ID_CMD_SIZE_2:
	case ID_CMD_SIZE_3:
		if (lastIDWidth == nCmdID) ChangeToggleBtnValue(lastIDWidth, true);
		else ChangeToggleBtnValue(lastIDWidth, false);
		lastIDWidth = nCmdID;
		gPenWidth = nCmdID - ID_CMD_SIZE_1 + 1.0F;
		break;
	case ID_CMD_SIZE_5:
		if (lastIDWidth == nCmdID) ChangeToggleBtnValue(lastIDWidth, true);
		else ChangeToggleBtnValue(lastIDWidth, false);
		lastIDWidth = nCmdID;
		gPenWidth = 5.0F;
		break;

	case ID_CUSTOM_QAT:
		break;
	default:
		break;
	}

	return S_OK;
}