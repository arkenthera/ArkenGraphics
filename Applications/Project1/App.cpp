//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//App.cpp
//--------------------------------------------------------------------------------
#include "App.h"
#include "EventManager.h"
#include "EKeyDown.h"
//--------------------------------------------------------------------------------
using namespace Arkeng;
//--------------------------------------------------------------------------------
App AppInstance;
//--------------------------------------------------------------------------------
App::App()
{

}
//--------------------------------------------------------------------------------
bool App::ConfigureEngineComponents()
{
	if(!ConfigureRenderingEngineComponents(800,480,D3D_FEATURE_LEVEL_11_0)) {
		return(false);
	}

	if(!ConfigureRenderingSetup()) {
		return(false);
	}

	return true;
}
//--------------------------------------------------------------------------------
void App::ShutdownEngineComponents()
{
	ShutdownRenderingSetup();
	ShutdownRenderingEngineComponents();
}
//--------------------------------------------------------------------------------
void App::Initialize()
{

}
//--------------------------------------------------------------------------------
void App::Update()
{
}
//--------------------------------------------------------------------------------
void App::Shutdown()
{
}
//--------------------------------------------------------------------------------
bool App::HandleEvent(EventPtr e)
{
	return Application::HandleEvent( e );
}
//--------------------------------------------------------------------------------
std::wstring App::GetName()
{
	return L"Basic App";
}
//--------------------------------------------------------------------------------