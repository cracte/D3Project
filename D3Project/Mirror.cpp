#include "Mirror.h"

CMirror::CMirror()
{
	g_pDevice->SetRenderState( D3DRS_STENCILENABLE, true); //����ģ�����
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //ģ��������ǳɹ� ComparisionOption
	g_pDevice->SetRenderState( D3DRS_STENCILREF, 0x1);//����ģ��ο�ֵ ref
	g_pDevice->SetRenderState( D3DRS_STENCILMASK, 0xffffffff); //����ģ������ mask
	g_pDevice->SetRenderState( D3DRS_STENCILWRITEMASK, 0xffffffff); //ģ��д����
	g_pDevice->SetRenderState( D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //����ģ�����ʧ�ܣ����ı�ģ�建��
	g_pDevice->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //������Ȳ���ʧ�ܣ����ı�ģ�建��
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE); //�����Գɹ�����ָ��ģ��ο�ֵ�滻ģ�建�����
}

CMirror::~CMirror()
{

}