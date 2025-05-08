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

	addLights();

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	// Entidad compuesta Farmer
	CompoundEntity* Farmer = new CompoundEntity();

	// Cabeza
	Sphere* head = new Sphere(100.0f, 40, 40);
	Material headMat = Material({ 1, 0.5f, 0 });
	gMaterials.push_back(headMat);
	head->setMaterial(headMat);
	Farmer->addEntity(head);

	// Ojo izquierdo
	Cone* coneA = new Cone(20, 0, 10);
	Material coneAMat = Material({ 0, 0.6f, 0.6f });
	gMaterials.push_back(coneAMat);
	coneA->setMaterial(coneAMat);
	mat4 rotconeA = rotate(coneA->modelMat(), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 trasconeA = translate(mat4(1), vec3(-30.0f, 30.0f, 95));
	coneA->setModelMat(trasconeA * rotconeA);
	Farmer->addEntity(coneA);

	// Ojo derecho
	Cone* coneB = new Cone(20, 0, 10);
	Material coneBMat = Material({ 0, 0.6f, 0.6f });
	gMaterials.push_back(coneBMat);
	coneB->setMaterial(coneBMat);
	mat4 rotconeB = rotate(coneB->modelMat(), radians(-90.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 trasconeB = translate(mat4(1), vec3(30.0f, 30.0f, 95));
	coneB->setModelMat(trasconeB * rotconeB);
	Farmer->addEntity(coneB);

	// Disco cabeza
	Disk* disk = new Disk(100.0f, 00.0f);
	Material diskMat = Material({ 1, 0, 0 });
	gMaterials.push_back(diskMat);
	disk->setMaterial(diskMat);
	mat4 trasDisk = translate(disk->modelMat(), vec3(0.0f, 75.0f, 0.0f));
	disk->setModelMat(trasDisk);
	Farmer->addEntity(disk);

	// Disco boca (diskMouth)
	Disk* diskM = new Disk(80, 0, 30, 30, std::numbers::pi);
	Material diskMouthMat = Material({ 0, 1, 0 });
	gMaterials.push_back(diskMouthMat);
	diskM->setMaterial(diskMouthMat);
	mat4 rotDiskM = rotate(mat4(1), radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	mat4 trasDiskM = translate(mat4(1), vec3(0, 0, 70));
	diskM->setModelMat(trasDiskM * rotDiskM);
	Farmer->addEntity(diskM);

	// Farmer a escena
	gObjects.push_back(Farmer);

	// Lo giramos levemente 15� para que frontalmente se vea la perspectiva y los discos
	Farmer->setModelMat(rotate(Farmer->modelMat(), radians(15.0f), vec3{ 1.f, 0.f, 0.f }));
}