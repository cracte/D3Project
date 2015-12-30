#include "Win.h"
#include "Common.h"
#include <Windows.h>

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
IDirect3D9* g_pD3Direct = NULL;
IDirect3DDevice9* g_pDevice = NULL;
RECT g_winRect = { 0, 0, 640, 480};

HRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if( hWnd == g_hWnd)
		return CWin::instance().WndProcMsg( message, wParam, lParam);
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}

CWin::CWin():
m_lastTime(0),
m_fpsTime(0.0f),
m_fpsCount( 0)
{
	InitWindow();
	initD3();

	// Main message loop
	MSG msg = {0};
	camera = new Camera;
	mesh = new CMesh( "tiger.x");
	light = new CLight;
	light->useLight();
	while( WM_QUIT != msg.message )
	{
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if( m_lastTime <= 0)
				m_lastTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			float deltaTime = ( nowTime - m_lastTime)/1000.0f;
			render( deltaTime);
			m_lastTime = timeGetTime();
		}
	}

	cleanUp();
}

CWin::~CWin()
{

}

bool CWin::InitWindow( )
{
	HINSTANCE hInstance = GetModuleHandle( NULL );
	// Register class
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, "");
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "className";
	wcex.hIconSm = LoadIcon( wcex.hInstance, "");
	if( !RegisterClassEx( &wcex ) )
		return false;

	// Create window
	g_hInst = hInstance;
	RECT rc = g_winRect;
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
	g_hWnd = CreateWindow( "className", "windowName", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
		NULL );
	if( !g_hWnd )
		return false;

	ShowWindow( g_hWnd, SW_SHOW);
	m_lastPoint.x = 0;
	m_lastPoint.y = 0;

	return true;
}

HRESULT CWin::WndProcMsg( UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( g_hWnd, &ps );
		EndPaint( g_hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_KEYDOWN:
		keyDown( wParam);
		break;
	case WM_RBUTTONDOWN:
		{
			//m_btnDownPoint = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
			m_btnDownPoint.x = (short)LOWORD(lParam);
			m_btnDownPoint.y = (short)HIWORD(lParam);
			m_isBtnDown = true;
		}
		break;
	case WM_MOUSEMOVE:
		{
			//camera->rotate( point.x - m_lastPoint.x, point.y - m_lastPoint.y);
			//camera->rotate( point.x, 10);
			//char str[512];
			//sprintf( str, "%d, %d\n", point.x, point.y);
			//OutputDebugString( str);
			if( m_isBtnDown)
			{
				POINT point = {(short)LOWORD(lParam), (short)HIWORD(lParam)};
				//camera->rotate( point.x - m_btnDownPoint.x, point.y - m_btnDownPoint.y);
				camera->rotateX( point.x - m_btnDownPoint.x);
				camera->rotateZ( point.y - m_btnDownPoint.y);
				m_btnDownPoint.x = point.x;
				m_btnDownPoint.y = point.y;
			}
		}
		break;
	case WM_RBUTTONUP:
		{
			m_isBtnDown = false;
		}
		break;

	default:
		return DefWindowProc( g_hWnd, message, wParam, lParam );
	}

	return 0;
}

bool CWin::initD3()
{
	g_pD3Direct = Direct3DCreate9( D3D_SDK_VERSION);
	if( g_pD3Direct == NULL)
		return false;

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	HRESULT hr = g_pD3Direct->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	if( FAILED( hr))
		return false;
	return true;
}

bool CWin::cleanUp()
{
	if( !g_pDevice)
		return false;
	g_pDevice->Release();
	g_pD3Direct->Release();
	return true;
}

bool CWin::keyDown( WPARAM wParam)
{
	if( wParam == 'A')
	{
		camera->move( -0.1f, 0.0f);
	}
	if( wParam == 'D')
	{
		camera->move( 0.1f, 0.0f);
	}
	if( wParam == 'W')
	{
		camera->move( 0.0f, 0.1f);
	}
	if( wParam == 'S')
	{
		camera->move( 0.0f, -0.1f);
	}
	return true;
}

void CWin::render( float dt)
{
	time_t nowTime;
	time( &nowTime);
	calcFPS( dt);
	//static SYSTEMTIME time;
	//time_t lastTime = mktime( time);
	//GetLocalTime( &time);
	//time_t timeNow = mktime( time);
	//float deltaTime = timeNow - lastTime;

	if( !g_pDevice)
		return;
	g_pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);

	if(SUCCEEDED( g_pDevice->BeginScene()))
	{
		//CVertexDraw::createVertex();
		//CLight light;
		//light.setLight();
		//CMaterial mat;
		//mat.setMaterial();

		//CVertexDraw::createCylinder();
		//CTexture texture;
		//texture.setTexture();
		//camera->move( 0.01);
		mesh->useMesh();
		//g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//������Ⱦģʽ
		g_pDevice->EndScene();
	}

	g_pDevice->Present( NULL, NULL, NULL, NULL);
}

void CWin::calcFPS( float dt)
{
	m_fpsTime += dt;
	m_fpsCount++;
	if( m_fpsTime >= 1.0f)
	{
		m_fpsTime = 0.0f;
		m_fpsCount = 0;

		float fps = m_fpsCount/m_fpsTime;
		Log( "fps == %f", fps);
	}
	RECT winRect;
	GetWindowRect( g_hWnd, &winRect);
	RECT rect;
	rect.right = g_winRect.right;
	rect.top = g_winRect.bottom;
	rect.left = rect.right - 100;
	rect.bottom = rect.top - 100;
	CFont font;
	font.drawText( "dfeafed", &rect);
}