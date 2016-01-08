#pragma once
#include "base.h"

struct Vertex
{
	//D3DXVECTOR3 position;
	//D3DXVECTOR3 normal;
	float pos_x, pos_y, pos_z;
	float normal_x, normal_y, normal_z;
	FLOAT tu, tv;
	Vertex( float x, float y, float z, float nx, float ny, float nz, float u, float v)
	{
		pos_x = x; pos_y = y; pos_z = z;
		normal_x = nx; normal_y = ny; normal_z = nz;
		tu = u; tv = v;
	}
};

struct Faces
{
	DWORD index1, index2, index3;
	Faces( DWORD i1, DWORD i2, DWORD i3)
	{
		index1 = i1; index2 = i2; index3 = i3;
	}
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

	IDirect3DTexture9* m_pTexture;
	char m_textureFile[512];

	D3DMATERIAL9 m_material;
};