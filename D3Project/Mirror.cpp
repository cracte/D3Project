#include "Mirror.h"

CMirror::CMirror()
{
	g_pDevice->SetRenderState( D3DRS_STENCILENABLE, true); //设置模板可用
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //模板测试总是成功 ComparisionOption
	g_pDevice->SetRenderState( D3DRS_STENCILREF, 0x1);//设置模板参考值 ref
	g_pDevice->SetRenderState( D3DRS_STENCILMASK, 0xffffffff); //设置模板掩码 mask
	g_pDevice->SetRenderState( D3DRS_STENCILWRITEMASK, 0xffffffff); //模板写掩码
	g_pDevice->SetRenderState( D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //像素模板测试失败，不改变模板缓存
	g_pDevice->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //像素深度测试失败，不改变模板缓存
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE); //都测试成功，用指定模板参考值替换模板缓存入口
}

CMirror::~CMirror()
{

}