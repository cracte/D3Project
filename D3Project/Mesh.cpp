#include "Mesh.h"

CMesh::CMesh( char* fileName)
{
	char meshName[512];
	sprintf( meshName, "../Resource/Mesh/%s", fileName);
	D3DXLoadMeshFromX( meshName, D3DXMESH_SYSTEMMEM, g_pDevice, NULL, &m_pMatrialBuffer, NULL, &m_numOfMatrial, &m_pMesh); //读取mesh文件
	D3DXMATERIAL* materal = (D3DXMATERIAL*)m_pMatrialBuffer->GetBufferPointer();  //mesh文件中的材质读取到内存

	m_pMeshMaterials = new D3DMATERIAL9[m_numOfMatrial]; 
	m_pMeshTextures = new IDirect3DTexture9* [m_numOfMatrial];

	for( DWORD i=0; i<m_numOfMatrial; i++)
	{
		m_pMeshMaterials[i] = materal[i].MatD3D;  //材质
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse; //材质中没有环境光，所以漫反射光
		char resPath[512];
		sprintf( resPath, "../Resource/Texture/%s", materal[i].pTextureFilename);  //纹理
		HRESULT hr = D3DXCreateTextureFromFile( g_pDevice, resPath, &m_pMeshTextures[i]);
		if( hr < 0)
			m_pMeshTextures[i] = NULL;
	}
	m_pMatrialBuffer->Release();
};

CMesh::~CMesh()
{
	if( m_pMeshMaterials)	//释放材质
		delete[] m_pMeshMaterials;
	if( m_pMeshTextures)
	{
		for( DWORD i=0; i<m_numOfMatrial; i++)	//释放纹理
		{
			m_pMeshTextures[i]->Release();
		}
		delete[] m_pMeshTextures;
	}
	if( m_pMesh)	//释放网格
		m_pMesh->Release();
}

void CMesh::useMesh()
{
	D3DXMATRIX worldMat;
	D3DXMatrixTranslation( &worldMat, 0.0f, 0.0f, 0.0f);  //坐标转换为矩阵
	g_pDevice->SetTransform( D3DTS_WORLD, &worldMat);  //设置世界坐标位置
	for( DWORD i=0; i<m_numOfMatrial; i++)
	{
		g_pDevice->SetMaterial( &m_pMeshMaterials[i]);	//设置材质
		g_pDevice->SetTexture( 0, m_pMeshTextures[i]);	//设置纹理
		m_pMesh->DrawSubset( i);	//渲染网格
	}
}
