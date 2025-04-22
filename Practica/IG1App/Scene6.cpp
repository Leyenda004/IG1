#include "Scene6.h"

#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"

using namespace glm;

void Scene6::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	//Radio, paralelos, meridianos
	Sphere* sphere = new Sphere(50.0f, 40, 40);
	//!!!!!!!! NORMALES NO SIGUEN
	//mat4 photoTras = translate(mat4(1.0f), vec3(200.0f, 200.0f, 200.0f));
	//sphere->setModelMat(photoTras * sphere->modelMat());
	gObjects.push_back(sphere);

	//Radio exterior / Radio interior / nRings / nSamples
	Disk* disk = new Disk(200.0f, 100.0f, 20, 20);
	gObjects.push_back(disk);

	//Altura / Radio inferior / Radio superior
	Cone* cone = new Cone(50.0f, 100.0f, 50.0f);
	gObjects.push_back(cone);

}