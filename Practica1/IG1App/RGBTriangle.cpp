#include "RGBTriangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

RGBTriangle::RGBTriangle(GLdouble radius) : EntityWithColors() {
	mMesh = Mesh::generateRGBTriangle(radius);
}

void RGBTriangle::update() {
	if (mMesh != nullptr) {
		//// Sentido horario sobre s� mismo
		//// Cast constante?
		//const_cast<RGBTriangle*>(this)->setModelMat(rotate(modelMat(), radians(-10.f), vec3(0, 0, 1)));

		//// Sentido antihorario sobre la circunferencia
		//GLdouble x, y, z;

		//// Coordenadas?
		//x = modelMat()[3][0];
		//y = modelMat()[3][1];
		//z = modelMat()[3][2];

		//mat4 mT1 = translate(mat4(1.0f), vec3(x, y, z));
		//mat4 mR = rotate(mat4(1.0f), radians(10.f), vec3(0, 0, 1));
		//mat4 mT2 = translate(mat4(1.0f), vec3(-x, -y, -z));

		//const_cast<RGBTriangle*>(this)->setModelMat();

		mat4 m1 = rotate(mModelMat, radians(-4.0f), vec3(0.0f, 0.0f, 1.0f));
		mat4 m2 = rotate(mat4(1.0f), radians(2.0f), vec3(0.0f, 0.0f, 1.0f));
		setModelMat(m2 * m1);
	}
}