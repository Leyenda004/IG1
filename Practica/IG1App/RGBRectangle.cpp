#include "RGBRectangle.h"
using namespace glm;

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) : EntityWithColors() {
	mMesh = Mesh::generateRGBRectangle(w, h);
	//load();
}

void RGBRectangle::render(glm::mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", aMat);

		glEnable(GL_CULL_FACE);

		// Back
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		// Front
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();

		glDisable(GL_CULL_FACE);
	}
}