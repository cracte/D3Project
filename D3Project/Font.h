#pragma once
#include "base.h"

class CFont
{
public:
	CFont();
	~CFont();

	void drawText( char* str, RECT* rect);

private:
	ID3DXFont* m_font;
};