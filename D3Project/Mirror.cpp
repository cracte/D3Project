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
	//开启模板缓存，设置渲染状态
	g_pDevice->SetRenderState( D3DRS_STENCILENABLE, true); //设置模板可用
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //ComparisionOption 模板测试总是成功 
	g_pDevice->SetRenderState( D3DRS_STENCILREF, 0x1);//ref 设置模板参考值 
	g_pDevice->SetRenderState( D3DRS_STENCILMASK, 0xffffffff); //mask 设置模板掩码 
	g_pDevice->SetRenderState( D3DRS_STENCILWRITEMASK, 0xffffffff); //模板写掩码
	g_pDevice->SetRenderState( D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //像素模板测试失败，不改变模板缓存
	g_pDevice->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //像素深度测试失败，不改变模板缓存
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE); //都测试成功，用指定模板参考值替换模板缓存入口

	//阻止写入深度缓存与后缓存
	g_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, false); //阻止写深度缓存
	g_pDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, true); //开启混合
	g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO); //后缓存只有镜子部分
	g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);

	//渲染镜子进模板缓存
	drawMirror();

	//重新设置深度缓存可写，镜子部分被写入了模板缓存中(1)，非镜子部分没被写入(0)
	g_pDevice->SetRenderState( D3DRS_ZWRITEENABLE, true);

	//测试模板通过的区域为镜子部分，该区域可以渲染反射物体了
	g_pDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_EQUAL); //ComparisionOption 模板测试相等
	g_pDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); //测试通过，不改变模板缓存

	//计算反射矩阵
	D3DXMATRIX W, T, R;
	//D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
	D3DXPLANE plane;
	D3DXPlaneFromPointNormal( &plane, &D3DXVECTOR3(2.5f, 5.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, -1.0f));//计算镜子平面
	D3DXMatrixReflect(&R, &plane);

	D3DXMatrixTranslation( &T, mesh->getPosition().x, mesh->getPosition().y, mesh->getPosition().z); 

	W = T * R;

	//清除深度缓存（被反射的物体比镜子深度大，镜子的图元会把被反射物体物体的图元弄模糊）
	g_pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	//混合，把被反射物体(srcPix)混合进镜子(destPix)中
	g_pDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	g_pDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO);

	//绘制被反射物体
	g_pDevice->SetTransform(D3DTS_WORLD, &W);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	mesh->drawMesh();

	//恢复渲染状态
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
	g_pDevice->SetTransform(D3DTS_WORLD, &I); //设置镜子位置
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}