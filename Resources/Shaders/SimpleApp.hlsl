//-----------------------------------------------------------------------------
cbuffer Transforms
 {
	matrix	 gWorld;
	matrix   WorldViewProjMatrix;
};
//-----------------------------------------------------------------------------
cbuffer LightBuffer
{
	float3 LightPositionWS;
	float4 LightColor;
};
//-----------------------------------------------------------------------------
struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal   : NORMAL;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color    : COLOR;
};

//-----------------------------------------------------------------------------
VS_OUTPUT VSMain( in VS_INPUT input )
{
	VS_OUTPUT output;
	
	output.position = mul( float4( input.position, 1.0f ), WorldViewProjMatrix );

	float3 NormalWS = mul( input.normal, (float3x3)gWorld );
	float diffuse = dot( normalize( float3( 1.0f, 1.0f, -1.0f ) ), NormalWS );

	output.color.rgb = LightColor.rgb * diffuse;

	output.color.a = 1.0f;

	return output;
}


//-----------------------------------------------------------------------------
float4 PSMain( in VS_OUTPUT input ) : SV_Target
{
	float4 color = input.color;

	return( color );
}
//-----------------------------------------------------------------------------