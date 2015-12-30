#pragma once
#include "base.h"

class CTexture
{
public:
	CTexture( char* fileName);
	~CTexture();

	void useTexture();

private:
	IDirect3DTexture9* m_pTexture;
};