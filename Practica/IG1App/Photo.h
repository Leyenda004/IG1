#pragma once
#include "EntityWithTexture.h"
class Photo :
    public EntityWithTexture
{
public:
    Photo(int l);
private:
    void update() override;
};

