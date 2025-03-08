#pragma once
#include "EntityWithTexture.h"
class GlassParapet :
    public EntityWithTexture
{
public:
    GlassParapet(GLdouble length, std::string mTextureOut);
    void render(glm::mat4 const& modelViewMat) const override;
private:
	Texture* mTextureAux;
};

