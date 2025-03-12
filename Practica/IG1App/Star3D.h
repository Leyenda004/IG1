#pragma once
// #include "SingleColorEntity.h"
#include "EntityWithTexture.h"
class Star3D :
    public EntityWithTexture
{
public:
    Star3D(GLdouble re, GLuint np, GLdouble h, GLdouble posX, GLdouble posY, GLdouble posZ, std::string mTexturePar);
    ~Star3D();
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
private:
    Texture* _starTexture;
    float _rotY = 0.0f, _rotZ = 0.0f, _rotationSpeed = 0.1f;
    glm::mat4 axeY;
};

