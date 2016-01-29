#include "Mirror.h"
#include "VertexDraw.h"

CMirror::CMirror()
{
	
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
	CVertexDraw::createMirrorSquare();

	//����������Ȼ����д�����Ӳ��ֱ�д����ģ�建����(1)���Ǿ��Ӳ���û��д��(0)
	g_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, true);

	//����ģ��ͨ��������Ϊ���Ӳ��֣������������Ⱦ����������
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_EQUAL); //ComparisionOption ģ��������
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); //����ͨ�������ı�ģ�建��

	//���㷴�����
	D3DXMATRIX W, T, R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXMatrixReflect(&R, &plane);

	D3DXMatrixTranslation(&T,
		0, 
		0,
		5.0); 

	W = T * R;

	//�����Ȼ��棨�����������Ⱦ�����ȴ󣬾��ӵ�ͼԪ��ѱ��������������ͼԪŪģ����
	g_pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	//��ϣ��ѱ���������(srcPix)��Ͻ�����(destPix)��
	g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO);

	//���Ʊ���������
	g_pDevice->SetTransform(D3DTS_WORLD, &W);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	mesh->useMeshNoTexture();

	//�ָ���Ⱦ״̬
	g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, false);
	g_pDevice->SetRenderState( D3DRS_STENCILENABLE, false);
	g_pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
}