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
	ID3DXBuffer* m_pShader; //编译后的shader
	ID3DXConstantTable* m_pConstantTable; //常量表
	IDirect3DPixelShader9* m_pPixelShader; //像素着色器
};