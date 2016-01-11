#pragma once
#include "base.h"

enum BlendType
{
	BlendType_Diffuse, //顶点(材质)混合
	BlendType_Texture, //纹理混合
};

class CXMesh
{
public:
	CXMesh( char* fileName);
	~CXMesh();

	void useMesh();

	void setProgressiveMesh( int Level = 10);

	void showBoundingBox( bool isShow);
	void showBoundingSphere( bool isShow);

	void setBlend( bool isUseBlend, BlendType type = BlendType_Diffuse); //混合

private:
	ID3DXBuffer* m_pMatrialBuffer;

	DWORD m_numOfMatrial;

	ID3DXMesh* m_pMesh;
	ID3DXMesh* m_pMeshNormal; //带法线向量的网格
	ID3DXPMesh* m_pProgressiveMesh;//渐进网格

	D3DMATERIAL9* m_pMeshMaterials; //材质
	IDirect3DTexture9** m_pMeshTextures; //纹理
};