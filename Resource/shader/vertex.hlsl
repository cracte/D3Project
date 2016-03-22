matrix viewMat;
vector color = {1.0f, 0.0f, 1.0f, 1.0f};

struct VS_INPUT
{
	vector color : COLOR;
	vector position : POSITION;
};

struct VS_OUTPUT
{
	vector color : COLOR;
	vector position : POSITION;
};

VS_OUTPUT main( VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.color = color;
	output.position = mul( input.position, viewMat);
	return output;
}