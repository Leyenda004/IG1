#pragma once
#include "EntityWithTexture.h"
#include "Mesh.h"
class Box :
    public EntityWithTexture
{
public:
	Box(GLdouble);
	void render(const glm::mat4& modelViewMat) const override;

private:
	Mesh* mMeshTapa = nullptr;
	Mesh* mMeshFondo = nullptr;
	glm::mat4 mModelMatTapa;
	glm::mat4 mModelMatFondo;

	Texture* _mTextureOut;
	Texture* _mTextureInside;

};

