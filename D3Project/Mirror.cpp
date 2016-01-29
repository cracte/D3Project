#include "Mirror.h"
#include "VertexDraw.h"

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z, 
		float nx, float ny, float nz,
		float u, float v)
	{
		_x  = x;  _y  = y;  _z  = z;
		_nx = nx; _ny = ny; _nz = nz;
		_u  = u;  _v  = v;
	}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;

	static const DWORD FVF;
};
const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

CMirror::CMirror()
{
	mat = new CMaterial( 0xfff0f0f0);
	texture = new CTexture( "ice.bmp");
	pVeretxBuffer = NULL;

	createMirrorSquare();
}

CMirror::~CMirror()
{

}

void CMirror::renderMirror( CXMesh* mesh)
{
	//����ģ�建�棬������Ⱦ״̬
	g_pDevice->SetRenderState( D3DRS_STENCILENABLE, true); //����ģ�����
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //ComparisionOption ģ��������ǳɹ� 
	g_pDevice->SetRenderState( D3DRS_STENCILREF, 0x1);//ref ����ģ��ο�ֵ 
	g_pDevice->SetRenderState( D3DRS_STENCILMASK, 0xffffffff); //mask ����ģ������ 
	g_pDevice->SetRenderState( D3DRS_STENCILWRITEMASK, 0xffffffff); //ģ��д����
	g_pDevice->SetRenderState( D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //����ģ�����ʧ�ܣ����ı�ģ�建��
	g_pDevice->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //������Ȳ���ʧ�ܣ����ı�ģ�建��
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE); //�����Գɹ�����ָ��ģ��ο�ֵ�滻ģ�建�����

	//��ֹд����Ȼ�����󻺴�
	g_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, false); //��ֹд��Ȼ���
	g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true); //�������
	g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO); //�󻺴�ֻ�о��Ӳ���
	g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	//��Ⱦ���ӽ�ģ�建��
	drawMirror();

	//����������Ȼ����д�����Ӳ��ֱ�д����ģ�建����(1)���Ǿ��Ӳ���û��д��(0)
	g_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, true);

	//����ģ��ͨ��������Ϊ���Ӳ��֣������������Ⱦ����������
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_EQUAL); //ComparisionOption ģ��������
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); //����ͨ�������ı�ģ�建��

	//���㷴�����
	D3DXMATRIX W, T, R;
	//D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXPLANE plane;
	D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(2.5f, 5.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, -1.0f));//���㾵��ƽ��
	D3DXMatrixReflect(&R, &plane);

	D3DXMatrixTranslation( &T, mesh->getPosition().x, mesh->getPosition().y, mesh->getPosition().z); 

	W = T * R;

	//�����Ȼ��棨�����������Ⱦ�����ȴ󣬾��ӵ�ͼԪ��ѱ��������������ͼԪŪģ����
	g_pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	//��ϣ��ѱ���������(srcPix)��Ͻ�����(destPix)��
	g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO);

	//���Ʊ���������
	g_pDevice->SetTransform(D3DTS_WORLD, &W);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	mesh->drawMesh();

	//�ָ���Ⱦ״̬
	g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState( D3DRS_STENCILENABLE, false);
	g_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
}

void CMirror::createMirrorSquare()
{
	if( FAILED( g_pDevice->CreateVertexBuffer( 6*sizeof(Vertex),
		0 , Vertex::FVF,
		D3DPOOL_DEFAULT, &pVeretxBuffer, NULL ) ) )
		return;

	Vertex* v = NULL;
	pVeretxBuffer->Lock( 0, 0, (void**)&v, 0);

	v[0] = Vertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex( 2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = Vertex(-2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = Vertex( 2.5f, 5.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = Vertex( 2.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	HRESULT hr = pVeretxBuffer->Unlock();
	hr = g_pDevice->SetStreamSource( 0, pVeretxBuffer, 0, sizeof(Vertex));
	hr = g_pDevice->SetFVF( Vertex::FVF);

	mat->useMaterial();
	texture->useTexture();
	hr = g_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2);
}

void CMirror::drawMirror()
{
	g_pDevice->SetStreamSource(0, pVeretxBuffer, 0, sizeof(Vertex));
	g_pDevice->SetFVF(Vertex::FVF);
	mat->useMaterial();
	texture->useTexture();
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	g_pDevice->SetTransform(D3DTS_WORLD, &I); //���þ���λ��
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}