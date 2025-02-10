#include "RGBCube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

RGBCube::RGBCube(GLdouble length) {
	mMesh = Mesh::generateRGBCubeTriangles(length);
}

void 
RGBCube::render(const glm::mat4& modelViewMat) const
{
	mat4 aMat = modelViewMat * mModelMat;
	mShader->use();
	mShader->setUniform("modelView", aMat);

			// Culling enable
	glEnable(GL_CULL_FACE);

	// Back
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	mMesh->render();

	// Front
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	mMesh->render();

	// Culling disable
	glDisable(GL_CULL_FACE);
}

void 
RGBCube::update()
{

	int r = 0.0f, g = 0.0f, b = 0.0f;
	 
	switch (index) {
		case 0:
			r = 1.0f; 
			g = 0.0f; 
			b = 0.0f;
			break;
		case 1:
			r = 0.0f; 
			g = 0.0f; 
			b = 1.0f;
			break;
		case 2:
			r = 0.0f; 
			g = 1.0f; 
			b = 0.0f;
			break;
	}

	if (angle < radians(179.9f)) {
		mat4 mT1 = translate(mModelMat, vec3(-100.0f, -100.0f, 100.0f));
		mat4 m1 = rotate(mat4(1.0f), radians(1.0f), vec3(r,g,b));
		setModelMat(mT1 * m1);
		mat4 mT2 = translate(mModelMat, vec3(100.0f, 100.0f, -100.0f));
		setModelMat(mT2);
		angle += radians(1.0f);
	}
	else {
		index++;
		angle = 0.0f;
	}

	if (index >= 3) index = 0;
}

