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
	//coneA->setModelMat(translate(coneA->modelMat(), vec3(-15.0f, 40.0f, 0.0f)));
	addEntity(coneA);

	//Radio exterior / Radio interior / nRings / nSamples
	Disk* disk = new Disk(32.0f, 0.0f, 20, 20);
	mat4 trasDisk = translate(disk->modelMat(), vec3(0.0f, 75.0f, 30.0f));
	mat4 rotDisk = rotate(disk->modelMat(), radians(45.0f), vec3(1.0f, 0.0f, 0.0f));
	disk->setModelMat(disk->modelMat() * rotDisk * trasDisk);
	gObjects.push_back(disk);

	Cone* coneB = new Cone(100.0f, 30.0f, 30.0f);
	mat4 trasconeB = translate(coneB->modelMat(), vec3(0.0f, 50.0f,20.0f));
	mat4 rotconeB = rotate(coneB->modelMat(), radians(45.0f), vec3(1.0f, 0.0f, 0.0f));
	coneB->setModelMat(coneB->modelMat() * rotconeB * trasconeB);
	//coneB->setModelMat(translate(coneB->modelMat(), vec3(0.0f, 65.0f, 50.0f)));
	addEntity(coneB);
}
