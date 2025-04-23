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
	Sphere* sphere = new Sphere(10.0f);
	addEntity(sphere);

	//Altura / Radio inferior / Radio superior
	Cone* coneIz = new Cone(100.0f, 10.0f, 10.0f);
	mat4 tras = translate(mat4(1.0f), vec3(-100.0f, 0.0f, 0.0f));
	mat4 rot = rotate(tras, radians(45.0f), vec3(0.0f, 0.0f, 1.0f));
	coneIz->setModelMat(rot);
	addEntity(coneIz);


	Cone* coneDr = new Cone(100.0f, 10.0f, 10.0f);
	//addEntity(coneDr);
}
