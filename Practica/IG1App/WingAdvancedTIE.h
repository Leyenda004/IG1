#pragma once
#include "EntityWithTexture.h"
#include "Mesh.h"
class WingAdvancedTIE :
    public EntityWithTexture
{
public:
	WingAdvancedTIE(GLdouble length, std::string mTextureOut);
	void render(glm::mat4 const& modelViewMat) const override;
};

