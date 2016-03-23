sampler baseTex; //采样器1
sampler lightTex; //采样器2

struct PS_INPUT
{
	float2 baseCoord : TEXCOORD1; //采样器1纹理坐标
	float2 lightCoord : TEXCOORD2; //采样器2纹理坐标
};

struct PS_OUTPUT
{
	vector diffuse : COLOR; //输出每个像素
};

PS_OUTPUT main( PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	vector color1 = tex2D( baseTex, input.baseCoord); //取采样器1纹理
	vector color2 = tex2D( lightTex, input.lightCoord); //取采样器2纹理
	vector color = color1*color2;
	output.diffuse = color;
	return output;
}