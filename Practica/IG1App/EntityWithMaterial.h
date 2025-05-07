#pragma once
#include "Entity.h"
#include "Material.h"
class EntityWithMaterial :
    public Abs_Entity
{
public:
	EntityWithMaterial(glm::vec3 color = glm::vec3{ 0.0f, 1.0f, 0.0f });
	~EntityWithMaterial() { delete mMaterial; };
	void setMaterial(Material* material) { mMaterial = material; }
	Material* getMaterial() const { return mMaterial; }
protected:
	Material* mMaterial;
};

