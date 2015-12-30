#include "Camera.h"

#define CAMERA_ROTATE_DISTANCE 100		//摄像机旋转360度，鼠标移动距离

Camera::Camera()
{
	//D3DXMatrixRotationAxis();
	//D3DXMatrixLookAtLH();
	//D3DXMatrixPerspectiveFovLH();
	m_position = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);//摄像机位置
	m_look = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);//摄像机视野方向
	m_up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);//视野正方形
	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_position, &m_look, &m_up);
	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);  //设置视野坐标

	D3DXMATRIX projectMateral;
	float fovy = D3DX_PI/4;//视野夹角，眼睛上下距离能看见的夹角
	float aspect = (g_winRect.right-g_winRect.left)/(g_winRect.bottom-g_winRect.top);  //窗口宽高比
	float zn = 1.0f; //前裁剪距离,摄像机最近视野
	float zf = 100.0f; //后裁剪距离，摄像机最大视野范围
	D3DXMatrixPerspectiveFovLH(&projectMateral, fovy, aspect, zn, zf);
	g_pDevice->SetTransform( D3DTS_PROJECTION, &projectMateral);  //设置投影坐标
}

Camera::~Camera()
{

} 

void Camera::move( float xPos, float zPos)
{
	//视野变换为摄像机移动，可以理解为世界变换的逆运算
	m_position.x -= xPos;
	m_look.x -= xPos;
	m_position.z -= zPos;
	m_look.z -= zPos;
	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_look, &m_position, &m_up);
	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);
}

void Camera::fly( float yPos /* = 0.0f */)
{
	m_position.y -= yPos;
	m_look.y -= yPos;
	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_look, &m_position, &m_up);
	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);
}

void Camera::rotateX( float x)
{
	D3DXMATRIX outMateral;
	float angleX = x/CAMERA_ROTATE_DISTANCE * D3DX_PI;
	D3DXVECTOR3 loolNormal;
	D3DXVec3Normalize( &loolNormal, &m_look);
	D3DXVECTOR3 xAxis = D3DXVECTOR3( loolNormal.x, 0.0f, 0.0f);
	D3DXMatrixRotationAxis( &outMateral, &xAxis, angleX);
	D3DXVec3TransformCoord( &m_look, &m_look, &outMateral);

	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_position, &m_look, &m_up);

	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);
}

void Camera::rotateZ( float z)
{
	D3DXMATRIX outMateral;
	float angleZ = z/CAMERA_ROTATE_DISTANCE * D3DX_PI;
	D3DXVECTOR3 loolNormal;
	D3DXVec3Normalize( &loolNormal, &m_look);
	D3DXVECTOR3 xAxis = D3DXVECTOR3( 0.0f, 0.0f, loolNormal.z);
	D3DXMatrixRotationAxis( &outMateral, &xAxis, angleZ);
	D3DXVec3TransformCoord( &m_look, &m_look, &outMateral);

	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_position, &m_look, &m_up);

	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);
}

void Camera::rotate(float x, float z)
{
	D3DXMATRIX outMateral;
	float angleX = x/CAMERA_ROTATE_DISTANCE * D3DX_PI;
	float angleZ = z/CAMERA_ROTATE_DISTANCE * D3DX_PI;
	D3DXVECTOR3 loolNormal;
	D3DXVec3Normalize( &loolNormal, &m_look);
	D3DXVECTOR3 xAxis = D3DXVECTOR3( loolNormal.x, 0.0f, 0.0f);
	D3DXVECTOR3 zAxis = D3DXVECTOR3( 0.0f, 0.0f, loolNormal.z);
	//D3DXMatrixRotationAxis( &outMateral, &xAxis, angleX);
	//D3DXMatrixRotationAxis( &outMateral, &xAxis, angleX);
	float angle = (x*x + z*z)/(CAMERA_ROTATE_DISTANCE*CAMERA_ROTATE_DISTANCE) * D3DX_PI;
	D3DXVECTOR3 lookRotate;
	lookRotate.x = m_look.x + x/CAMERA_ROTATE_DISTANCE;
	lookRotate.y = m_look.y;
	lookRotate.z = m_look.z + z/CAMERA_ROTATE_DISTANCE;

	D3DXVECTOR3 v1 = m_look - m_position;
	D3DXVECTOR3 v2 = lookRotate - m_position;
	D3DXVECTOR3 axis;
	D3DXVec3Cross( &axis, &v1, &v2);
	D3DXMatrixRotationAxis( &outMateral, &axis, angle);
	
	D3DXVec3TransformCoord( &m_look, &m_look, &outMateral);
	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_position, &m_look, &m_up);

	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);
	//m_look = lookRotate;
}