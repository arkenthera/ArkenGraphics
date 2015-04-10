//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//PipelineManager.h
//--------------------------------------------------------------------------------
#ifndef __PipelineManager_h__
#define __PipelineManager_h__
//--------------------------------------------------------------------------------
#include "ArkVertexShaderStage11.h"
#include "ArkPixelShaderStage11.h"
#include "Dx11ResourceProxy.h"
#include "Dx11Resource.h"
#include "DxOutputMergerStage.h"
#include "DxRasterizerStage.h"
#include "DxIAStage.h"
#include "ArkRenderEffect11.h"
#include "ArkGeometry11.h"
//--------------------------------------------------------------------------------
namespace Arkeng
{
	class ArkCommandList11;
	typedef Microsoft::WRL::ComPtr<ID3DUserDefinedAnnotation> UserDefinedAnnotationComPtr;

	class PipelineManager
	{
	public:
		PipelineManager();
		~PipelineManager();

		void SetDeviceContext(DeviceContextComPtr Context,D3D_FEATURE_LEVEL FeatureLevel);

		void BindConstantBufferParameter( ShaderType type,std::shared_ptr<ArkRenderParameter11> pParam, UINT slot,IParameterManager* pParamManager );
		void BindSamplerStateParameter( ShaderType type,std::shared_ptr<ArkRenderParameter11> pParam, UINT slot,IParameterManager* pParamManager );
		void BindShaderResourceParameter( ShaderType type,std::shared_ptr<ArkRenderParameter11> pParam, UINT slot,IParameterManager* pParamManager );

		void BindShader( ShaderType type,int ID, IParameterManager* pParamManager );

		void ClearRenderTargets();
		void ApplyRenderTargets();

		void ApplyPipelineResources();
		void ClearPipelineResources();

		void ApplyInputResources();
		void ClearInputResources();

		void ClearPipelineState();

		void ClearBuffers( float color[],float depth,UINT stencil = 0 );
		void ClearPipelineSRVs();

		void Draw( ArkRenderEffect11& effect, GeometryPtr chunk, IParameterManager* pParamManager );
		void Draw( ArkRenderEffect11& effect, ResourcePtr vb, ResourcePtr ib,
					int inputLayout, D3D11_PRIMITIVE_TOPOLOGY primType,
					UINT vertexStride, UINT numIndices, IParameterManager* pParamManager);
        void DrawNonIndexed( ArkRenderEffect11& effect, ResourcePtr vb, int inputLayout, 
                    D3D11_PRIMITIVE_TOPOLOGY primType, UINT vertexStride, UINT vertexCount, 
                    UINT startVertexLocation, IParameterManager* pParamManager);
		void DrawInstanced( ArkRenderEffect11& effect, GeometryPtr chunk,
							ResourcePtr instanceData, UINT instanceDataStride,
							UINT numInstances, IParameterManager* pParamManager );
		void DrawInstanced( ArkRenderEffect11& effect, ResourcePtr vb,
							D3D11_PRIMITIVE_TOPOLOGY primType, ResourcePtr ib,
							int inputLayout, UINT vertexStride, UINT numIndices,
							ResourcePtr instanceData, UINT instanceDataStride,
							UINT numInstances, IParameterManager* pParamManager );

		void Draw( UINT VertexCount, UINT StartVertex );
		void DrawIndexed( UINT IndexCount, UINT StartIndex, int VertexOffset ); 
		void DrawIndexedInstanced( UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation );
		void DrawInstancedIndirect( ID3D11Buffer* argsBuffer, UINT offset );

		D3D11_MAPPED_SUBRESOURCE	MapResource( int index, UINT subresource, D3D11_MAP actions, UINT flags );
		void						UnMapResource( int index, UINT subresource );

		D3D11_MAPPED_SUBRESOURCE	MapResource( ResourcePtr pGlyphResource, UINT subresource, D3D11_MAP actions, UINT flags );
		void						UnMapResource( ResourcePtr pGlyphResource, UINT subresource );

		D3D11_MAPPED_SUBRESOURCE MapResource( Dx11Resource* pArkResource, UINT subresource, D3D11_MAP actions, UINT flags );
		void UnMapResource(Dx11Resource* pArkResource,UINT subresource);

		void GenerateCommandList( ArkCommandList11* pList );
		void ExecuteCommandList( ArkCommandList11* pList );

		void BeginEvent( std::wstring& name );
		void EndEvent();
		void SetMarker( std::wstring& name );

		D3D_FEATURE_LEVEL						m_FeatureLevel;
		UserDefinedAnnotationComPtr				m_pAnnotation;

		DeviceContextComPtr			            m_pContext;

		ArkVertexShaderStage11					VertexShaderStage;
		ArkPixelShaderStage11					PixelShaderStage;

		ArkShaderStage11*						ShaderStages[2];

		DxOutputMergerStage						OutputMergerStage;
		DxRasterizerStage						RasterizerStage;
		DxIAStage								InputAssemblerStage;
	};
};
//--------------------------------------------------------------------------------
#endif