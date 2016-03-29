extern texture tex; //����
extern matrix worldMat; //��������

sampler s0 = sampler_state
{
	Texture = (tex);
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

technique tech1
{
	pass p1
	{
		//VertexShader = compile vs_2_0 VertexMain(); //���嶥����ɫ��
		//PixelShader = compile ps_2_0 PixelMain(); //����������ɫ��
		
		fvf = XYZ | Normal | Tex1;
		Lighting = true;  //�����ƹ�
		NormalizeNormals = true; //����������׼��
		SpecularEnable = false; //�رվ��淴������
		
		//�任
		WorldTransform[0] = (worldMat);
		//ViewTransform = (viewMat);
		//ProjectionTransform = (projMat);
		
		//���õƹ�
		LightType[0] = Directional;
		LightAmbient[0] = {0.2f, 0.2f, 0.2f, 1.0f};
		LightDiffuse[0] = {1.0f, 1.0f, 1.0f, 1.0f};
		LightSpecular[0] = {0.0f,  0.0f, 0.0f, 1.0f};
		LightDirection[0] = {1.0f, -1.0f, 1.0f, 0.0f};
		LightPosition[0] = {0.0f,  0.0f, 0.0f, 0.0f};
		
		LightEnable[0] = true;
		
		//���ò���
		MaterialAmbient = {1.0f, 1.0f, 1.0f, 1.0f};
		MaterialDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};
		MaterialEmissive = {0.0f, 0.0f, 0.0f, 0.0f};
		MaterialPower = 1.0f;
		MaterialSpecular = {1.0f, 1.0f, 1.0f, 1.0f};
		
		//���ò�����
		Sampler[0] = s0;
	}
}