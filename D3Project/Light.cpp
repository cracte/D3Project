#include "Light.h"

CLight::CLight()
{
	memset( &m_light, 0, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_light.Direction = D3DXVECTOR3(0.5,1.0,0.5);
	m_light.Position = D3DXVECTOR3(-0.1,-0.1,-0.1);
	m_light.Range = 1000.0;
}

CLight::~CLight()
{

}

void CLight::useLight()
{
	g_pDevice->SetLight( 0, &m_light);
	g_pDevice->LightEnable( 0, true);
	g_pDevice->SetRenderState( D3DRS_LIGHTING, true);
	g_pDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff);
}