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