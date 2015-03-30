//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//Camera.cpp
//--------------------------------------------------------------------------------
#include "Pch.h"
#include "Camera.h"
#include "Scene.h"
//--------------------------------------------------------------------------------
using namespace Arkeng;
//--------------------------------------------------------------------------------
Camera::Camera() 
	: m_pCameraView( nullptr ),
	m_pScene(nullptr),
	m_fNear( 0.1f ),
	m_fFar( 100.0f ),
	m_fAspect( 1280.0f / 800.0f ),
	m_fFov( static_cast<float>( 3.14f ) / 4.0f ),
	m_fWidth( 1280.0f ),
	m_fHeight( 800.0f ),
	m_ProjMatrix( DirectX::XMMatrixIdentity() ),
	m_pSpatialController( nullptr )
{
	m_pSpatialController = new ArkSpatialController<ArkNode3D>();
	GetNode()->Controllers.Attach( m_pSpatialController );

	m_pViewPositionWriter = Parameters.SetVectorParameter( L"ViewPosition", XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f ) );
}
//--------------------------------------------------------------------------------
Camera::~Camera()
{
	Safe_Delete( m_pCameraView );
}
//--------------------------------------------------------------------------------
void Camera::RenderFrame( ArkRenderer11* pRenderer )
{
	if( m_pCameraView )
	{
		if( m_pScene )
		{
			m_pCameraView->SetScene( m_pScene );
		}

		//

		//// Set the view position in the parameter system, for use by any of the
		//// views being used in this frame.

		XMVECTOR p = GetNode()->Transform.Position() + GetBody()->Transform.Position();
		XMFLOAT3 pp;

		m_pViewPositionWriter->SetValue( p );

		Parameters.InitRenderParams();

		//// Use the pre-draw method to queue any needed render views in the scene.
		//// This is followed by rendering all of the views to generate the current
		//// frame.

		m_pCameraView->QueuePreTasks( pRenderer );
		pRenderer->ProcessTaskQueue();

	}
}
//--------------------------------------------------------------------------------
bool Camera::HandleEvent( EventPtr pEvent )
{
	eEvent e = pEvent->GetEventType();

	return false;
}
//--------------------------------------------------------------------------------
std::wstring Camera::GetName()
{
	return L"Camera";
}
//--------------------------------------------------------------------------------
void Camera::SetCameraView( RenderTask* pView )
{
	m_pCameraView = pView;
	m_pCameraView->SetEntity( m_pBody );
}
//--------------------------------------------------------------------------------
RenderTask* Camera::GetCameraView()
{
	return m_pCameraView;
}
//--------------------------------------------------------------------------------
void Camera::SetScene( Scene* pScene )
{
	m_pScene = pScene;
}
//--------------------------------------------------------------------------------
void Camera::ApplyProjectionParams()
{
	m_ProjMatrix = DirectX::XMMatrixPerspectiveLH( m_fFov, m_fAspect, m_fNear, m_fFar );

	if ( m_pCameraView )
		m_pCameraView->SetProjMatrix( m_ProjMatrix );	
}
//--------------------------------------------------------------------------------
void Camera::ApplyOrthographicParams()
{
	//
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
void Camera::SetProjectionParams( float zn, float zf, float aspect, float fov )
{
	m_fNear = zn;
	m_fFar = zf;
	m_fAspect = aspect;
	m_fFov = fov;

	ApplyProjectionParams();
}
//--------------------------------------------------------------------------------
void Camera::SetOrthographicParams( float zn, float zf, float width, float height )
{
	m_fNear = zn;
	m_fFar = zf;
	m_fWidth = width;
	m_fHeight = height;

	ApplyOrthographicParams();
}
//--------------------------------------------------------------------------------
void Camera::SetClipPlanes( float zn, float zf )
{
	m_fNear = zn;
	m_fFar = zf;

	ApplyProjectionParams();
}
//--------------------------------------------------------------------------------
void Camera::SetAspectRatio( float aspect )
{
	m_fAspect = aspect;

	ApplyProjectionParams();
}
//--------------------------------------------------------------------------------
void Camera::SetFieldOfView( float fov )
{
	m_fFov = fov;

	ApplyProjectionParams();
}
//--------------------------------------------------------------------------------
float Camera::GetNearClipPlane()
{
	return( m_fNear );
}
//--------------------------------------------------------------------------------
float Camera::GetFarClipPlane()
{
	return( m_fFar );
}
//--------------------------------------------------------------------------------
float Camera::GetAspectRatio()
{
	return( m_fAspect );
}
//--------------------------------------------------------------------------------
float Camera::GetFieldOfView()
{
	return( m_fFov );
}
//--------------------------------------------------------------------------------
ArkSpatialController<ArkNode3D>& Camera::Spatial()
{
	return( *m_pSpatialController );
}
//--------------------------------------------------------------------------------