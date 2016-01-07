#include "XMesh.h"

CXMesh::CXMesh( char* fileName):
m_pMesh( NULL),
m_pMeshNormal( NULL)
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
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse; //������û�л����⣬��������Ϊ�������
		//m_pMeshMaterials[i].Diffuse = D3DXCOLOR( 0xff00ffff); //�������
		//m_pMeshMaterials[i].Specular = D3DXCOLOR( 0xff00ffff); //���淴���
		//m_pMeshMaterials[i].Emissive = D3DXCOLOR( 0xff00ffff); //�����
		char resPath[512];
		sprintf( resPath, "../Resource/Texture/%s", materal[i].pTextureFilename);  //����
		HRESULT hr = D3DXCreateTextureFromFile( g_pDevice, resPath, &m_pMeshTextures[i]);
		if( hr < 0)
			m_pMeshTextures[i] = NULL;
	}
	//�ڽ���Ϣ
	vector<DWORD> adjacencyInfo( m_pMesh->GetNumFaces()*3);

	//���ɶ��㷨��
	DWORD fvf = m_pMesh->GetFVF();
	if( (fvf&D3DFVF_NORMAL) == 0x0) //û�ж��㷨��
	{
		//��¡����
		m_pMesh->CloneMeshFVF(m_pMesh->GetOptions(), m_pMesh->GetFVF()|D3DFVF_NORMAL, g_pDevice, &m_pMeshNormal);
		
		m_pMesh->GenerateAdjacency( 0.001, &adjacencyInfo[0]);
		//���㶥�㷨��
		D3DXComputeNormals( m_pMeshNormal, &adjacencyInfo[0]);
	}

	//���ɽ�������
	int faceCount = m_pMesh->GetNumFaces();
	D3DXGeneratePMesh( m_pMesh, &adjacencyInfo[0], NULL, NULL, faceCount/10, D3DXMESHSIMP_FACE, &m_pProgressiveMesh);
	m_pMatrialBuffer->Release();
};

CXMesh::~CXMesh()
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
	if( m_pMeshNormal)
		m_pMeshNormal->Release();
	if( m_pProgressiveMesh)
		m_pProgressiveMesh->Release();
}

void CXMesh::useMesh()
{
	D3DXMATRIX worldMat;
	D3DXMatrixTranslation( &worldMat, 0.0f, 0.0f, 5.0f);  //����ת��Ϊ����
	g_pDevice->SetTransform( D3DTS_WORLD, &worldMat);  //������������λ��
	for( DWORD i=0; i<m_numOfMatrial; i++)
	{
		g_pDevice->SetMaterial( &m_pMeshMaterials[i]);	//���ò���
		g_pDevice->SetTexture( 0, m_pMeshTextures[i]);	//��������
		m_pMesh->DrawSubset( i);	//��Ⱦ����
	}

	worldMat;
	D3DXMatrixTranslation( &worldMat, 1.0f, 0.0f, 5.0f);  //����ת��Ϊ����
	g_pDevice->SetTransform( D3DTS_WORLD, &worldMat);  //������������λ��
	for( DWORD i=0; i<m_numOfMatrial; i++)
	{
		g_pDevice->SetMaterial( &m_pMeshMaterials[i]);	//���ò���
		g_pDevice->SetTexture( 0, m_pMeshTextures[i]);	//��������
		if( m_pMeshNormal)
		{
			m_pMeshNormal->DrawSubset( i);	//��Ⱦ����
		}
	}
}

void CXMesh::setProgressiveMesh( int Level /* = 10 */)
{
	int maxFace = m_pProgressiveMesh->GetMaxFaces();
	int minFace = m_pProgressiveMesh->GetMinFaces();
	int face = m_pProgressiveMesh->GetNumFaces();
	if( Level >= 10)
		m_pProgressiveMesh->SetNumFaces( m_pProgressiveMesh->GetMaxFaces());
	else if( Level <= 1)
		m_pProgressiveMesh->SetNumFaces( m_pProgressiveMesh->GetMinFaces());
	else
		m_pProgressiveMesh->SetNumFaces( m_pProgressiveMesh->GetMinFaces()*Level);
}

void CXMesh::showBoundingBox(bool isShow)
{
	if( isShow && m_pMesh)
	{
		BYTE* vertexBuff;
		D3DXVECTOR3 boxMin;
		D3DXVECTOR3 boxMax;
		ID3DXMesh* pBoxMesh;
		m_pMesh->LockVertexBuffer( 0, (void**)&vertexBuff);
		D3DXComputeBoundingBox( (D3DXVECTOR3*)vertexBuff, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &boxMin, &boxMax);//�����Χ��
		D3DXCreateBox( g_pDevice, boxMax.x - boxMin.x, boxMax.y - boxMin.y, boxMax.z - boxMin.z, &pBoxMesh, NULL);
		pBoxMesh->DrawSubset( 0);
	}
}

void CXMesh::showBoundingSphere( bool isShow)
{
	if( isShow && m_pMesh)
	{
		BYTE* vertexBuff;
		D3DXVECTOR3 center;
		float radius;
		ID3DXMesh* pSphereMesh;
		m_pMesh->LockVertexBuffer( 0, (void**)&vertexBuff);
		D3DXComputeBoundingSphere( (D3DXVECTOR3*)vertexBuff, m_pMesh->GetNumVertices(), m_pMesh->GetNumBytesPerVertex(), &center, &radius);//�����Χ��
		D3DXCreateSphere( g_pDevice, radius, 200, 5, &pSphereMesh, NULL);
		pSphereMesh->DrawSubset( 0);
	}
}