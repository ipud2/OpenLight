Texture2D       gTexture        :   register( t0 );
SamplerState    gSampleLinear   :   register( s0 );

struct VertexOut
{
    float4 PosH     :       SV_POSITION;
    float2 Tex      :       TEXCOORD;
};

float4 main( VertexOut input ) : SV_TARGET
{
	float4 color = gTexture.Sample( gSampleLinear , input.Tex );
    return color;
}