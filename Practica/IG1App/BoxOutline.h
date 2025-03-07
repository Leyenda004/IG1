#pragma once
//#include "SingleColorEntity.h"
#include "EntityWithTexture.h"

class BoxOutline :
    public EntityWithTexture
{
private:
    Texture* _mTextureOut;
    Texture* _mTextureInside;
public:
    BoxOutline(GLdouble length/* = 100.f*/,std::string mTextureOut, std::string mTextureInside);
    void render(const glm::mat4& modelViewMat) const override;
};

