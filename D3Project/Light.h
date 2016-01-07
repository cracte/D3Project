#pragma once
#include "base.h"

enum LightType
{
	LightType_Directional, //方向光源
	LightType_Point, //点光源
	LightType_Spot, //聚光灯
};

class CLight
{
public:
	CLight();
	CLight( LightType lightType);
	~CLight();

	void useLight();
	void enableSpeular( bool isEnable); //开关镜面反射光计算
	void setPosition( D3DXVECTOR3* pos);

private:
	D3DLIGHT9 m_light;
	LightType m_type;
};