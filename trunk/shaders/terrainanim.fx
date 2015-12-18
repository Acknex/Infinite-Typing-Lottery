float4x4 matWorldViewProj;
float4x4 matWorld;
float4 vecSkill41;
float4 vecSunDir;
float4 vecTime;

texture mtlSkin1;
sampler2D smpBlend = sampler_state
{
	texture = <mtlSkin1>;
};

texture entSkin1;
sampler2D smpTex = sampler_state
{
	texture = <entSkin1>;
};

texture entSkin2;
sampler2D smpNorm = sampler_state
{
	texture = <entSkin2>;
};

struct VS_OUT
{
	float4 position : POSITION;
	float4 texcoord : TEXCOORD0;
	float3 lightdir : TEXCOORD1;
};

VS_OUT vs_main1(float4 inPos : POSITION, float4 inNormal : NORMAL, float2 inTex : TEXCOORD0)
{
	VS_OUT o = (VS_OUT)0;
	o.position = mul(inPos, matWorldViewProj);
	o.texcoord.xy = inTex;
	o.texcoord.zw = mul(inPos, matWorld).xz*0.001;
	o.lightdir = inNormal.xyz;
	return o;
}

float4 ps_main1(float4 inTex : TEXCOORD0, float3 inNormal : TEXCOORD1) : COLOR0
{
	float4 blend = tex2D(smpBlend, inTex.zw);
	clip(blend.x-vecSkill41.y);
	return tex2D(smpTex, inTex.xy)*(saturate(dot(inNormal, -vecSunDir.xyz))+0.5);
}

VS_OUT vs_main2(float4 inPos : POSITION, float4 inNormal : NORMAL, float2 inTex : TEXCOORD0, float4 inTangent : TEXCOORD2)
{
	VS_OUT o = (VS_OUT)0;
	float height = max(inPos.y+50.0, 0.0)*vecSkill41.x*0.1;
	inPos.x += sin(inPos.x*0.001+vecTime.w)*height;
	inPos.z += cos(inPos.z*0.001+vecTime.w)*height;
	inPos.y += height;
	o.position = mul(inPos, matWorldViewProj);
	o.texcoord.xy = inTex;
	o.texcoord.zw = mul(inPos, matWorld).xz*0.001;
	
	float3x3 matTangent;
	matTangent[0] = inNormal.xyz;
	matTangent[1] = cross(inNormal.xyz, inTangent.xyz);
	matTangent[2] = inTangent.xyz;
	
	o.lightdir = mul(matTangent, -vecSunDir);
	
	return o;
}

float4 ps_main2(float4 inTex : TEXCOORD0, float3 inLight : TEXCOORD1) : COLOR0
{
	float4 blend = tex2D(smpBlend, inTex.zw);
	clip(-blend.x+vecSkill41.y);
	float3 normal = tex2D(smpNorm, inTex.xy);
	return tex2D(smpTex, inTex.xy)*(saturate(dot(normal, inLight.xyz))+0.5);
}

technique t0
{
	pass p0
	{
		FillMode = 2;
		VertexShader = compile vs_3_0 vs_main1();
		PixelShader = compile ps_3_0 ps_main1();
	}
	
	pass p1
	{
		FillMode = 0;
		VertexShader = compile vs_3_0 vs_main2();
		PixelShader = compile ps_3_0 ps_main2();
	}
}