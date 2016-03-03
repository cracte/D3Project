#include "VertexShader.h"

CVertexShader::CVertexShader( )
{
	//��������
	D3DVERTEXELEMENT9 vetexDec[] = 
	{
		{0, 0, D3DDECLTYPE_FLOAT4, 0, D3DDECLUSAGE_COLOR, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};
	//������������
	g_pDevice->CreateVertexDeclaration( vetexDec, &m_pDeclaration);

	//���붥����ɫ��
	D3DXCompileShaderFromFile( "../Resource/shader/shader.hlsl", NULL, NULL, "main", "vs_2_0", D3DXSHADER_DEBUG, &m_pShader, &m_pErrorMsg, &m_pConstantTable);
	if( m_pErrorMsg)
	{
		Log( (char*)m_pErrorMsg->GetBufferPointer());
		return;
	}
	//����������ɫ��
	g_pDevice->CreateVertexShader( (DWORD*)m_pShader->GetBufferPointer(), &m_pVertexShader);
	//���ó���Ĭ��ֵ
	m_pConstantTable->SetDefaults( g_pDevice);
}

CVertexShader::~CVertexShader()
{

}

void CVertexShader::setConstant(D3DXMATRIX* matrix)
{
	//���ó���
	D3DXHANDLE viewMatrix = m_pConstantTable->GetConstantByName( NULL, "viewMat");
	m_pConstantTable->SetMatrix( g_pDevice, viewMatrix, matrix);
	g_pDevice->SetVertexShader( m_pVertexShader);
}