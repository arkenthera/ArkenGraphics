//--------------------------------------------------------------------------------
//This is a file from Arkengine
//
//
//Copyright (c) Alperen Gezer.All rights reserved.
//
//ArkDrawExecutor11.h
//--------------------------------------------------------------------------------
template <class TVertex>
ArkDrawExecutor11<TVertex>::ArkDrawExecutor11( )
{
	// Default to triangle list...
	m_ePrimType = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}
//--------------------------------------------------------------------------------
template <class TVertex>
ArkDrawExecutor11<TVertex>::~ArkDrawExecutor11()
{
}
//--------------------------------------------------------------------------------
template <class TVertex>
void ArkDrawExecutor11<TVertex>::Execute( PipelineManager* pPipeline, IParameterManager* pParamManager )
{
	// If any vertices have been added, then render them!

	if ( VertexBuffer.GetElementCount() > 0 ) {

		// First upload the data to the D3D11 buffer resource (this only uploads
		// if something has been changed since last upload).
		VertexBuffer.UploadData( pPipeline );
	
		pPipeline->InputAssemblerStage.ClearCurrentState();

		// Set the Input Assembler state, then perform the draw call.
		int layout = GetInputLayout( pPipeline->ShaderStages[VERTEX_SHADER]->CurrentState.ShaderProgram.GetState() );
		pPipeline->InputAssemblerStage.CurrentState.InputLayout.SetState( layout );
		pPipeline->InputAssemblerStage.CurrentState.PrimitiveTopology.SetState( m_ePrimType );
		pPipeline->InputAssemblerStage.CurrentState.VertexBuffers.SetState( 0, VertexBuffer.GetBuffer()->m_iResource );
		pPipeline->InputAssemblerStage.CurrentState.VertexBufferStrides.SetState( 0, sizeof( TVertex ) );
		pPipeline->InputAssemblerStage.CurrentState.VertexBufferOffsets.SetState( 0, 0 );
	
		pPipeline->ApplyInputResources();

		// Perform a draw call without any indices, instances, or indirect anything!
		pPipeline->Draw( VertexBuffer.GetElementCount(), 0 );
	}
}
//--------------------------------------------------------------------------------
template <class TVertex>
void ArkDrawExecutor11<TVertex>::ResetGeometry()
{
	// Reset the vertex count here to prepare for the next drawing pass.
	
	ResetVertices();
}
//--------------------------------------------------------------------------------
template <class TVertex>
void ArkDrawExecutor11<TVertex>::ResetVertices()
{
	VertexBuffer.ResetData();
}
//--------------------------------------------------------------------------------
template <class TVertex>
void ArkDrawExecutor11<TVertex>::AddVertex( const TVertex& vertex )
{
	VertexBuffer.AddElement( vertex );
}
//--------------------------------------------------------------------------------
template <class TVertex>
D3D11_PRIMITIVE_TOPOLOGY ArkDrawExecutor11<TVertex>::GetPrimitiveType()
{
	return( m_ePrimType );
}
//--------------------------------------------------------------------------------
template <class TVertex>
void ArkDrawExecutor11<TVertex>::SetPrimitiveType( D3D11_PRIMITIVE_TOPOLOGY type )
{
	m_ePrimType = type;
}
//--------------------------------------------------------------------------------
template <class TVertex>
unsigned int ArkDrawExecutor11<TVertex>::GetVertexCount()
{
	return( VertexBuffer.GetElementCount() );
}
//--------------------------------------------------------------------------------
template <class TVertex>
unsigned int ArkDrawExecutor11<TVertex>::GetPrimitiveCount()
{
	unsigned int count = 0;
	unsigned int referencedVertices = VertexBuffer.GetElementCount();

	switch ( m_ePrimType )
	{
	case D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED:
		break;
	case D3D11_PRIMITIVE_TOPOLOGY_POINTLIST:
		count = referencedVertices; break;
	case D3D11_PRIMITIVE_TOPOLOGY_LINELIST:
		count = referencedVertices / 2; break;
	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP:
		count = referencedVertices - 1; break;
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		count = referencedVertices / 3; break;
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
		count = referencedVertices - 2; break;
	case D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
		count = referencedVertices / 4; break;
	case D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
		count = referencedVertices - 3; break;
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
		count = referencedVertices / 6; break;
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
		count = ( referencedVertices - 3 ) / 2; break;
	case D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST:
		count = referencedVertices; break;
	case D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 2; break;
	case D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 3; break;
	case D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 4; break;
	case D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 5; break;
	case D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 6; break;
	case D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 7; break;
	case D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 8; break;
	case D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 9; break;
	case D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 10; break;
	case D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 11; break;
	case D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 12; break;
	case D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 13; break;
	case D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 14; break;
	case D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 15; break;
	case D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 16; break;
	case D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 17; break;
	case D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 18; break;
	case D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 19; break;
	case D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 20; break;
	case D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 21; break;
	case D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 22; break;
	case D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 23; break;
	case D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 24; break;
	case D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 25; break;
	case D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 26; break;
	case D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 27; break;
	case D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 28; break;
	case D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 29; break;
	case D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 30; break;
	case D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 31; break;
	case D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST:
		count = referencedVertices / 32; break;
	}

	return( count );
}
//--------------------------------------------------------------------------------
template <class TVertex>
void ArkDrawExecutor11<TVertex>::SetMaxVertexCount( unsigned int count )
{
	VertexBuffer.SetMaxElementCount( count );
}
//--------------------------------------------------------------------------------
