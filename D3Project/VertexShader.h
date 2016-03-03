#pragma once
#include "base.h"

class CVertexShader
{
public:
	CVertexShader();
	~CVertexShader();

	void setConstant( D3DXMATRIX* matrix);

private:
	IDirect3DVertexDeclaration9* m_pDeclaration;
	ID3DXBuffer* m_pShader; //编译后的shader
	ID3DXBuffer* m_pErrorMsg; //错误消息
	ID3DXConstantTable* m_pConstantTable; //常量表
	IDirect3DVertexShader9* m_pVertexShader; //顶点着色器
};