#pragma once
#include "base.h"

class CLight
{
public:
	CLight();
	~CLight();

	void useLight();

private:
	D3DLIGHT9 m_light;
};