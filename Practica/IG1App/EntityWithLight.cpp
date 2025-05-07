#include "EntityWithLight.h"
#include "Mesh.h"
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

EntityWithLight::EntityWithLight(SpotLight* light) : mLight(light)
{
    mMesh = Mesh::generateCube(0.1f);
    mLight->setEnabled(true);
    // lightSphere->setMaterial(new Material({ 1.0f, 1.0f, 1.0f }));
}

void EntityWithLight::update()
{
    if (mLight != nullptr)
    {
        vec3 lightPos = glm::vec3(modelMat() * vec4(0.0, 0.0, 0.0, 1.0));
        mLight->setPosition(lightPos);

        if (SpotLight* spotLight = dynamic_cast<SpotLight*>(mLight))
        {
            vec3 lightDir = glm::vec3(modelMat() * vec4(0.0, -1.0, 0.0, 0.0));
            spotLight->setDirection(lightDir);
        }
    }
}


