#pragma once
#include "base.h"

class CMaterial
{
public:
	CMaterial();

	CMaterial( D3DXCOLOR color);
	~CMaterial();

	void setAmbient( D3DXCOLOR color);

	void setDiffuse( D3DXCOLOR color);

	void setEmissive( D3DXCOLOR color);

	void setSpecular( D3DXCOLOR color);

	void setPower( float power);

	void useMaterial();

private:
	D3DMATERIAL9 mat;
};