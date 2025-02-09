#include "RGBCube.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
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
	//mat4 mT1 = translate(mModelMat, vec3(0,-100.0f, 100.0f));
	//mat4 mR = rotate(mat4(1.0f), radians(1.0f), vec3(1,0,0));
	//mat4 mT2 = translate(mModelMat, vec3(0, 100.0f, -100.0f));
	//setModelMat(mT1 * mR * mT2);

	//EJE X
	if (index == 0) {
		if (angle <= radians(180.f)) {
			mat4 mT1 = translate(mModelMat, vec3(-100.0f, -100.0f, 100.0f));
			mat4 m1 = rotate(mat4(1.0f), radians(1.0f), vec3(1.0f, 0.0f, 0.0f));
			setModelMat(mT1 * m1);
			mat4 mT2 = translate(mModelMat, vec3(100.0f, 100.0f, -100.0f));
			setModelMat(mT2);
			angle += radians(1.0f);
		}
		else {
			index++;
			angle = 0.0f;
		}
	}

	//EJE Z
	if (index == 1) {
		if (angle <= radians(180.f)) {
			mat4 mT1 = translate(mModelMat, vec3(-100.0f, -100.0f, 100.0f));
			mat4 m1 = rotate(mat4(1.0f), radians(-1.0f), vec3(0.0f, 0.0f, 1.0f));
			setModelMat(mT1 * m1);
			mat4 mT2 = translate(mModelMat, vec3(100.0f, 100.0f, -100.0f));
			setModelMat(mT2);
			angle += radians(1.0f);
		}
		else {
			index++;
			angle = 0.0f;
		}
	}

	//EJE Y
	if (index == 2) {
		GLfloat a = glm::length(vec3(mModelMat[1]));
		if (angle <= radians(180.f)) {
			mat4 mT1 = translate(mModelMat, vec3(-100.0f, -100.0f, 100.0f));
			mat4 m1 = rotate(mat4(1.0f), radians(1.0f), vec3(0.0f, 1.0f, 0.0f));
			setModelMat(mT1 * m1);
			mat4 mT2 = translate(mModelMat, vec3(100.0f, 100.0f, -100.0f));
			setModelMat(mT2);
			angle += radians(1.0f);
		}
		else {
			index++;
			angle = 0.0f;
		}
	}

	if (index >= 3) index = 0;
}

