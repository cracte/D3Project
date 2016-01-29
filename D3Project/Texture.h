#pragma once
#include "base.h"

enum Sampler_Type
{
	Sampler_Point, //点采样
	Sampler_Linear, //线段采样
	Sampler_Anisotropic, //异性采样
};

enum Mipmaps_Type
{
	Mipmaps_None,
	Mipmaps_Point,
	Mipmaps_Linear,
};

enum AddressMode_Type
{
	AddressMode_Wrap, //环绕寻址
	AddressMode_Border, //边框寻址
	AddressMode_Clamp, //截取寻址
	AddressMode_Mirror, //镜像寻址
};

enum BlendType
{
	BlendType_Diffuse, //顶点(材质)混合
	BlendType_Texture, //纹理混合
};

class CTexture
{
public:
	CTexture( char* fileName);
	~CTexture();

	void useTexture();

	void setSampler( Sampler_Type type, int level = 0); //设置采样器
	void setMipmaps( Mipmaps_Type type);//设置过滤器
	void setAddressMode( AddressMode_Type type);//设置寻址模式

	void setBlend( bool isUseBlend, BlendType type = BlendType_Diffuse); //混合

private:
	IDirect3DTexture9* m_pTexture;
};