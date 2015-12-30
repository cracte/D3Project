#include "base.h"
#include "VertexDraw.h"
#include "Material.h"
#include "Light.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;
IDirect3D9* g_pD3Direct = NULL;
IDirect3DDevice9* g_pDevice = NULL;

Camera* camera = NULL;
CMesh* mesh = NULL;
CLight* light = NULL;
