#include "VertexDraw.h"



CVertexDraw::CVertexDraw()
{

}

CVertexDraw::~CVertexDraw()
{

}

void CVertexDraw::createVertex() //D3DFVF_XYZRHW 为固定在屏幕上的2D图形，左上角有坐标原点
{
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw; // The transformed position for the vertex.
		DWORD color;        // The vertex color.
	};

	static const DWORD FVF = (D3DFVF_XYZRHW|D3DFVF_DIFFUSE);

	CUSTOMVERTEX vertices[] =	//顶点
	{
		{ 10.0f,  250.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
		{ 250.0f, 250.0f, 0.5f, 1.0f, 0xff00ff00, },
		{  10.0f, 10.0f, 0.5f, 1.0f, 0xff0000ff, },
		{  250.0f, 10.0f, 0.5f, 1.0f, 0xff0000ff, },
	};

	WORD indices[] =	//索引，必须是逆时针，三个一组
	{
		0,2,1,1,2,3
	};

	IDirect3DVertexBuffer9* pVeretxBuffer = NULL;
	g_pDevice->CreateVertexBuffer( sizeof( vertices), 0, FVF, D3DPOOL_DEFAULT, &pVeretxBuffer, NULL);//创建顶点buff
	void* pVertices = NULL;
	pVeretxBuffer->Lock( 0, sizeof( vertices), &pVertices, 0);
	memcpy( pVertices, vertices, sizeof(vertices));//拷贝进内存
	pVeretxBuffer->Unlock();

	IDirect3DIndexBuffer9* pIndexBuffer = NULL;
	HRESULT hr = g_pDevice->CreateIndexBuffer( sizeof(indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIndexBuffer, NULL);
	void* pIndices = NULL;
	hr = pIndexBuffer->Lock( 0, sizeof(indices), &pIndices, 0);
	memcpy( pIndices, indices, sizeof(indices));
	hr = pIndexBuffer->Unlock();

	hr = g_pDevice->SetStreamSource( 0, pVeretxBuffer, 0, sizeof(CUSTOMVERTEX));//顶点流
	hr = g_pDevice->SetIndices( pIndexBuffer);//索引流

	hr = g_pDevice->SetFVF( FVF);//设置顶点格式

	//通过索引绘制图形
	hr = g_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, sizeof(vertices)/sizeof(CUSTOMVERTEX), 0, sizeof( indices)/sizeof(WORD)/3);
}

void CVertexDraw::createSquare()// D3DFVF_XYZ为3D图形, 区域中心为坐标原点
{
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z; 
		DWORD color; 
	};

	static const DWORD FVF = (D3DFVF_XYZ|D3DFVF_DIFFUSE);

	CUSTOMVERTEX vertices[] =	//顶点
	{
		{ 0.0f, 0.0f, 0.0f, 0xffff0000, }, // x, y, z, rhw, color
		{ 1.0f, 0.0f, 0.0f, 0xff00ff00, },
		{ 1.0f, 1.0f, 0.0f, 0xff0000ff, },
		{ 0.0f, 1.0f, 0.0f, 0xff0000ff, },
	};

	WORD indices[] =	//索引，必须是顺时针，三个一组
	{
		0,2,1,3,2,0
		//0,3,1,3,2,1
	};

	IDirect3DVertexBuffer9* pVeretxBuffer = NULL;
	g_pDevice->CreateVertexBuffer( sizeof( vertices), 0, FVF, D3DPOOL_DEFAULT, &pVeretxBuffer, NULL);//创建顶点buff
	void* pVertices = NULL;
	pVeretxBuffer->Lock( 0, sizeof( vertices), &pVertices, 0);
	memcpy( pVertices, vertices, sizeof(vertices));//拷贝进内存
	pVeretxBuffer->Unlock();

	IDirect3DIndexBuffer9* pIndexBuffer = NULL;
	HRESULT hr = g_pDevice->CreateIndexBuffer( sizeof(indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &pIndexBuffer, NULL);
	void* pIndices = NULL;
	hr = pIndexBuffer->Lock( 0, sizeof(indices), &pIndices, 0);
	memcpy( pIndices, indices, sizeof(indices));
	hr = pIndexBuffer->Unlock();

	hr = g_pDevice->SetStreamSource( 0, pVeretxBuffer, 0, sizeof(CUSTOMVERTEX));//顶点流
	hr = g_pDevice->SetIndices( pIndexBuffer);//索引流

	hr = g_pDevice->SetFVF( FVF);//设置顶点格式
	g_pDevice->SetRenderState( D3DRS_LIGHTING, false); //开启灯光

	//通过索引绘制图形
	hr = g_pDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, sizeof(vertices)/sizeof(CUSTOMVERTEX), 0, sizeof( indices)/sizeof(WORD)/3);
}

void CVertexDraw::createCylinder()
{
	struct CUSTOMVERTEX
	{

		D3DXVECTOR3 position; // The 3D position for the vertex.
		D3DXVECTOR3 normal;   // The surface normal for the vertex.
		FLOAT tu, tv;
	};
	static const DWORD FVF = (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1);

	IDirect3DVertexBuffer9* pVeretxBuffer = NULL;
	if( FAILED( g_pDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
		0 , FVF,
		D3DPOOL_DEFAULT, &pVeretxBuffer, NULL ) ) )
		return;

	CUSTOMVERTEX* pVertices = NULL;
	pVeretxBuffer->Lock( 0, 0, (void**)&pVertices, 0);

	for( DWORD i=0; i<50; i++ )
	{
		FLOAT theta = (2*D3DX_PI*i)/(50-1);
		pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
		pVertices[2*i+0].tu       = ((FLOAT)i)/(50-1);
		pVertices[2*i+0].tv       = 1.0f;
		pVertices[2*i+0].normal   = D3DXVECTOR3( sinf(theta), 0.0f, cosf(theta) );
		pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
		pVertices[2*i+1].normal   = D3DXVECTOR3( sinf(theta), 0.0f, cosf(theta) );
		pVertices[2*i+1].tu       = ((FLOAT)i)/(50-1);
		pVertices[2*i+1].tv       = 0.0f;
	}
	HRESULT hr = pVeretxBuffer->Unlock();
	hr = g_pDevice->SetStreamSource( 0, pVeretxBuffer, 0, sizeof(CUSTOMVERTEX));
	hr = g_pDevice->SetFVF( FVF);
	hr = g_pDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2);
}