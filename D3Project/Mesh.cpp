#include "Mesh.h"

#define FLOAT_EPSILON 0.0001f

CMesh::CMesh()
{
	D3DXCreateMeshFVF( m_numFaces, m_numVertices, m_options, m_FVF, g_pDevice, &m_pMesh);

	//顶点缓存
	m_pMesh->LockVertexBuffer( 0, (void**)&m_pVertexData);
	//
	//顶点缓存数据
	//
	m_pMesh->UnlockVertexBuffer();

	//面缓存
	m_pMesh->LockIndexBuffer( 0, (void**)&m_pFaceData);
	//
	//面缓存数据
	//
	m_pMesh->UnlockIndexBuffer();

	//属性缓存,指定子集
	DWORD* pAttributesData;
	m_pMesh->LockAttributeBuffer( 0, &pAttributesData);
	m_pMesh->UnlockAttributeBuffer();
	
	//获取邻接信息
	//std::vector<DWORD> adjacencyInfo( m_numFaces*3);
	m_pMesh->GenerateAdjacency(FLOAT_EPSILON, &m_adjacencyInfo[0]);

	//优化
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