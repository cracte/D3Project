#pragma once
#include "base.h"

class CXMesh
{
public:
	CXMesh( char* fileName);
	~CXMesh();

	void useMesh();

	void setProgressiveMesh( int Level = 10);

	void showBoundingBox( bool isShow);
	void showBoundingSphere( bool isShow);
	void setPosition( float x, float y, float z);
	D3DXVECTOR3 getPosition(){ return m_position; }
	void drawMesh();
	
private:
	ID3DXBuffer* m_pMatrialBuffer;

	DWORD m_numOfMatrial;

	ID3DXMesh* m_pMesh;
	ID3DXMesh* m_pMeshNormal; //����������������
	ID3DXPMesh* m_pProgressiveMesh;//��������

	D3DMATERIAL9* m_pMeshMaterials; //����
	IDirect3DTexture9** m_pMeshTextures; //����

	D3DXVECTOR3 m_position;
};