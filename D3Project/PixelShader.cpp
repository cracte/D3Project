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
	setConstant();
}

CPixelShader::~CPixelShader()
{
	m_pShader->Release();
	m_pPixelShader->Release();
	m_pConstantTable->Release();
}

//设置常量
void CPixelShader::setConstant()
{
	//取常量句柄
	D3DXHANDLE baseTexHandle = m_pConstantTable->GetConstantByName( NULL, "baseTex");
	D3DXHANDLE lightTexHandle = m_pConstantTable->GetConstantByName( NULL, "lightTex");
	//取常量描述
	D3DXCONSTANT_DESC baseTexDesc;
	D3DXCONSTANT_DESC lightTexDesc;
	UINT count;
	m_pConstantTable->GetConstantDesc( baseTexHandle, &baseTexDesc, &count);
	m_pConstantTable->GetConstantDesc( lightTexHandle, &lightTexDesc, &count);
	//读取纹理
	IDirect3DTexture9* baseTexture;
	IDirect3DTexture9* lightTextrue;
	D3DXCreateTextureFromFile( g_pDevice, "../Resource/Texture/crate.bmp", &baseTexture);
	D3DXCreateTextureFromFile( g_pDevice, "../Resource/Texture/spotlight.bmp", &lightTextrue);
	//设置常量
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
	//设置像素着色器
	g_pDevice->SetPixelShader( m_pPixelShader);
}