#pragma once
#include "EntityWithTexture.h"
#include "Mesh.h"
class Box :
    public EntityWithTexture
{
public:
	Box(GLdouble lenght, GLdouble x, GLdouble y, GLdouble z);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

private:
	GLdouble l;

	Mesh* mMeshTapa;
	Mesh* mMeshFondo;
	glm::mat4 mModelMatTapa;
	glm::mat4 mModelMatFondo;

	Texture* _mTextureOut;
	Texture* _mTextureInside;

	bool giroFuera = true;
	int velGiro = 3;
	int giroTotal = 90;
	int c = 0; //contador de giro

	//glm::mat4 mModelMatTapaDestino;
};