#pragma once
#include "base.h"

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	FLOAT tu, tv;
};

struct Faces
{
	DWORD index1, index2, index3;
};

class CMesh
{
public:
	CMesh();
	~CMesh();

	void drawMesh();

private:
	DWORD m_numFaces; //三角形数量
	DWORD m_numVertices; //顶点数量
	DWORD m_FVF;
	DWORD m_options;
	DWORD m_subsetCount; //子集数量

	Vertex* m_pVertexData; //顶点缓存
	Faces* m_pFaceData; //面缓存
	std::vector<DWORD> m_adjacencyInfo; //邻接信息

	ID3DXMesh* m_pMesh;//网格信息

	std::vector<D3DXMATERIAL> m_materialInfo;//材质信息
};