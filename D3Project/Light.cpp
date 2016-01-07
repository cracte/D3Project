#include "Light.h"

CLight::CLight()
{
	m_type = LightType_Directional;

	memset( &m_light, 0, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR( 0xffffffff); //�������
	m_light.Ambient = D3DXCOLOR( 0xffffffff); //������
	m_light.Specular = D3DXCOLOR( 0xffffffff); //���淴���
	m_light.Position = D3DXVECTOR3(-0.1,-0.1,-0.1); //λ��,�Է����Դ��Ч
	m_light.Direction = D3DXVECTOR3(0.5,1.0,0.5); //����,�Ե��Դ��Ч
	m_light.Range = 5.0; //��Χ�������Դ��Ч
}

CLight::CLight( LightType lightType)
{
	m_type = lightType;

	memset( &m_light, 0, sizeof(m_light));
	if( lightType == LightType_Directional)
	{
		m_light.Type = D3DLIGHT_DIRECTIONAL;
		m_light.Diffuse = D3DXCOLOR( 0xffffffff); //�������
		m_light.Ambient = D3DXCOLOR( 0xffffffff); //������
		m_light.Specular = D3DXCOLOR( 0xffffffff); //���淴���
		m_light.Direction = D3DXVECTOR3(0.5,1.0,0.5); //����
	}
	else if( lightType == LightType_Point)
	{
		m_light.Type = D3DLIGHT_POINT;
		m_light.Diffuse = D3DXCOLOR( 0xffffffff); //�������
		m_light.Ambient = D3DXCOLOR( 0xffffffff); //������
		m_light.Specular = D3DXCOLOR( 0xffffffff); //���淴���
		m_light.Position = D3DXVECTOR3(0.0,0.0,0.0); //λ��
		m_light.Range = 500.0; //��Χ
		m_light.Attenuation0 = 0.1; //�㶨˥��
		m_light.Attenuation1 = 0.1; //һ��˥��
		m_light.Attenuation2 = 0.1; //����˥��
	}
	else if( lightType == LightType_Spot)
	{
		m_light.Type = D3DLIGHT_SPOT;
		m_light.Diffuse = D3DXCOLOR( 0xffffffff); //�������
		m_light.Ambient = D3DXCOLOR( 0xffffffff); //������
		m_light.Specular = D3DXCOLOR( 0xffffffff); //���淴���
		m_light.Position = D3DXVECTOR3(1.0,1.0,1.0); //λ��
		m_light.Direction = D3DXVECTOR3(0.0,0.0,5.0); //����
		m_light.Range = 5000.0; //��Χ
		m_light.Falloff = 1.0; //����Բ׶˥����
		m_light.Attenuation0 = 0.1; //�㶨˥��
		m_light.Attenuation1 = 0.1; //һ��˥��
		m_light.Attenuation2 = 0.1; //����˥��
		m_light.Theta = D3DX_PI/6; //�۹����Բ׶
		m_light.Phi = D3DX_PI/4; //�۹����Բ׶
	}
}

CLight::~CLight()
{

}

void CLight::useLight()
{
	g_pDevice->SetLight( 0, &m_light);
	g_pDevice->LightEnable( 0, true);
	g_pDevice->SetRenderState( D3DRS_LIGHTING, true); //�����ƹ�

	g_pDevice->SetRenderState( D3DRS_NORMALIZENORMALS, true);//����������׼��
	enableSpeular( true);
	//g_pDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff);//���û�����
}

void CLight::enableSpeular( bool isEnable)
{
	g_pDevice->SetRenderState( D3DRS_SPECULARENABLE, true);//�رվ��淴������
}

void CLight::setPosition( D3DXVECTOR3* pos)
{
	m_light.Position = *pos;
	//useLight();//�ı����Ժ��������ù�Դ
}