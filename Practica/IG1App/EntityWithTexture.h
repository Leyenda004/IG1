#pragma once
#include "Texture.h"

class EntityWithTexture
{
private:
	Texture* mTexture;
	GLboolean mModulate = false;
public:
	EntityWithTexture();
	void render(mat4 const& modelViewMat) const;
};

