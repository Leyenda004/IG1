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
	if (mMesh != nullptr) {
		//SI QUITO ESTAS 3 LINEAS SE VA AL CENTRO REVISAR??????
		mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", aMat);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
	}
}

void 
RGBCube::update()
{

	int x = 0.0f, y = 0.0f, z = 0.0f;
	 
	switch (index) {
		case 0:
			x = 1.0f; 
			y = 0.0f; 
			z = 0.0f;
			break;
		case 1:
			x = 0.0f; 
			y = 0.0f; 
			z = 1.0f;
			break;
		case 2:
			x = 0.0f; 
			y = 1.0f; 
			z = 0.0f;
			break;
	}

	if (angle < radians(179.9f)) {
		mat4 mT1 = translate(mModelMat, vec3(-100.0f, -100.0f, 100.0f));
		mat4 m1 = rotate(mat4(1.0f), radians(1.0f), vec3(x,y,z));
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