#pragma once
#include "EntityWithTexture.h"
class Photo :
    public EntityWithTexture
{
public:
    Photo();
private:
    void update() override;
};

