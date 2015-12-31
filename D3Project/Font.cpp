#include "Font.h"

CFont::CFont()
{
	D3DXFONT_DESC font;
	memset( &font, 0, sizeof(font));
	font.Height = 20;
	font.Width = 20;
	font.Weight = 500;
	font.Italic = false; //ÊÇ·ñÐ±Ìå
	font.CharSet = DEFAULT_CHARSET;
	font.OutputPrecision = 2;
	strcpy( font.FaceName, "Times New Roman");
	 
	D3DXCreateFontIndirect( g_pDevice, &font, &m_font);
}

CFont::~CFont()
{
	m_font->Release();
}

void CFont::drawText( char* str, RECT* rect, DWORD colour)
{
	m_font->DrawTextA( NULL, str, -1, rect,DT_TOP|DT_RIGHT, colour);
	return;
}