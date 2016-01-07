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

class CTexture
{
public:
	CTexture( char* fileName);
	~CTexture();

	void useTexture();

	void setSampler( Sampler_Type type, int level = 0); //设置采样器
	void setMipmaps( Mipmaps_Type type);//设置过滤器

private:
	IDirect3DTexture9* m_pTexture;
};