#pragma once
#include "base.h"

class CFont
{
public:
	CFont();
	~CFont();

	void drawText( char* str, RECT* rect, DWORD colour = 0xff000000);

private:
	ID3DXFont* m_font;
};