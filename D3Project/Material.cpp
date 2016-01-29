#include "Material.h"

CMaterial::CMaterial()
{
	memset( &mat, 0, sizeof(mat));
	mat.Ambient = D3DXCOLOR(0xffffffff);
	mat.Diffuse = D3DXCOLOR(0xffffffff);
	mat.Emissive = D3DXCOLOR(0xffffffff);
	mat.Specular = D3DXCOLOR(0xffffffff);
	mat.Power = 1.0;
}

CMaterial::CMaterial( D3DXCOLOR color)
{
	memset( &mat, 0, sizeof(mat));
	mat.Ambient = color;
	mat.Diffuse = color;
	mat.Emissive = color;
	mat.Specular = color;
	mat.Power = 1.0;
}

CMaterial::~CMaterial()
{

}

void CMaterial::useMaterial()
{
	g_pDevice->SetMaterial( &mat);
}

void CMaterial::setAmbient(D3DXCOLOR color)
{
	mat.Ambient = color;
}

void CMaterial::setDiffuse(D3DXCOLOR color)
{
	mat.Diffuse = color;
}

void CMaterial::setEmissive(D3DXCOLOR color)
{
	mat.Emissive = color;
}

void CMaterial::setSpecular(D3DXCOLOR color)
{
	mat.Specular = color;
}

void CMaterial::setPower(float power)
{
	mat.Power = power;
}