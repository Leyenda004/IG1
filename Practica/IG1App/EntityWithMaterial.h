#pragma once
#include "Entity.h"
#include "Material.h"
class EntityWithMaterial :
    public Abs_Entity
{
public:
	EntityWithMaterial();
	~EntityWithMaterial() {};
private:
	Material* mMaterial;
};

