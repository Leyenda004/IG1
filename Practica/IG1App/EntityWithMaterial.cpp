#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial(glm::vec3 color)
{
	mMaterial = Material(color);
}

void EntityWithMaterial::setMaterial(const Material& material)
{
	mMaterial = material;
}

Material EntityWithMaterial::getMaterial() const
{
	return mMaterial;
}
