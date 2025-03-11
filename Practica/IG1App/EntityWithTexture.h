#pragma once
#include "Texture.h"

#include "Entity.h"

class EntityWithTexture : public Abs_Entity
{
protected:
	Texture* mTexture = nullptr;
	GLboolean mModulate = false;
public:
	EntityWithTexture();
	~EntityWithTexture();
	void setTexture(Texture* tex) { mTexture = tex; }
	void render(glm::mat4 const& modelViewMat) const override;
};

