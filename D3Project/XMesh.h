#pragma once
#include "base.h"

class CXMesh
{
public:
	CXMesh( char* fileName);
	~CXMesh();

	void useMesh();
	void useMeshNoTexture();

	void setProgressiveMesh( int Level = 10);

	void showBoundingBox( bool isShow);
	void showBoundingSphere( bool isShow);

	
private:
	ID3DXBuffer* m_pMatrialBuffer;

	DWORD m_numOfMatrial;

	ID3DXMesh* m_pMesh;
	ID3DXMesh* m_pMeshNormal; //带法线向量的网格
	ID3DXPMesh* m_pProgressiveMesh;//渐进网格

	D3DMATERIAL9* m_pMeshMaterials; //材质
	IDirect3DTexture9** m_pMeshTextures; //纹理
};