sampler baseTex; //������1
sampler lightTex; //������2

struct PS_INPUT
{
	float2 baseCoord : TEXCOORD1; //������1��������
	float2 lightCoord : TEXCOORD2; //������2��������
};

struct PS_OUTPUT
{
	vector diffuse : COLOR; //���ÿ������
};

PS_OUTPUT main( PS_INPUT input)
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	vector color1 = tex2D( baseTex, input.baseCoord); //ȡ������1����
	vector color2 = tex2D( lightTex, input.lightCoord); //ȡ������2����
	vector color = color1*color2;
	output.diffuse = color;
	return output;
}