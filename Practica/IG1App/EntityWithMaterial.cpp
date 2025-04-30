#include "EntityWithMaterial.h"
#include "Material.h"

using namespace glm;

EntityWithMaterial::EntityWithMaterial(vec3 color)
{
    // Una de estas dos !!
    // mMaterial = new Material(color);
    //mMaterial->setAmb(color);
	mMaterial = new Material(color);
}