//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//EWindow.h
//--------------------------------------------------------------------------------
#include "Pch.h"
#include "EWindow.h"
//--------------------------------------------------------------------------------
using namespace Arkeng;
//--------------------------------------------------------------------------------
EWindow::EWindow( HWND hwnd, unsigned int wParam,long lParam )
{
	m_pHwnd = hwnd;
	m_iWParam = wParam;
	m_iLParam = lParam;
}
//--------------------------------------------------------------------------------
EWindow::~EWindow()
{
}
//--------------------------------------------------------------------------------
HWND EWindow::GetWindowHandle()
{
	return m_pHwnd;
}
//--------------------------------------------------------------------------------
unsigned int EWindow::GetWParam()
{
	return m_iWParam;
}
//--------------------------------------------------------------------------------
unsigned int EWindow::GetLParam()
{
	return m_iLParam;
}
//--------------------------------------------------------------------------------