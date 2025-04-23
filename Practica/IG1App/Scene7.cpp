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
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	Sphere* Tatooine = new Sphere(200.0f, 40, 40);
	Tatooine->setColor({1.0f,0.9f,0.0f,1.0f}); //255,233,0
	gObjects.push_back(Tatooine);

	Node = new CompoundEntity();
	CompoundEntity* NodeAuxRot = new CompoundEntity();

	mat4 TIErot = rotate(mat4(1.0f), radians(90.0f), vec3(0.f, 1.f, 0.f));
	NodeAuxRot->setModelMat(NodeAuxRot->modelMat() * TIErot);
	Node->addEntity(NodeAuxRot);

	AdvancedTIE* FighterTIE = new AdvancedTIE();
	mat4 TIEtras = translate(mat4(1.0f), vec3(0.0f, 1120.0f, 0.0f));
	mat4 TIEscale = scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f));
	FighterTIE->setModelMat(FighterTIE->modelMat() * TIEscale * TIEtras);
	Node->addEntity(FighterTIE);
	gObjects.push_back(Node);

}

bool Scene7::handleKey(unsigned int key)
{
	bool needRedisplay = true;
	switch (key) {
	case 'h':
		rotateTIE();
		break;
	case 'g':
		orbitTIE();
		break;
	default:
		needRedisplay = false;
		break;
	}
	return needRedisplay;
}

void Scene7::rotateTIE()
{
	Node->setModelMat(glm::rotate(Node->modelMat(), radians(3.0f), vec3{0.f, 1.f, 0.f}));
}

void Scene7::orbitTIE()
{
	Node->setModelMat(glm::rotate(Node->modelMat(), radians(3.0f), vec3{ 1.f, 0.f, 0.f }));
}
