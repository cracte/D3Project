#include "PixelShader.h"

CPixelShader::CPixelShader()
{
	//编译像素着色器
	ID3DXBuffer* pErrorBuff;
	D3DXCompileShaderFromFile( "../Resource/shader/pixel.hlsl", NULL, NULL, "main", "ps_2_0", D3DXSHADER_DEBUG, &m_pShader, &pErrorBuff, &m_pConstantTable);
	if( pErrorBuff)
	{
		Log( (char*)pErrorBuff->GetBufferPointer());
		return;
	}
	//创建像素着色器
	g_pDevice->CreatePixelShader( (DWORD*)m_pShader->GetBufferPointer(), &m_pPixelShader);
	//设置常量默认值
	m_pConstantTable->SetDefaults( g_pDevice);
}

CPixelShader::~CPixelShader()
{
	m_pShader->Release();
	m_pPixelShader->Release();
}

void CPixelShader::setShader()
{
	//设置像素着色器
	g_pDevice->SetPixelShader( m_pPixelShader);
}