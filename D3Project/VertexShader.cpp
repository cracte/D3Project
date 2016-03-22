#include "VertexShader.h"

CVertexShader::CVertexShader( )
{
	//声明顶点
	D3DVERTEXELEMENT9 vetexDec[] = 
	{
		{0, 0, D3DDECLTYPE_FLOAT4, 0, D3DDECLUSAGE_COLOR, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_POSITION, 0},
		D3DDECL_END()
	};
	//创建顶点声明
	g_pDevice->CreateVertexDeclaration( vetexDec, &m_pDeclaration);

	//编译顶点着色器
	D3DXCompileShaderFromFile( "../Resource/shader/vertex.hlsl", NULL, NULL, "main", "vs_2_0", D3DXSHADER_DEBUG, &m_pShader, &m_pErrorMsg, &m_pConstantTable);
	if( m_pErrorMsg)
	{
		Log( (char*)m_pErrorMsg->GetBufferPointer());
		return;
	}
	//创建顶点着色器
	g_pDevice->CreateVertexShader( (DWORD*)m_pShader->GetBufferPointer(), &m_pVertexShader);
	//设置常量默认值
	m_pConstantTable->SetDefaults( g_pDevice);
}

CVertexShader::~CVertexShader()
{
	m_pShader->Release();
	m_pVertexShader->Release();
	m_pConstantTable->Release();
}

void CVertexShader::setConstant(D3DXMATRIX* matrix)
{
	//设置顶点声明
	g_pDevice->SetVertexDeclaration( m_pDeclaration);
	//设置常量
	D3DXHANDLE viewMatrix = m_pConstantTable->GetConstantByName( NULL, "viewMat");
	m_pConstantTable->SetMatrix( g_pDevice, viewMatrix, matrix);
	//设置着色器
	g_pDevice->SetVertexShader( m_pVertexShader);
}