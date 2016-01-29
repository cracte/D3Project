#pragma once
#include "base.h"

enum Sampler_Type
{
	Sampler_Point, //�����
	Sampler_Linear, //�߶β���
	Sampler_Anisotropic, //���Բ���
};

enum Mipmaps_Type
{
	Mipmaps_None,
	Mipmaps_Point,
	Mipmaps_Linear,
};

enum AddressMode_Type
{
	AddressMode_Wrap, //����Ѱַ
	AddressMode_Border, //�߿�Ѱַ
	AddressMode_Clamp, //��ȡѰַ
	AddressMode_Mirror, //����Ѱַ
};

enum BlendType
{
	BlendType_Diffuse, //����(����)���
	BlendType_Texture, //������
};

class CTexture
{
public:
	CTexture( char* fileName);
	~CTexture();

	void useTexture();

	void setSampler( Sampler_Type type, int level = 0); //���ò�����
	void setMipmaps( Mipmaps_Type type);//���ù�����
	void setAddressMode( AddressMode_Type type);//����Ѱַģʽ

	void setBlend( bool isUseBlend, BlendType type = BlendType_Diffuse); //���

private:
	IDirect3DTexture9* m_pTexture;
};