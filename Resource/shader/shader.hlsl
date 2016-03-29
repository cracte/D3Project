extern texture tex; //纹理
extern matrix worldMat; //世界坐标

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
		//VertexShader = compile vs_2_0 VertexMain(); //定义顶点着色器
		//PixelShader = compile ps_2_0 PixelMain(); //定义像素着色器
		
		fvf = XYZ | Normal | Tex1;
		Lighting = true;  //开启灯光
		NormalizeNormals = true; //法线向量标准化
		SpecularEnable = false; //关闭镜面反射光计算
		
		//变换
		WorldTransform[0] = (worldMat);
		//ViewTransform = (viewMat);
		//ProjectionTransform = (projMat);
		
		//设置灯光
		LightType[0] = Directional;
		LightAmbient[0] = {0.2f, 0.2f, 0.2f, 1.0f};
		LightDiffuse[0] = {1.0f, 1.0f, 1.0f, 1.0f};
		LightSpecular[0] = {0.0f,  0.0f, 0.0f, 1.0f};
		LightDirection[0] = {1.0f, -1.0f, 1.0f, 0.0f};
		LightPosition[0] = {0.0f,  0.0f, 0.0f, 0.0f};
		
		LightEnable[0] = true;
		
		//设置材质
		MaterialAmbient = {1.0f, 1.0f, 1.0f, 1.0f};
		MaterialDiffuse = {1.0f, 1.0f, 1.0f, 1.0f};
		MaterialEmissive = {0.0f, 0.0f, 0.0f, 0.0f};
		MaterialPower = 1.0f;
		MaterialSpecular = {1.0f, 1.0f, 1.0f, 1.0f};
		
		//设置采样器
		Sampler[0] = s0;
	}
}