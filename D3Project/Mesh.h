#pragma once
#include "base.h"

class CMesh
{
public:
	CMesh( char* fileName);
	~CMesh();

	void useMesh();

private:
	ID3DXBuffer* m_pMatrialBuffer;

	DWORD m_numOfMatrial;
	ID3DXMesh* m_pMesh;

	D3DMATERIAL9* m_pMeshMaterials;
	IDirect3DTexture9** m_pMeshTextures;
};