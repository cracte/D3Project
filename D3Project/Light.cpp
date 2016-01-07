#include "Light.h"

CLight::CLight()
{
	m_type = LightType_Directional;

	memset( &m_light, 0, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR( 0xffffffff); //漫反射光
	m_light.Ambient = D3DXCOLOR( 0xffffffff); //环境光
	m_light.Specular = D3DXCOLOR( 0xffffffff); //镜面反射光
	m_light.Position = D3DXVECTOR3(-0.1,-0.1,-0.1); //位置,对方向光源无效
	m_light.Direction = D3DXVECTOR3(0.5,1.0,0.5); //方向,对点光源无效
	m_light.Range = 5.0; //范围，方向光源无效
}

CLight::CLight( LightType lightType)
{
	m_type = lightType;

	memset( &m_light, 0, sizeof(m_light));
	if( lightType == LightType_Directional)
	{
		m_light.Type = D3DLIGHT_DIRECTIONAL;
		m_light.Diffuse = D3DXCOLOR( 0xffffffff); //漫反射光
		m_light.Ambient = D3DXCOLOR( 0xffffffff); //环境光
		m_light.Specular = D3DXCOLOR( 0xffffffff); //镜面反射光
		m_light.Direction = D3DXVECTOR3(0.5,1.0,0.5); //方向
	}
	else if( lightType == LightType_Point)
	{
		m_light.Type = D3DLIGHT_POINT;
		m_light.Diffuse = D3DXCOLOR( 0xffffffff); //漫反射光
		m_light.Ambient = D3DXCOLOR( 0xffffffff); //环境光
		m_light.Specular = D3DXCOLOR( 0xffffffff); //镜面反射光
		m_light.Position = D3DXVECTOR3(0.0,0.0,0.0); //位置
		m_light.Range = 500.0; //范围
		m_light.Attenuation0 = 0.1; //恒定衰减
		m_light.Attenuation1 = 0.1; //一次衰减
		m_light.Attenuation2 = 0.1; //二次衰减
	}
	else if( lightType == LightType_Spot)
	{
		m_light.Type = D3DLIGHT_SPOT;
		m_light.Diffuse = D3DXCOLOR( 0xffffffff); //漫反射光
		m_light.Ambient = D3DXCOLOR( 0xffffffff); //环境光
		m_light.Specular = D3DXCOLOR( 0xffffffff); //镜面反射光
		m_light.Position = D3DXVECTOR3(1.0,1.0,1.0); //位置
		m_light.Direction = D3DXVECTOR3(0.0,0.0,5.0); //方向
		m_light.Range = 5000.0; //范围
		m_light.Falloff = 1.0; //内外圆锥衰减度
		m_light.Attenuation0 = 0.1; //恒定衰减
		m_light.Attenuation1 = 0.1; //一次衰减
		m_light.Attenuation2 = 0.1; //二次衰减
		m_light.Theta = D3DX_PI/6; //聚光灯内圆锥
		m_light.Phi = D3DX_PI/4; //聚光灯内圆锥
	}
}

CLight::~CLight()
{

}

void CLight::useLight()
{
	g_pDevice->SetLight( 0, &m_light);
	g_pDevice->LightEnable( 0, true);
	g_pDevice->SetRenderState( D3DRS_LIGHTING, true); //开启灯光

	g_pDevice->SetRenderState( D3DRS_NORMALIZENORMALS, true);//法线向量标准化
	enableSpeular( true);
	//g_pDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff);//设置环境光
}

void CLight::enableSpeular( bool isEnable)
{
	g_pDevice->SetRenderState( D3DRS_SPECULARENABLE, true);//关闭镜面反射光计算
}

void CLight::setPosition( D3DXVECTOR3* pos)
{
	m_light.Position = *pos;
	//useLight();//改变属性后重新设置光源
}