//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//ArkPlane.h
//--------------------------------------------------------------------------------
#include "Pch.h"
#include "ArkPlane.h"
//--------------------------------------------------------------------------------
using namespace Arkeng;
//--------------------------------------------------------------------------------
ArkPlane::ArkPlane()
{
	m_fComponents[0] = 0.0f;
	m_fComponents[1] = 0.0f;
	m_fComponents[2] = 0.0f;
	m_fComponents[3] = 0.0f;
}
//--------------------------------------------------------------------------------
ArkPlane::ArkPlane(float a, float b, float c, float d)
{
	m_fComponents[0] = a;
	m_fComponents[1] = b;
	m_fComponents[2] = c;
	m_fComponents[3] = d;
}
//--------------------------------------------------------------------------------
ArkPlane::ArkPlane( DirectX::XMVECTOR Plane )
{
	DirectX::XMFLOAT4 P;
	DirectX::XMStoreFloat4( &P,Plane );

	m_fComponents[0] = P.x;
	m_fComponents[1] = P.y;
	m_fComponents[2] = P.z;
	m_fComponents[3] = P.w;

}
//--------------------------------------------------------------------------------
ArkPlane::~ArkPlane()
{
}
//--------------------------------------------------------------------------------
void ArkPlane::Normalize()
{
	float fMagnitude = sqrt(A*A + B*B + C*C);

	for (int i = 0; i < 4; i++)
	{
        m_fComponents[i] /= fMagnitude;
	}
}
//--------------------------------------------------------------------------------
float ArkPlane::DistanceToPoint( const DirectX::XMVECTOR& pt ) const
{
	DirectX::XMFLOAT3 d;
	DirectX::XMStoreFloat3( &d,pt );
	return (A * d.x +
			B * d.y +
			C * d.z +
			D);
}
//--------------------------------------------------------------------------------
float ArkPlane::a() const
{
	return(A);
}
//--------------------------------------------------------------------------------
float& ArkPlane::a()
{
	return(A);
}
//--------------------------------------------------------------------------------
float ArkPlane::b() const
{
	return(B);
}
//--------------------------------------------------------------------------------
float& ArkPlane::b()
{
	return(B);
}
//--------------------------------------------------------------------------------
float ArkPlane::c() const
{
	return(C);
}
//--------------------------------------------------------------------------------
float& ArkPlane::c()
{
	return(C);
}
//--------------------------------------------------------------------------------
float ArkPlane::d() const
{
	return(D);
}
//--------------------------------------------------------------------------------
float& ArkPlane::d()
{
	return(D);
}
//--------------------------------------------------------------------------------
eEShape ArkPlane::GetShapeType( ) const
{
	return( PLANE );
}
//--------------------------------------------------------------------------------