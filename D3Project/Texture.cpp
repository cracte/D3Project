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