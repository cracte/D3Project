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
	DWORD m_numFaces; //����������
	DWORD m_numVertices; //��������
	DWORD m_FVF;
	DWORD m_options;
	DWORD m_subsetCount; //�Ӽ�����

	Vertex* m_pVertexData; //���㻺��
	Faces* m_pFaceData; //�滺��
	std::vector<DWORD> m_adjacencyInfo; //�ڽ���Ϣ

	ID3DXMesh* m_pMesh;//������Ϣ

	std::vector<D3DXMATERIAL> m_materialInfo;//������Ϣ
};