#pragma once
#include "base.h"

enum LightType
{
	LightType_Directional, //�����Դ
	LightType_Point, //���Դ
	LightType_Spot, //�۹��
};

class CLight
{
public:
	CLight();
	CLight( LightType lightType);
	~CLight();

	void useLight();
	void enableSpeular( bool isEnable); //���ؾ��淴������
	void setPosition( D3DXVECTOR3* pos);

private:
	D3DLIGHT9 m_light;
	LightType m_type;
};