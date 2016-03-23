#pragma once
#include "base.h"

class CPixelShader
{
public:
	CPixelShader();
	~CPixelShader();

	void setConstant();
	void setShader();

private:
	ID3DXBuffer* m_pShader; //������shader
	ID3DXConstantTable* m_pConstantTable; //������
	IDirect3DPixelShader9* m_pPixelShader; //������ɫ��
};