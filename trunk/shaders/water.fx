float4x4 matWorldViewProj;
float4 vecSkill41;
//float4 vecSunDir;
float4 vecTime;

texture entSkin1;
sampler2D smpTex = sampler_state
{
	texture = <entSkin1>;
};

struct VS_OUT
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
	float3 normal : TEXCOORD1;
	float3 pos : TEXCOORD2;
};

VS_OUT vs_main(float4 inPos : POSITION, float4 inNormal : NORMAL, float2 inTex : TEXCOORD0)
{
	VS_OUT o = (VS_OUT)0;
	
/*	float fac = min(30.0/length(inPos.xz), 1.0);
	float wave = (length(inPos.xz)*0.1-vecSkill41.x)*5.0;
	if(wave > -3.1514*vecSkill41.y && wave < 0)
		inPos.y += sin(wave)*fac*fac*3.0;*/
	
	o.pos = inPos;
	o.position = mul(inPos, matWorldViewProj);
	o.texcoord = inTex;
	o.normal = float3(inPos.x+sin(vecTime.w*0.001*vecSkill41.z)*30.0, inPos.y, inPos.z+cos(vecTime.w*0.001*vecSkill41.z)*30.0);//float3(0.0, 0.0, 1.0)+inPos.y;//inNormal.xyz;
	return o;
}

float4 ps_main(float2 inTex : TEXCOORD0, float3 inNormal : TEXCOORD1, float3 inPos : TEXCOORD2) : COLOR0
{
	float facw = min(20.0/length(inPos.xz), 1.0);
	float wave = (length(inPos.xz)*0.1-vecSkill41.x);
	if(wave > -3.1514*vecSkill41.y && wave < 0)
		inPos.y += sin(wave)*facw*facw;
	
	float fac = length(inNormal.xz*0.2-round(inNormal.xz*0.05)*4.0)*0.2;
	
	float3 col = float3(1.0, 0.0, 0.0);
	col = lerp(col, float3(0.0, 1.0, 0.0), fac*(sin(vecTime.w*0.004*vecSkill41.z+fac)*0.5+0.5));
	col = lerp(col, float3(0.0, 0.0, 1.0), fac*fac*(cos(vecTime.w*0.004*vecSkill41.z+fac)*0.5+0.5));
	col = lerp(col, 1.0-col, inPos.y);
	return float4(col, 1.0);
}

technique t0
{
	pass p0
	{
		FillMode = 0;
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
}