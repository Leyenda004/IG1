#include "AdvancedTIE.h"

#include "Sphere.h"
#include "Disk.h"
#include "Cone.h"
#include "WingAdvancedTIE.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

AdvancedTIE::AdvancedTIE()
{
	//Radio, paralelos, meridianos
	Sphere* sphere = new Sphere(100.0f);
	sphere->setColor({ 0.0f,0.25f,0.41f,1.0f }); //(0,65,106)
	addEntity(sphere);
	
	//Altura / Radio inferior / Radio superior
	Cone* coneA = new Cone(300.0f, 20.0f, 20.0f);
	coneA->setColor({ 0.0f,0.25f,0.41f,1.0f }); //(0,65,106)
	coneA->setModelMat(rotate(mat4(1.0f), radians(90.0f), vec3(0.0f, 0.0f, 1.0f)));
	coneA->setModelMat(translate(coneA->modelMat(), vec3(0.0f, -5.0f, 0.0f)));
	addEntity(coneA);
	
	//Radio exterior / Radio interior / nRings / nSamples
	Disk* disk = new Disk(32.0f, 0.0f, 20, 20);
	disk->setColor({ 0.0f,0.25f,0.41f,1.0f }); //(0,65,106)
	mat4 trasDisk = translate(disk->modelMat(), vec3(0.0f, 150.0f, 0.0f));
	mat4 rotDisk = rotate(disk->modelMat(), radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	disk->setModelMat(disk->modelMat() * rotDisk * trasDisk);
	addEntity(disk);
	
	Cone* coneB = new Cone(100.0f, 30.0f, 30.0f);
	coneB->setColor({ 0.0f,0.25f,0.41f,1.0f }); //(0,65,106)
	mat4 trasconeB = translate(coneB->modelMat(), vec3(0.0f, 100.0f,0.0f));
	mat4 rotconeB = rotate(coneB->modelMat(), radians(90.0f), vec3(1.0f, 0.0f, 0.0f));
	coneB->setModelMat(coneB->modelMat() * rotconeB * trasconeB);
	//coneB->setModelMat(translate(coneB->modelMat(), vec3(0.0f, 65.0f, 50.0f)));
	addEntity(coneB);

	WingAdvancedTIE* wingA = new WingAdvancedTIE(300.0f, "../assets/images/noche.jpg");
	mat4 traswingA = translate(wingA->modelMat(), vec3(-145.0f, 0.0f, 0.0f));
	mat4 rotwingA = rotate(wingA->modelMat(), radians(-90.0f), vec3(0.0f, 1.0f, 0.0f));
	wingA->setModelMat(traswingA * rotwingA * wingA->modelMat());
	addEntity(wingA);

	WingAdvancedTIE* wingB = new WingAdvancedTIE(300.0f, "../assets/images/noche.jpg");
	mat4 traswingB = translate(wingB->modelMat(), vec3(145.0f, 0.0f, 0.0f));
	mat4 rotwingB = rotate(wingB->modelMat(), radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	wingB->setModelMat(traswingB * rotwingB * wingB->modelMat());
	addEntity(wingB);
}
