#include "Scene7.h"

#include "Sphere.h"
#include "CompoundEntity.h"
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

	Sphere* Tatooine = new Sphere(400.0f, 40, 40);
	mat4 mT = translate(mat4(1.0f), vec3(0.0f, 0.0f, -0.0f));
	Tatooine->setModelMat(mT * Tatooine->modelMat());
	gObjects.push_back(Tatooine);

	CompoundEntity* Ovni = new CompoundEntity();

	Disk* disk = new Disk(200.0f, 100.0f, 20, 20);
	mat4 mT2 = translate(mat4(1.0f), vec3(0.0f, 400.0f, 0.0f));
	disk->setModelMat(mT2 * disk->modelMat());
	gObjects.push_back(disk);
	//Ovni->addEntity(disk);
	//Cone* cone = new Cone(50.0f, 100.0f, 50.0f);
	//Ovni->addEntity(cone);

	//mat4 mT = translate(mat4(1.0f), vec3(0.0f, 0.0f, 500.0f));
	//Ovni->setModelMat(mT * Ovni->modelMat());

	//gObjects.push_back(Ovni);

}
