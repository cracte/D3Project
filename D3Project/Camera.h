#pragma once
#include "base.h"

class Camera
{
public:
	Camera();

	~Camera();

	void move( float xPos = 0.0f, float zPos = 0.0f);

	void fly( float yPos = 0.0f);

	void rotate( float x, float z);
	void rotateX( float x);
	void rotateZ( float x);

private:

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_up;
};