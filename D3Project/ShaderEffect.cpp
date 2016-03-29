#include "ShaderEffect.h"

CShaderEffect::CShaderEffect()
{
	//编译着色器
	ID3DXBuffer* pErrorBuffer = NULL;
	D3DXCreateEffectFromFile( g_pDevice, "../Resource/shader/shader.hlsl", NULL, NULL, D3DXSHADER_DEBUG, 0, &m_pEffect, &pErrorBuffer);
	if( pErrorBuffer)
	{
		Log( (char*)pErrorBuffer->GetBufferPointer());
		return;
	}
	
	D3DXCreateTeapot( g_pDevice, &m_pMesh, NULL);
}

CShaderEffect::~CShaderEffect()
{
	m_pEffect->Release();
	m_pMesh->Release();
}	
//设置常量
void CShaderEffect::setConstant()
{
	//设置纹理
	IDirect3DTexture9* texture;
	D3DXCreateTextureFromFile( g_pDevice, "../Resource/Texture/banana.bmp", &texture);
	D3DXHANDLE texHandle = m_pEffect->GetParameterByName( NULL, "tex");
	m_pEffect->SetTexture( texHandle, texture);
	//设置世界坐标
	D3DXMATRIX worldMat;
	D3DXMatrixTranslation( &worldMat, 0.0f, 0.0f, 4.0f);  //坐标转换为矩阵
	D3DXHANDLE posHandle = m_pEffect->GetParameterByName( NULL, "worldMat");
	m_pEffect->SetMatrix( posHandle, &worldMat);
}
//使用效果
void CShaderEffect::setShader()
{
	//活动技术句柄
	D3DXHANDLE tech = m_pEffect->GetTechniqueByName( "tech1");
	//检测硬件是否支持
	if( m_pEffect->ValidateTechnique( tech) == S_OK)
	{
		//设置技术
		m_pEffect->SetTechnique( tech);
		//技术的过程数量
		UINT passNum = 0;
		m_pEffect->Begin( &passNum, 0);
		for( UINT i=0; i<passNum; i++)
		{
			//渲染过程
			m_pEffect->BeginPass( i);
			m_pMesh->DrawSubset( 0);
			m_pEffect->EndPass();
		}
		m_pEffect->End();
	}
}