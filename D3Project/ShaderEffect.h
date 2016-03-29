#pragma once

#include "base.h"

class CShaderEffect
{
public:
	CShaderEffect();

	~CShaderEffect();

	void setConstant();

	void setShader();
private:
	ID3DXEffect* m_pEffect; //±àÒëºóµÄshader

	ID3DXMesh* m_pMesh;
};