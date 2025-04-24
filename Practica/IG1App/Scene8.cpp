#include "Scene8.h"

#include "CompoundEntity.h"
#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void Scene8::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	CompoundEntity* Farmer = new CompoundEntity();

	Sphere* head = new Sphere(100.0f, 40, 40);
	head->setColor({ 1, 0.5f, 0, 1 });
	Farmer->addEntity(head);

	// Ojo izquierdo
	Cone* coneA = new Cone(20, 0, 10);
	coneA->setColor({ 0, 0.60f, 0.6f, 1.0f });
	mat4 rotconeA = rotate(coneA->modelMat(), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 trasconeA = translate(mat4(1), vec3(-30.0f, 30.0f, 95));
	coneA->setModelMat(trasconeA * rotconeA);
	Farmer->addEntity(coneA);

	// Ojo derecho
	Cone* coneB = new Cone(20, 0, 10);
	coneB->setColor({ 0, 0, 1, 1.0f });
	mat4 rotconeB = rotate(coneB->modelMat(), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 trasconeB = translate(mat4(1), vec3(30.0f, 30.0f, 95));
	coneB->setModelMat(trasconeB * rotconeB);
	Farmer->addEntity(coneB);

	// Disco cabeza
	Disk* disk = new Disk(100.0f, 00.0f);
	disk->setColor({ 1, 0, 0, 1.0f });
	mat4 trasDisk = translate(disk->modelMat(), vec3(0.0f, 75.0f, 0.0f));
	disk->setModelMat(trasDisk);
	Farmer->addEntity(disk);

	// Disco boca (diskMouth)
	Disk* diskM = new Disk(80, 0, 30, 30, std::numbers::pi);
	diskM->setColor({ 0, 1, 0, 1.0f });
	mat4 rotDiskM = rotate(mat4(1), radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 trasDiskM = translate(mat4(1), vec3(0, 0, 70));
	diskM->setModelMat(trasDiskM * rotDiskM);
	Farmer->addEntity(diskM);

	gObjects.push_back(Farmer);

	Farmer->setModelMat(rotate(Farmer->modelMat(), radians(15.0f), vec3{ 1.f, 0.f, 0.f }));

}