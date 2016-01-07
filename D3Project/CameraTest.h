#pragma once
#include "base.h"

class CameraTest
{
public:
	CameraTest();

	~CameraTest();

	void move( float xPos = 0.0f, float zPos = 0.0f);

	void fly( float yPos = 0.0f);

	void rotate( float x, float z);
	void rotateX( float x);
	void rotateZ( float x);
	void setProjectMatrix();

private:

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_up;
};