#include "Mesh.h"

CMesh::CMesh( char* fileName)
{
	char meshName[512];
	sprintf( meshName, "../Resource/Mesh/%s", fileName);
	D3DXLoadMeshFromX( meshName, D3DXMESH_SYSTEMMEM, g_pDevice, NULL, &m_pMatrialBuffer, NULL, &m_numOfMatrial, &m_pMesh); //��ȡmesh�ļ�
	D3DXMATERIAL* materal = (D3DXMATERIAL*)m_pMatrialBuffer->GetBufferPointer();  //mesh�ļ��еĲ��ʶ�ȡ���ڴ�

	m_pMeshMaterials = new D3DMATERIAL9[m_numOfMatrial]; 
	m_pMeshTextures = new IDirect3DTexture9* [m_numOfMatrial];

	for( DWORD i=0; i<m_numOfMatrial; i++)
	{
		m_pMeshMaterials[i] = materal[i].MatD3D;  //����
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse; //������û�л����⣬�����������
		char resPath[512];
		sprintf( resPath, "../Resource/Texture/%s", materal[i].pTextureFilename);  //����
		HRESULT hr = D3DXCreateTextureFromFile( g_pDevice, resPath, &m_pMeshTextures[i]);
		if( hr < 0)
			m_pMeshTextures[i] = NULL;
	}
	m_pMatrialBuffer->Release();
};

CMesh::~CMesh()
{
	if( m_pMeshMaterials)	//�ͷŲ���
		delete[] m_pMeshMaterials;
	if( m_pMeshTextures)
	{
		for( DWORD i=0; i<m_numOfMatrial; i++)	//�ͷ�����
		{
			m_pMeshTextures[i]->Release();
		}
		delete[] m_pMeshTextures;
	}
	if( m_pMesh)	//�ͷ�����
		m_pMesh->Release();
}

void CMesh::useMesh()
{
	D3DXMATRIX worldMat;
	D3DXMatrixTranslation( &worldMat, 0.0f, 0.0f, 0.0f);  //����ת��Ϊ����
	g_pDevice->SetTransform( D3DTS_WORLD, &worldMat);  //������������λ��
	for( DWORD i=0; i<m_numOfMatrial; i++)
	{
		g_pDevice->SetMaterial( &m_pMeshMaterials[i]);	//���ò���
		g_pDevice->SetTexture( 0, m_pMeshTextures[i]);	//��������
		m_pMesh->DrawSubset( i);	//��Ⱦ����
	}
}
