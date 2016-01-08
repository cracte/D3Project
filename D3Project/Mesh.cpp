#include "Mesh.h"

#define FLOAT_EPSILON 0.0001f

CMesh::CMesh()
{
	m_numVertices = 24;
	m_numFaces = 12;
	m_options = D3DXMESH_MANAGED;
	m_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	m_pMesh = NULL;
	m_subsetCount = 3;
	sprintf( m_textureFile, "%s", "banana.bmp");

	D3DXCreateMeshFVF( m_numFaces, m_numVertices, m_options, m_FVF, g_pDevice, &m_pMesh);

	//顶点缓存
	m_pMesh->LockVertexBuffer( 0, (void**)&m_pVertexData);
	//
	//顶点缓存数据
	//
	// fill in the front face vertex data
	m_pVertexData[0] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	m_pVertexData[1] = Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	m_pVertexData[2] = Vertex( 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	m_pVertexData[3] = Vertex( 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	// fill in the back face vertex data
	m_pVertexData[4] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	m_pVertexData[5] = Vertex( 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	m_pVertexData[6] = Vertex( 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	m_pVertexData[7] = Vertex(-1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// fill in the top face vertex data
	m_pVertexData[8]  = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	m_pVertexData[9]  = Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	m_pVertexData[10] = Vertex( 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	m_pVertexData[11] = Vertex( 1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	// fill in the bottom face vertex data
	m_pVertexData[12] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	m_pVertexData[13] = Vertex( 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	m_pVertexData[14] = Vertex( 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	m_pVertexData[15] = Vertex(-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// fill in the left face vertex data
	m_pVertexData[16] = Vertex(-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	m_pVertexData[17] = Vertex(-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	m_pVertexData[18] = Vertex(-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	m_pVertexData[19] = Vertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// fill in the right face vertex data
	m_pVertexData[20] = Vertex( 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	m_pVertexData[21] = Vertex( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	m_pVertexData[22] = Vertex( 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	m_pVertexData[23] = Vertex( 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	m_pMesh->UnlockVertexBuffer();

	//面缓存
	m_pMesh->LockIndexBuffer( 0, (void**)&m_pFaceData);
	//
	//面缓存数据
	//
	// fill in the front face index data
	m_pFaceData[0] = Faces( 0, 1, 2);
	m_pFaceData[1] = Faces( 0, 2, 3);

	// fill in the back face index data
	m_pFaceData[2] = Faces( 4, 5, 6);
	m_pFaceData[3] = Faces( 4, 6, 7);

	// fill in the top face index data
	m_pFaceData[4] = Faces( 8, 9, 10);
	m_pFaceData[5] = Faces( 8, 10, 11);

	// fill in the bottom face index data
	m_pFaceData[6] = Faces( 12, 13, 14);
	m_pFaceData[7] = Faces( 12, 14, 15);

	// fill in the left face index data
	m_pFaceData[8] = Faces( 16, 17, 18);
	m_pFaceData[9] = Faces( 16, 18, 19);

	// fill in the right face index data
	m_pFaceData[10] = Faces( 20, 21, 22);
	m_pFaceData[11] = Faces( 20, 22, 23);
	m_pMesh->UnlockIndexBuffer();

	//属性缓存,指定子集
	DWORD* pAttributesData;
	m_pMesh->LockAttributeBuffer( 0, &pAttributesData);
	for(int a = 0; a < 3; a++)
		pAttributesData[a] = 0;
	for(int b = 4; b < 8; b++)
		pAttributesData[b] = 1;
	for(int c = 8; c < 12; c++)
		pAttributesData[c] = 2;
	m_pMesh->UnlockAttributeBuffer();
	
	//获取邻接信息
	std::vector<DWORD> adjacencyInfo( m_numFaces*3);
	m_pMesh->GenerateAdjacency(FLOAT_EPSILON, &adjacencyInfo[0]);
	for( size_t i=0; i<adjacencyInfo.size(); ++i)
	{
		m_adjacencyInfo.push_back( adjacencyInfo[i]);
	}

	//优化
	DWORD optimizeFlag = D3DXMESHOPT_COMPACT|D3DXMESHOPT_ATTRSORT|D3DXMESHOPT_VERTEXCACHE;
	m_pMesh->OptimizeInplace( optimizeFlag, &m_adjacencyInfo[0], 0, 0, 0);

	//纹理
	char pathName[512];
	sprintf( pathName, "../Resource/Texture/%s", m_textureFile);
	HRESULT hr = D3DXCreateTextureFromFile( g_pDevice, pathName, &m_pTexture);

	//设置材质,有灯光就必须有材质，否则灯光被完全吸收，不会显示纹理
	m_material.Ambient = D3DXCOLOR( 0xffffffff);
	m_material.Diffuse = D3DXCOLOR( 0xffffffff);
	m_material.Emissive = D3DXCOLOR( 0xffffffff);
	m_material.Specular = D3DXCOLOR( 0xffffffff);
	m_material.Power = 50;
}

CMesh::~CMesh()
{

}

void CMesh::drawMesh()
{
	for( int i=0; i<m_subsetCount; ++i)
	{
		g_pDevice->SetTexture( 0, m_pTexture);
		g_pDevice->SetMaterial( &m_material);
		m_pMesh->DrawSubset( i);
	}
}