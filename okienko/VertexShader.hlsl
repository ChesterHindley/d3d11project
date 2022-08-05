struct Vertex
{
	float3 color : COLOR;
	float4 v : SV_POSITION;
};

cbuffer buf
{
	matrix transform;

};

Vertex main( float3 pos : POSITION,float3 color : COLOR )
{
	Vertex v;
	v.v = mul(float4(pos, 1.0f),transform);
	v.color = color;
	return v;
}