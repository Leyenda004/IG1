#include "Scene1.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene1::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	// COLOR , LADOS, DISTANCIA DESDE EL CENTRO
	GLdouble r = 200.f;

	RGBTriangle* trian = new RGBTriangle(30.f);
	// Movemos el triangulo en el círculo creado
	trian->setModelMat(translate(trian->modelMat(), vec3(r, 0, 0)));
	gObjects.push_back(trian);

	gObjects.push_back(new RegularPolygon(dvec4(1.0f, 1.0f, 1.0f, 1.0f), 32, r));
	gObjects.push_back(new RGBRectangle(200.0f, 100.0f));
}