#include "AdvancedTIE.h"

#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

AdvancedTIE::AdvancedTIE()
{
	//Radio, paralelos, meridianos
	Sphere* sphere = new Sphere(100.0f);
	addEntity(sphere);

	//Altura / Radio inferior / Radio superior
	Cone* coneA = new Cone(300.0f, 20.0f, 20.0f);
	coneA->setModelMat(rotate(mat4(1.0f), radians(45.0f), vec3(0.0f, 0.0f, 1.0f)));
	addEntity(coneA);

	Cone* coneB = new Cone(100.0f, 30.0f, 30.0f);
	coneB->setModelMat(rotate(mat4(1.0f), radians(45.0f), vec3(1.0f, 0.0f, 0.0f)));
	coneB->setModelMat(translate(coneB->modelMat(), vec3(0.0f, 0.0f, 50.0f)));
	//coneB->setModelMat(translate(coneB->modelMat(), vec3(0.0f, 20.0f, 0.0f)));
	addEntity(coneB);
}
