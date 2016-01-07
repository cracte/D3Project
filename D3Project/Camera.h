#pragma once
#include "base.h"

class Camera
{
public:
	Camera();
	~Camera();

	void setProjectMatrix();

	void walk( float units);
	void strafe( float units);
	void fly( float units);

	void pitch( float angle);
	void yaw( float angle);
	void roll( float angle);

	void setPosition( D3DXVECTOR3* pos);

	void move( float x, float z);
	void rotate( float x, float y);

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;

	void getViewMatrix( D3DXMATRIX* view);
};