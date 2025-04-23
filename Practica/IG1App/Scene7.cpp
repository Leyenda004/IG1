#include "Scene7.h"

#include "Sphere.h"
#include "CompoundEntity.h"
#include "AdvancedTIE.h"
#include "Disk.h"
#include "Cone.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void Scene7::init()
{
	this->setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	//Sphere* Tatooine = new Sphere(100.0f, 40, 40);
	//gObjects.push_back(Tatooine);

	CompoundEntity* FigtherTIE = new CompoundEntity();
	AdvancedTIE* tie = new AdvancedTIE();
	FigtherTIE->addEntity(tie);

	FigtherTIE->setModelMat(translate(FigtherTIE->modelMat(), vec3(0.0f, 0.0f, 100.0f)));
	gObjects.push_back(FigtherTIE);

}
