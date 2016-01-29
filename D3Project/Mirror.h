#pragma once
#include "base.h"
#include "XMesh.h"
#include "Material.h"

class CMirror
{
public:
	CMirror();
	~CMirror();

	void renderMirror( CXMesh* mesh);
};