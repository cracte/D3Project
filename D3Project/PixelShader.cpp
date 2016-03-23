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
	setConstant();
}

CPixelShader::~CPixelShader()
{
	m_pShader->Release();
	m_pPixelShader->Release();
	m_pConstantTable->Release();
}

//���ó���
void CPixelShader::setConstant()
{
	//ȡ�������
	D3DXHANDLE baseTexHandle = m_pConstantTable->GetConstantByName( NULL, "baseTex");
	D3DXHANDLE lightTexHandle = m_pConstantTable->GetConstantByName( NULL, "lightTex");
	//ȡ��������
	D3DXCONSTANT_DESC baseTexDesc;
	D3DXCONSTANT_DESC lightTexDesc;
	UINT count;
	m_pConstantTable->GetConstantDesc( baseTexHandle, &baseTexDesc, &count);
	m_pConstantTable->GetConstantDesc( lightTexHandle, &lightTexDesc, &count);
	//��ȡ����
	IDirect3DTexture9* baseTexture;
	IDirect3DTexture9* lightTextrue;
	D3DXCreateTextureFromFile( g_pDevice, "../Resource/Texture/crate.bmp", &baseTexture);
	D3DXCreateTextureFromFile( g_pDevice, "../Resource/Texture/spotlight.bmp", &lightTextrue);
	//���ó���
	g_pDevice->SetTexture( baseTexDesc.RegisterIndex, baseTexture);
	g_pDevice->SetTexture( lightTexDesc.RegisterIndex, lightTextrue);
	g_pDevice->SetSamplerState( baseTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState( baseTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState( baseTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState( lightTexDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState( lightTexDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pDevice->SetSamplerState( lightTexDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
}

void CPixelShader::setShader()
{
	//����������ɫ��
	g_pDevice->SetPixelShader( m_pPixelShader);
}