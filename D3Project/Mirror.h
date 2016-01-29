#pragma once
#include "base.h"
#include "XMesh.h"
#include "Material.h"
#include "Texture.h"

class CMirror
{
public:
	CMirror();
	~CMirror();

	void renderMirror( CXMesh* mesh);
	void createMirrorSquare();
	void drawMirror();

private:
	CMaterial* mat;
	CTexture* texture;

	IDirect3DVertexBuffer9* pVeretxBuffer;
};