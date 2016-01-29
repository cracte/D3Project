#include "Texture.h"

CTexture::CTexture( char* fileName)
{
	char pathName[512];
	sprintf( pathName, "../Resource/Texture/%s", fileName);
	HRESULT hr = D3DXCreateTextureFromFile( g_pDevice, pathName, &m_pTexture);
}

CTexture::~CTexture()
{

}

void CTexture::useTexture()
{
	g_pDevice->SetTexture( 0, m_pTexture);

	g_pDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	g_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	g_pDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	g_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
}

void CTexture::setSampler(Sampler_Type type, int level)
{
	if( type == Sampler_Point)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT); //缩小采样
		g_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT); //放大采样
	}
	else if( type == Sampler_Linear)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	else if( type == Sampler_Anisotropic)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
		g_pDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
		g_pDevice->SetSamplerState( 0, D3DSAMP_MAXANISOTROPY, level);
	}
}

void CTexture::setMipmaps( Mipmaps_Type type)
{
	if( type == Mipmaps_None)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}
	else if( type == Mipmaps_Point)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	}
	else if( type == Mipmaps_Linear)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	}
}

void CTexture::setAddressMode( AddressMode_Type type)
{
	if( type == AddressMode_Wrap)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP); //纹理u轴
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP); //纹理v轴
	}
	else if( type == AddressMode_Border)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		g_pDevice->SetSamplerState( 0, D3DSAMP_BORDERCOLOR, 0xffffffff); //边框颜色
	}
	else if( type == AddressMode_Clamp)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	}
	else if( type == AddressMode_Mirror)
	{
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		g_pDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
	}
}

//开启混合渲染完之后要关闭混合
void CTexture::setBlend( bool isUseBlend, BlendType type)
{
	g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, isUseBlend); //开启alpha值混合

	if( isUseBlend)
	{
		g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //设置原资源混合模式
		g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //设置混合资源混合模式

		if( type == BlendType_Diffuse)
		{
			//设置alpha资源为材质
			g_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			g_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
		}
		else if( type == BlendType_Texture)
		{
			//设置alpha资源为纹理的alpha通道
			g_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
			g_pDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		}
	}
}