#include "Camera.h"

#define CAMERA_ROTATE_DISTANCE 100		//�������ת360�ȣ�����ƶ�����

Camera::Camera()
{
	//D3DXMatrixRotationAxis();
	//D3DXMatrixLookAtLH();
	//D3DXMatrixPerspectiveFovLH();
	m_position = D3DXVECTOR3( 0.0f, 0.0f, 0.0f);//�����λ��
	m_look = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);//�������Ұ����
	m_up = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);//��Ұ������
	D3DXMATRIX viewMateral;
	D3DXMatrixLookAtLH( &viewMateral, &m_position, &m_look, &m_up);
	g_pDevice->SetTransform( D3DTS_VIEW, &viewMateral);  //������Ұ����

	D3DXMATRIX projectMateral;
	float fovy = D3DX_PI/4;//��Ұ�нǣ��۾����¾����ܿ����ļн�
	float aspect = (g_winRect.right-g_winRect.left)/(g_winRect.bottom-g_winRect.top);  //���ڿ�߱�
	float zn = 1.0f; //ǰ�ü�����,����������Ұ
	float zf = 100.0f; //��ü����룬����������Ұ��Χ
	D3DXMatrixPerspectiveFovLH(&projectMateral, fovy, aspect, zn, zf);
	g_pDevice->SetTransform( D3DTS_PROJECTION, &projectMateral);  //����ͶӰ����
}

Camera::~Camera()
{

} 

void Camera::move( float xPos, float zPos)
{
	//��Ұ�任Ϊ������ƶ����������Ϊ����任��������
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