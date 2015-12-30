#include "Material.h"

CMaterial::CMaterial()
{
	memset( &mat, 0, sizeof(mat));
	mat.Ambient = D3DXCOLOR( 1.0, 0.0, 1.0, 0.0);
	mat.Diffuse = D3DXCOLOR( 1.0, 0.0, 1.0, 0.0);
	mat.Emissive = D3DXCOLOR( 1.0, 0.0, 1.0, 0.0);
	mat.Power = 1.0;
}

CMaterial::~CMaterial()
{

}

void CMaterial::useMaterial()
{
	g_pDevice->SetMaterial( &mat);
}