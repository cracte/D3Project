#pragma once
#include "base.h"

class CFont
{
public:
	CFont();
	~CFont();

	void drawText( char* str, RECT* rect, DWORD colour = 0xffff0000);

private:
	ID3DXFont* m_font;
};