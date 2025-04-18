#include "Scene6.h"

#include "Sphere.h"
#include "Disk.h"



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


	Sphere* sphere = new Sphere(200.0f, 30, 30);
	mat4 photoTras = translate(mat4(1.0f), vec3(200.0f, 200.0f, 200.0f));
	sphere->setModelMat(photoTras * sphere->modelMat());
	gObjects.push_back(sphere);

	Disk* disk = new Disk(200.0f, 100.0f);
	gObjects.push_back(disk);
}