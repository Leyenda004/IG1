#include "Cube.h"
using namespace glm;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(GLdouble length) {
	mMesh = Mesh::generateCube(length);
}

void Cube::render(glm::mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {

		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", aMat);

		// Culling enable
		glEnable(GL_CULL_FACE);

		// Back
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		// Front
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();

		// Culling disable
		glDisable(GL_CULL_FACE);
	}
}