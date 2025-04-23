#include "Scene6.h"

#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"
#include "CompoundEntity.h"

using namespace glm;

void Scene6::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	CompoundEntity* ovni = new CompoundEntity();
	
	//!!!!!!!! NORMALES NO SIGUEN

	//Radio, paralelos, meridianos
	Sphere* sphere = new Sphere(50.0f);
	ovni->addEntity(sphere);
	//Radio exterior / Radio interior / nRings / nSamples
	Disk* disk = new Disk(200.0f, 100.0f);
	ovni->addEntity(disk);
	//Altura / Radio inferior / Radio superior
	Cone* cone = new Cone(50.0f, 100.0f, 100.0f);
	ovni->addEntity(cone);

	gObjects.push_back(ovni);

}