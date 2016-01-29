#include "Camera.h"

Camera::Camera()
{
	m_position = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
	m_right = D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
	m_up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
	m_look = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);

	D3DXMATRIX viewMatrix;
	getViewMatrix( &viewMatrix);
	g_pDevice->SetTransform( D3DTS_VIEW, &viewMatrix);

	setProjectMatrix();
}

Camera::~Camera()
{

}

void Camera::setProjectMatrix()
{
	D3DXMATRIX projectMateral;
	float fovy = D3DX_PI/4;//视野夹角，眼睛上下距离能看见的夹角
	float aspect = winWidth/winHigh;  //窗口宽高比
	float zn = 0.0f; //前裁剪距离,摄像机最近视野
	float zf = 1000.0f; //后裁剪距离，摄像机最大视野范围
	D3DXMatrixPerspectiveFovLH(&projectMateral, fovy, aspect, zn, zf);
	g_pDevice->SetTransform( D3DTS_PROJECTION, &projectMateral);  //设置投影坐标
}

void Camera::getViewMatrix( D3DXMATRIX* view)
{
	//保持摄像头视野正交
	D3DXVec3Normalize( &m_look, &m_look);

	D3DXVec3Cross( &m_up, &m_look, &m_right);
	D3DXVec3Normalize( &m_up, &m_up);

	D3DXVec3Cross( &m_right, &m_up, &m_look);
	D3DXVec3Normalize( &m_right, &m_right);

	float x = -D3DXVec3Dot( &m_right, &m_position);
	float y = -D3DXVec3Dot( &m_up, &m_position);
	float z = -D3DXVec3Dot( &m_look, &m_position);

	(*view)._11 = m_right.x; (*view)._12 = m_up.x; (*view)._13 = m_look.x; (*view)._14 = 0.0f;
	(*view)._21 = m_right.y; (*view)._22 = m_up.y; (*view)._23 = m_look.y; (*view)._24 = 0.0f;
	(*view)._31 = m_right.z; (*view)._32 = m_up.z; (*view)._33 = m_look.z; (*view)._34 = 0.0f;
	(*view)._41 = x; (*view)._42 = y; (*view)._43 = z; (*view)._44 = 1.0f;
}

void Camera::walk(float units)
{
	m_position += m_look * units;
}

void Camera::strafe(float units)
{
	m_position += m_right * units;
}

void Camera::fly(float units)
{
	m_position += m_up * units;
}

void Camera::pitch(float angle)
{
	D3DXMATRIX t;
	D3DXMatrixRotationAxis( &t, &m_right, angle);

	D3DXVec3TransformCoord( &m_look, &m_look, &t);
	D3DXVec3TransformCoord( &m_up, &m_up, &t);
}

void Camera::yaw( float angle)
{
	D3DXMATRIX t;
	D3DXMatrixRotationAxis( &t, &m_up, angle);

	D3DXVec3TransformCoord( &m_right, &m_right, &t);
	D3DXVec3TransformCoord( &m_look, &m_look, &t);
}

void Camera::roll(float angle)
{
	D3DXMATRIX t;
	D3DXMatrixRotationAxis( &t, &m_look, angle);

	D3DXVec3TransformCoord( &m_right, &m_right, &t);
	D3DXVec3TransformCoord( &m_up, &m_up, &t);
}

void Camera::setPosition( D3DXVECTOR3* pos)
{
	m_position = *pos;

	D3DXMATRIX viewMatrix;
	getViewMatrix( &viewMatrix);
	g_pDevice->SetTransform( D3DTS_VIEW, &viewMatrix);
}

void Camera::move( float x, float z)
{
	D3DXMATRIX viewMatrix;
	strafe( x);
	walk( z);
	getViewMatrix( &viewMatrix);

	g_pDevice->SetTransform( D3DTS_VIEW, &viewMatrix);
}

void Camera::rotate(float x, float y)
{
	D3DXMATRIX viewMatrix;
	yaw( x);
	pitch( y);
	getViewMatrix( &viewMatrix);

	g_pDevice->SetTransform( D3DTS_VIEW, &viewMatrix);
}