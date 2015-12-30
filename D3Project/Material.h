#pragma once
#include "base.h"

class CMaterial
{
public:
	CMaterial();
	~CMaterial();

	void useMaterial();

private:
	D3DMATERIAL9 mat;
};