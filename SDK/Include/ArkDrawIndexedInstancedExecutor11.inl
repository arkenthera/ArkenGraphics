//--------------------------------------------------------------------------------
// This file is a portion of the Hieroglyph 3 Rendering Engine.  It is distributed
// under the MIT License, available in the root of this distribution and 
// at the following URL:
//
// http://www.opensource.org/licenses/mit-license.php
//
// Copyright (c) Jason Zink 
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::ArkDrawIndexedInstancedExecutor11( ) :
	m_uiStart( 0 ),
	m_uiCount( 0 )
{
	// Initialize our buffer to a reasonable size
	InstanceBuffer.SetMaxElementCount( 1000 );
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::~ArkDrawIndexedInstancedExecutor11()
{
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
void ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::Execute( PipelineManager* pPipeline, IParameterManager* pParamManager )
{
	// With instanced rendering, we only proceed if there are instances there to 
	// render.

	if ( InstanceBuffer.GetElementCount() > 0 ) {

		// Upload all the data to our D3D11 buffer resources.
		VertexBuffer.UploadData( pPipeline );
		IndexBuffer.UploadData( pPipeline );
		InstanceBuffer.UploadData( pPipeline );
	
		pPipeline->InputAssemblerStage.ClearCurrentState();

		// Set the Input Assembler state, then perform the draw call.
		int layout = GetInputLayout( pPipeline->ShaderStages[VERTEX_SHADER]->CurrentState.ShaderProgram.GetState() );
		pPipeline->InputAssemblerStage.CurrentState.InputLayout.SetState( layout );
		pPipeline->InputAssemblerStage.CurrentState.PrimitiveTopology.SetState( m_ePrimType );

		pPipeline->InputAssemblerStage.CurrentState.VertexBuffers.SetState( 0, VertexBuffer.GetBuffer()->m_iResource );
		pPipeline->InputAssemblerStage.CurrentState.VertexBufferStrides.SetState( 0, sizeof( TVertex ) );
		pPipeline->InputAssemblerStage.CurrentState.VertexBufferOffsets.SetState( 0, 0 );

		pPipeline->InputAssemblerStage.CurrentState.VertexBuffers.SetState( 1, InstanceBuffer.GetBuffer()->m_iResource );
		pPipeline->InputAssemblerStage.CurrentState.VertexBufferStrides.SetState( 1, sizeof( TInstance ) );
		pPipeline->InputAssemblerStage.CurrentState.VertexBufferOffsets.SetState( 1, 0 );

		pPipeline->InputAssemblerStage.CurrentState.IndexBuffer.SetState( IndexBuffer.GetBuffer()->m_iResource );
		pPipeline->InputAssemblerStage.CurrentState.IndexBufferFormat.SetState( DXGI_FORMAT_R32_UINT );
	
		pPipeline->ApplyInputResources();

		// Here we provide an index count and an instance count to the indexed 
		// instanced draw call.
		if ( m_uiCount == 0 ) {
			pPipeline->DrawIndexedInstanced( IndexBuffer.GetElementCount(), InstanceBuffer.GetElementCount(), 0, 0, 0 );
		} else {
			pPipeline->DrawIndexedInstanced( IndexBuffer.GetElementCount(), m_uiCount, 0, 0, m_uiStart );
		}
	}
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
void ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::ResetGeometry()
{
	// Reset the instances here to prepare for the next drawing pass.  Then
	// allow the super class to reset its buffers as well.

	ResetInstances();
	ArkDrawIndexedExecutor11::ResetGeometry();
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
void ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::ResetInstances()
{
	InstanceBuffer.ResetData();
	m_uiStart = 0;
	m_uiCount = 0;
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
void ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::AddInstance( const TInstance& data )
{
	InstanceBuffer.AddElement( data );
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
unsigned int ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::GetInstanceCount()
{
	// The number of instances is directly the number of vertices in the 
	// per-instance vertex buffer.

	return( InstanceBuffer.GetElementCount() );
}
//--------------------------------------------------------------------------------
template <class TVertex, class TInstance>
void ArkDrawIndexedInstancedExecutor11<TVertex,TInstance>::SetInstanceRange( unsigned int start, unsigned int end )
{
	// Validate the data before accepting it.
	if ( start < end && end < InstanceBuffer.GetElementCount() ) {
		m_uiStart = start;
		m_uiCount = end-start;
	} else {
		m_uiStart = 0;
		m_uiCount = 0;
	}
}
//--------------------------------------------------------------------------------
