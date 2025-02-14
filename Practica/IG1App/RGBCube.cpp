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
		// Se mueve al origen
		mat4 mT1 = translate(mModelMat, vec3(-100.0f, -100.0f, 100.0f));
		// Se rota sobre el eje designado
		mat4 m1 = rotate(mat4(1.0f), radians(1.0f), vec3(x, y, z));
		// Se aplica la transformación
		mModelMat = (mT1 * m1);
		// Se vuelve a la posición
		mat4 mT2 = translate(mModelMat, vec3(100.0f, 100.0f, -100.0f));
		mModelMat = mT2;
		// Se añade el ángulo para tenerlo en cuenta en los otros ejes
		angle += radians(1.0f);
	}
	else {
		index++;
		angle = 0.0f;
	}

	if (index >= 3) index = 0;
}