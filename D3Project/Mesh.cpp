#include "Mesh.h"

#define FLOAT_EPSILON 0.0001f

CMesh::CMesh()
{
	D3DXCreateMeshFVF( m_numFaces, m_numVertices, m_options, m_FVF, g_pDevice, &m_pMesh);

	//���㻺��
	m_pMesh->LockVertexBuffer( 0, (void**)&m_pVertexData);
	//
	//���㻺������
	//
	m_pMesh->UnlockVertexBuffer();

	//�滺��
	m_pMesh->LockIndexBuffer( 0, (void**)&m_pFaceData);
	//
	//�滺������
	//
	m_pMesh->UnlockIndexBuffer();

	//���Ի���,ָ���Ӽ�
	DWORD* pAttributesData;
	m_pMesh->LockAttributeBuffer( 0, &pAttributesData);
	m_pMesh->UnlockAttributeBuffer();
	
	//��ȡ�ڽ���Ϣ
	//std::vector<DWORD> adjacencyInfo( m_numFaces*3);
	m_pMesh->GenerateAdjacency(FLOAT_EPSILON, &m_adjacencyInfo[0]);

	//�Ż�
	DWORD optimizeFlag = D3DXMESHOPT_COMPACT|D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE;
	m_pMesh->OptimizeInplace( optimizeFlag, &m_adjacencyInfo[0], 0, 0, 0);
}

CMesh::~CMesh()
{

}

void CMesh::drawMesh()
{
	for( int i=0; i<m_subsetCount; ++i)
	{
		m_pMesh->DrawSubset( i);
	}
}