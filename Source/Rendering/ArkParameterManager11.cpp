//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//ArkParameterManager11.cpp
//--------------------------------------------------------------------------------
#include "Pch.h"
#include "ArkParameterManager11.h"
#include "ArkVectorParameter11.h"
#include "ArkMatrixParameter11.h"
#include "ArkMatrixArrayParameter11.h"
#include "ArkParameterManager11.h"
#include "ArkLog.h"
//--------------------------------------------------------------------------------
using namespace Arkeng;
using namespace DirectX;
//--------------------------------------------------------------------------------
std::map<std::wstring,std::shared_ptr<ArkRenderParameter11>> ArkParameterManager11::m_Parameters;
//--------------------------------------------------------------------------------
ArkParameterManager11::ArkParameterManager11(unsigned int ID)
{
	m_ID = ID;
	m_pWorldMatrix = GetMatrixParameterRef(std::wstring(L"gWorld"));
	m_pViewMatrix  = GetMatrixParameterRef(std::wstring(L"gView"));
	m_pProjMatrix  = GetMatrixParameterRef(std::wstring(L"gProj"));

	m_pWorldViewMatrix     = GetMatrixParameterRef(std::wstring(L"WorldViewMatrix"));
	m_pWorldProjMatrix     = GetMatrixParameterRef(std::wstring(L"WorldProjMatrix"));
	m_pViewProjMatrix      = GetMatrixParameterRef(std::wstring(L"ViewProjMatrix"));
	m_pWorldViewProjMatrix = GetMatrixParameterRef(std::wstring(L"WorldViewProjMatrix"));
}
//--------------------------------------------------------------------------------
ArkParameterManager11::~ArkParameterManager11()
{
	std::map< std::wstring,std::shared_ptr<ArkRenderParameter11> >::iterator iter = m_Parameters.begin();
	while(iter != m_Parameters.end()) {
		(iter->second).reset();
		iter++;
	}

	m_Parameters.clear();
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetConstantBufferParameter(const std::wstring& name,ResourcePtr resource)
{
	std::shared_ptr<ArkRenderParameter11> pParameter = m_Parameters[name];

	// Only create the new parameter if it hasn't already been registered
	if(pParameter == 0)
	{
		pParameter = std::make_shared<ArkConstantBufferParameter11>();
		pParameter->SetName(name);
		m_Parameters[name] = std::dynamic_pointer_cast<ArkRenderParameter11>(pParameter);

		// Initialize the parameter with the current data in all slots
		pParameter->InitializeParameterData(reinterpret_cast<void*>(&resource->m_iResource));
	}
	else
	{
		if(pParameter->GetParameterType() == CBUFFER)
			pParameter->SetParameterData(reinterpret_cast<void*>(&resource->m_iResource),GetID());
		else
			ArkLog::Get(LogType::Renderer).Output(L"Constant buffer parameter name collision!");
	}
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetVectorParameter(const std::wstring& name,DirectX::XMVECTOR* pV)
{
	std::shared_ptr<ArkRenderParameter11> pParameter = m_Parameters[name];

	if(pParameter == 0)
	{
		pParameter = std::make_shared<ArkVectorParameter11>();
		pParameter->SetName(name);
		m_Parameters[name] = std::dynamic_pointer_cast<ArkRenderParameter11>(pParameter);

		pParameter->InitializeParameterData(reinterpret_cast<void*>(pV));
	}
	else
	{
		if(pParameter->GetParameterType() == ArkParamType::VECTOR)
		{
			pParameter->SetParameterData(reinterpret_cast<void*>(pV),GetID());
		}
		else
		{
			ArkLog::Get(LogType::Renderer).Output(L"VECTOR parameter name error!");
		}
	}

}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetMatrixParameter(const std::wstring& name,DirectX::XMMATRIX* pM)
{
	std::shared_ptr<ArkRenderParameter11> pParameter = m_Parameters[name];

	if(pParameter == 0)
	{
		pParameter = std::make_shared<ArkMatrixParameter11>();
		pParameter->SetName(name);
		m_Parameters[name] = std::dynamic_pointer_cast<ArkRenderParameter11>(pParameter);

		pParameter->InitializeParameterData(reinterpret_cast<void*>(pM));
	}
	else
	{
		if(pParameter->GetParameterType() == ArkParamType::MATRIX)
		{
			pParameter->SetParameterData(reinterpret_cast<void*>(pM),GetID());
		}
		else
		{
			ArkLog::Get(LogType::Renderer).Output(L"MATRIX parameter name error!");
		}
	}
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetMatrixArrayParameter(const std::wstring& name,DirectX::XMFLOAT4X4* pmA)
{
	std::shared_ptr<ArkRenderParameter11> pParameter = m_Parameters[name];

	if(pParameter == 0)
	{
		pParameter = std::make_shared<ArkMatrixArrayParameter11>();
		pParameter->SetName(name);
		m_Parameters[name] = std::dynamic_pointer_cast<ArkRenderParameter11>(pParameter);

		pParameter->InitializeParameterData(reinterpret_cast<void*>(pmA));
	}
	else
	{
		if(pParameter->GetParameterType() == ArkParamType::MATRIX_ARRAY)
		{
			pParameter->SetParameterData(reinterpret_cast<void*>(pmA),GetID());
		}
		else
		{
			ArkLog::Get(LogType::Renderer).Output(L"MATRIX_ARRAY parameter name error!");
		}
	}
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetConstantBufferParameter(std::shared_ptr<ArkRenderParameter11> pParameter,ResourcePtr resource)
{
	if(pParameter->GetParameterType() == CBUFFER)
		pParameter->SetParameterData(reinterpret_cast<void*>(&resource->m_iResource),GetID());
	else
		ArkLog::Get(LogType::Renderer).Write(L"Constant buffer parameter name collision!");
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetVectorParameter(std::shared_ptr<ArkRenderParameter11> pP,DirectX::XMVECTOR* pV)
{
	if(pP->GetParameterType() == ArkParamType::VECTOR)
		pP->SetParameterData(reinterpret_cast<void*>(pV),GetID());
	else
		ArkLog::Get(LogType::Renderer).Output(L"VECTOR parameter name error!");
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetMatrixParameter(std::shared_ptr<ArkRenderParameter11> pP,DirectX::XMMATRIX* pV)
{
	if(pP->GetParameterType() == ArkParamType::MATRIX)
		pP->SetParameterData(reinterpret_cast<void*>(pV),GetID());
	else
		ArkLog::Get(LogType::Renderer).Output(L"MATRIX parameter name error!");
}
//--------------------------------------------------------------------------------

void ArkParameterManager11::SetMatrixArrayParameter(std::shared_ptr<ArkRenderParameter11> pP,DirectX::XMFLOAT4X4* pV)
{
	if(pP->GetParameterType() == ArkParamType::MATRIX_ARRAY)
		pP->SetParameterData(reinterpret_cast<void*>(pV),GetID());
	else
		ArkLog::Get(LogType::Renderer).Output(L"MATRIX_ARRAY parameter name error!");
}
//--------------------------------------------------------------------------------
DirectX::XMVECTOR ArkParameterManager11::GetVectorParameter(const std::wstring& name)
{
	XMVECTOR pV;
	pV = XMVectorZero();

	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	if(pParam != 0)
	{
		if(pParam->GetParameterType() == ArkParamType::VECTOR)
			pV = std::dynamic_pointer_cast<ArkVectorParameter11>(pParam)->GetVector();
	}
	else
	{
		pParam = std::make_shared<ArkVectorParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}
	return pV;
}
//--------------------------------------------------------------------------------
std::shared_ptr<ArkConstantBufferParameter11> ArkParameterManager11::GetConstantBufferParameterRef(const std::wstring& name)
{
	// Check for the existence of this parameter.  This search includes any
	// parent parameter managers if the parameter doesn't exist in this one.

	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	// If the parameter is not found, create a new default one.  This goes 
	// into the bottom level manager.

	if(pParam == 0)
	{
		pParam = std::make_shared<ArkConstantBufferParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}

	return(std::dynamic_pointer_cast<ArkConstantBufferParameter11>(pParam));
}
//--------------------------------------------------------------------------------
int ArkParameterManager11::GetConstantBufferParameter(const std::wstring& name)
{
	int result;
	result = -1;

	// Check for the existence of this parameter.  This search includes any
	// parent parameter managers if the parameter doesn't exist in this one.

	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	// If the parameter is not found, create a new default one.  This goes 
	// into the bottom level manager.

	if(pParam != 0)
	{
		if(pParam->GetParameterType() == CBUFFER)
			result = std::dynamic_pointer_cast<ArkConstantBufferParameter11>(pParam)->GetIndex(1);
	}
	else
	{
		pParam = std::make_shared<ArkConstantBufferParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}

	return(result);
}
DirectX::XMMATRIX ArkParameterManager11::GetMatrixParameter(const std::wstring& name)
{
	XMMATRIX pM;
	pM = XMMatrixIdentity();

	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	if(pParam != 0)
	{
		if(pParam->GetParameterType() == ArkParamType::MATRIX)
			pM = std::dynamic_pointer_cast<ArkMatrixParameter11>(pParam)->GetMatrix();
	}
	else
	{
		pParam = std::make_shared<ArkVectorParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}
	return pM;
}
//--------------------------------------------------------------------------------
DirectX::XMFLOAT4X4 ArkParameterManager11::GetMatrixArrayParameter(const std::wstring& name)
{
	XMFLOAT4X4 pmA;
	XMStoreFloat4x4(&pmA,XMMatrixIdentity());

	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	if(pParam != 0)
	{
		if(pParam->GetParameterType() == ArkParamType::MATRIX_ARRAY)
			pmA = std::dynamic_pointer_cast<ArkMatrixArrayParameter11>(pParam)->GetMatrixArray();
	}
	else
	{
		pParam = std::make_shared<ArkVectorParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}
	return pmA;
}
//--------------------------------------------------------------------------------
DirectX::XMVECTOR ArkParameterManager11::GetVectorParameter(std::shared_ptr<ArkRenderParameter11> pP)
{
	assert(pP != 0);

	XMVECTOR result;
	result = XMVectorZero();

	if(pP->GetParameterType() == ArkParamType::VECTOR)
	{
		result = std::dynamic_pointer_cast<ArkVectorParameter11>(pP)->GetVector();
	}
	return result;
}
//--------------------------------------------------------------------------------
DirectX::XMMATRIX ArkParameterManager11::GetMatrixParameter(std::shared_ptr<ArkRenderParameter11> pP)
{
	XMMATRIX pM;
	pM = XMMatrixIdentity();

	if(pP->GetParameterType() == ArkParamType::MATRIX)
	{
		pM = std::dynamic_pointer_cast<ArkMatrixParameter11>(pP)->GetMatrix( GetID() );
	}
	return pM;
}
//--------------------------------------------------------------------------------
DirectX::XMFLOAT4X4 ArkParameterManager11::GetMatrixArrayParameter(std::shared_ptr<ArkRenderParameter11> pP)
{
	XMFLOAT4X4 pmA;
	XMStoreFloat4x4(&pmA,XMMatrixIdentity());

	if(pP->GetParameterType() == ArkParamType::MATRIX_ARRAY)
		pmA = std::dynamic_pointer_cast<ArkMatrixArrayParameter11>(pP)->GetMatrixArray();
	return pmA;
}
int ArkParameterManager11::GetConstantBufferParameter(std::shared_ptr<ArkRenderParameter11> pParameter)
{
	assert(pParameter != 0);

	int result = -1;

	// If the parameter is not found, create a new default one.  This goes 
	// into the bottom level manager.

	if(pParameter->GetParameterType() == CBUFFER)
		result = std::dynamic_pointer_cast<ArkConstantBufferParameter11>(pParameter)->GetIndex(GetID());

	return(result);
}
//--------------------------------------------------------------------------------
std::shared_ptr<ArkVectorParameter11> ArkParameterManager11::GetVectorParameterRef(const std::wstring& name)
{
	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	if(pParam == 0)
	{
		pParam = std::make_shared<ArkVectorParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}

	return (std::dynamic_pointer_cast<ArkVectorParameter11>(pParam));
}
//--------------------------------------------------------------------------------
std::shared_ptr<ArkMatrixParameter11> ArkParameterManager11::GetMatrixParameterRef(const std::wstring& name)
{
	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	if(pParam == 0)
	{
		pParam = std::make_shared<ArkMatrixParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}

	return (std::dynamic_pointer_cast<ArkMatrixParameter11>(pParam));
}
//--------------------------------------------------------------------------------
std::shared_ptr<ArkMatrixArrayParameter11> ArkParameterManager11::GetMatrixArrayParameterRef(const std::wstring& name)
{
	std::shared_ptr<ArkRenderParameter11> pParam = GetParameterRef(name);

	if(pParam == 0)
	{
		pParam = std::make_shared<ArkMatrixArrayParameter11>();
		pParam->SetName(name);
		m_Parameters[name] = pParam;
	}

	return (std::dynamic_pointer_cast<ArkMatrixArrayParameter11>(pParam));
}
//--------------------------------------------------------------------------------
std::shared_ptr<ArkRenderParameter11> ArkParameterManager11::GetParameterRef(const std::wstring& name)
{
	return m_Parameters[name];
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetWorldMatrix(DirectX::XMMATRIX* w)
{
	SetMatrixParameter(m_pWorldMatrix,w);

	XMMATRIX WorldMatrix = GetMatrixParameter(m_pWorldMatrix);
	XMMATRIX ViewMatrix  = GetMatrixParameter(m_pViewMatrix);
	XMMATRIX ProjMatrix  = GetMatrixParameter(m_pProjMatrix);

	XMMATRIX WorldViewMatrix = WorldMatrix * ViewMatrix;
	XMMATRIX ViewProjMatrix = ViewMatrix * ProjMatrix;
	XMMATRIX WorldProjMatrix = WorldMatrix * ProjMatrix;
	XMMATRIX WorldViewProjMatrix = WorldMatrix * ViewProjMatrix;

	SetMatrixParameter(m_pWorldViewMatrix,&WorldViewMatrix);
	SetMatrixParameter(m_pViewProjMatrix,&ViewProjMatrix);
	SetMatrixParameter(m_pWorldProjMatrix,&WorldProjMatrix);
	SetMatrixParameter(m_pWorldViewProjMatrix,&WorldViewProjMatrix);
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetViewMatrix(DirectX::XMMATRIX* w)
{
	SetMatrixParameter(m_pViewMatrix,w);

	XMMATRIX WorldMatrix = GetMatrixParameter(m_pWorldMatrix);
	XMMATRIX ViewMatrix  = GetMatrixParameter(m_pViewMatrix);
	XMMATRIX ProjMatrix  = GetMatrixParameter(m_pProjMatrix);

	XMMATRIX WorldViewMatrix = WorldMatrix * ViewMatrix;
	XMMATRIX ViewProjMatrix = ViewMatrix * ProjMatrix;
	XMMATRIX WorldProjMatrix = WorldMatrix * ProjMatrix;
	XMMATRIX WorldViewProjMatrix = WorldMatrix * ViewProjMatrix;

	SetMatrixParameter(m_pWorldViewMatrix,&WorldViewMatrix);
	SetMatrixParameter(m_pViewProjMatrix,&ViewProjMatrix);
	SetMatrixParameter(m_pWorldProjMatrix,&WorldProjMatrix);
	SetMatrixParameter(m_pWorldViewProjMatrix,&WorldViewProjMatrix);
}
//--------------------------------------------------------------------------------
void ArkParameterManager11::SetProjectionMatrix(DirectX::XMMATRIX* w)
{
	SetMatrixParameter(m_pProjMatrix,w);

	XMMATRIX WorldMatrix = GetMatrixParameter(m_pWorldMatrix);
	XMMATRIX ViewMatrix  = GetMatrixParameter(m_pViewMatrix);
	XMMATRIX ProjMatrix  = GetMatrixParameter(m_pProjMatrix);

	XMMATRIX WorldViewMatrix = WorldMatrix * ViewMatrix;
	XMMATRIX ViewProjMatrix = ViewMatrix * ProjMatrix;
	XMMATRIX WorldProjMatrix = WorldMatrix * ProjMatrix;
	XMMATRIX WorldViewProjMatrix = WorldMatrix * ViewProjMatrix;

	SetMatrixParameter(m_pWorldViewMatrix,&WorldViewMatrix);
	SetMatrixParameter(m_pViewProjMatrix,&ViewProjMatrix);
	SetMatrixParameter(m_pWorldProjMatrix,&WorldProjMatrix);
	SetMatrixParameter(m_pWorldViewProjMatrix,&WorldViewProjMatrix);
}
//--------------------------------------------------------------------------------
unsigned int ArkParameterManager11::GetID()
{
	return m_ID;
}