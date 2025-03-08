#pragma once
#include "EntityWithTexture.h"
#include "Mesh.h"
class Box :
    public EntityWithTexture
{
	Box();
private:
	Mesh* mMeshTapa;
	Mesh* mMeshFondo;
};

