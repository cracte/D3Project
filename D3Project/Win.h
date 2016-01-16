#pragma once
#include "base.h"
#include "VertexDraw.h"
#include "Material.h"
#include "Light.h"
#include "Texture.h"
#include "XMesh.h"
#include "Camera.h"
#include "Font.h"
#include "Mesh.h"

class CWin
{
public:
	CWin();
	~CWin();

	static CWin& instance()
	{
		static CWin win;
		return win;
	}

	HRESULT WndProcMsg( UINT message, WPARAM wParam, LPARAM lParam );

	bool keyDown( WPARAM wParam);

private:

	bool InitWindow();

	bool initD3();

	bool cleanUp();

	void render( float dt);
	void calcFPS( float dt);

	Camera* camera;
	CXMesh* mesh;
	CLight* light;

	POINT m_lastPoint;
	POINT m_btnDownPoint;
	bool m_isBtnDown;

	DWORD m_lastTime;

	float m_fpsTime;
	int m_fpsCount;
};