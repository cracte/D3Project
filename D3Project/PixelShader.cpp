#include "PixelShader.h"

CPixelShader::CPixelShader()
{
	//����������ɫ��
	ID3DXBuffer* pErrorBuff;
	D3DXCompileShaderFromFile( "../Resource/shader/pixel.hlsl", NULL, NULL, "main", "ps_2_0", D3DXSHADER_DEBUG, &m_pShader, &pErrorBuff, &m_pConstantTable);
	if( pErrorBuff)
	{
		Log( (char*)pErrorBuff->GetBufferPointer());
		return;
	}
	//����������ɫ��
	g_pDevice->CreatePixelShader( (DWORD*)m_pShader->GetBufferPointer(), &m_pPixelShader);
	//���ó���Ĭ��ֵ
	m_pConstantTable->SetDefaults( g_pDevice);
}

CPixelShader::~CPixelShader()
{
	m_pShader->Release();
	m_pPixelShader->Release();
}

void CPixelShader::setShader()
{
	//����������ɫ��
	g_pDevice->SetPixelShader( m_pPixelShader);
}