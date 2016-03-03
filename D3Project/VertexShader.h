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
	ID3DXBuffer* m_pShader; //������shader
	ID3DXBuffer* m_pErrorMsg; //������Ϣ
	ID3DXConstantTable* m_pConstantTable; //������
	IDirect3DVertexShader9* m_pVertexShader; //������ɫ��
};