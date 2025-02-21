#pragma once
#include "Entity.h"

#include "EntityWithTexture.h"
class Ground :
    public EntityWithTexture
{
public:
    Ground();
    void render(const glm::mat4& modelViewMat) const override;
};

