#pragma once
#include "EntityWithTexture.h"
class Photo :
    public EntityWithTexture
{
public:
    Photo(Texture* tex);
private:
    void update() override;
};

