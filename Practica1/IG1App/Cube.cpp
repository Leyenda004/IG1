#include "Cube.h"
using namespace glm;

Cube::Cube(double length) {
	mMesh = Mesh::generateCube(length);
}

void Cube::render(glm::mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", aMat);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
		
		// Culling
		glEnable(GL_CULL_FACE);
		// Back
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glCullFace(GL_BACK);
		mMesh->render();

		//// Front
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();
		glDisable(GL_CULL_FACE);
	}
}