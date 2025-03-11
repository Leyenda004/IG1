#pragma once
// #include "SingleColorEntity.h"
#include "EntityWithTexture.h"
class Star3D :
    public EntityWithTexture
{
public:
    Star3D(GLdouble re, GLuint np, GLdouble h, std::string mTexturePar);
    ~Star3D();
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
private:
    Texture* _starTexture;
};

