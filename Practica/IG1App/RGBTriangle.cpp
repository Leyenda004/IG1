#include "RGBTriangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

RGBTriangle::RGBTriangle(GLdouble radius) : EntityWithColors() {
	mMesh = Mesh::generateRGBTriangle(radius);
}

void RGBTriangle::render(const glm::mat4& modelViewMat) const
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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	mMesh->render();

	// Culling disable
	glDisable(GL_CULL_FACE);
}

void RGBTriangle::update() {
	if (mMesh != nullptr) {
		//// Sentido horario sobre s� mismo
		//setModelMat(rotate(modelMat(), radians(-10.f), vec3(0, 0, 1)));

		//// Coordenadas
		//GLdouble x, y, z;
		//x = modelMat()[3][0];
		//y = modelMat()[3][1];
		//z = modelMat()[3][2];

		//// Sentido antihorario sobre la circunferencia
		//mat4 mT1 = translate(mat4(1.0f), vec3(x, y, z));
		//mat4 mR = rotate(mat4(1.0f), radians(10.f), vec3(0, 0, 1));
		//mat4 mT2 = translate(mat4(1.0f), vec3(-x, -y, -z));

		//setModelMat(mModelMat * mT1 * mR * mT2);


		// RECORDATORIO PARA ELENA: En el enunciado de la práctica, el giro sobre sí mismo es en horario y en la demo es en antihorario

		// Se gira la malla sobre sí misma pasándole el mModelMat, y se gira sobre el eje
		// pasándole la matriz identidad, ya que rotas sobre el punto de origen
		mat4 m1 = rotate(mModelMat, radians(-4.0f), vec3(0.0f, 0.0f, 1.0f));
		mat4 m2 = rotate(mat4(1.0f), radians(2.0f), vec3(0.0f, 0.0f, 1.0f));

		// Se le aplican los cambios a la matriz
		mModelMat = m2 * m1;
	}
}