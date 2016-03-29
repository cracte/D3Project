#include "ShaderEffect.h"

CShaderEffect::CShaderEffect()
{
	//������ɫ��
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
//���ó���
void CShaderEffect::setConstant()
{
	//��������
	IDirect3DTexture9* texture;
	D3DXCreateTextureFromFile( g_pDevice, "../Resource/Texture/banana.bmp", &texture);
	D3DXHANDLE texHandle = m_pEffect->GetParameterByName( NULL, "tex");
	m_pEffect->SetTexture( texHandle, texture);
	//������������
	D3DXMATRIX worldMat;
	D3DXMatrixTranslation( &worldMat, 0.0f, 0.0f, 4.0f);  //����ת��Ϊ����
	D3DXHANDLE posHandle = m_pEffect->GetParameterByName( NULL, "worldMat");
	m_pEffect->SetMatrix( posHandle, &worldMat);
}
//ʹ��Ч��
void CShaderEffect::setShader()
{
	//��������
	D3DXHANDLE tech = m_pEffect->GetTechniqueByName( "tech1");
	//���Ӳ���Ƿ�֧��
	if( m_pEffect->ValidateTechnique( tech) == S_OK)
	{
		//���ü���
		m_pEffect->SetTechnique( tech);
		//�����Ĺ�������
		UINT passNum = 0;
		m_pEffect->Begin( &passNum, 0);
		for( UINT i=0; i<passNum; i++)
		{
			//��Ⱦ����
			m_pEffect->BeginPass( i);
			m_pMesh->DrawSubset( 0);
			m_pEffect->EndPass();
		}
		m_pEffect->End();
	}
}