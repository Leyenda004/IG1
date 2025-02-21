#pragma once
#include "Texture.h"

#include "Entity.h"

class EntityWithTexture : public Abs_Entity
{
private:
	Texture* mTexture;
	GLboolean mModulate = false;
public:
	EntityWithTexture();
	void render(glm::mat4 const& modelViewMat) const override;
};

