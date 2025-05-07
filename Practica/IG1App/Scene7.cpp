#include "Scene7.h"

#include "Sphere.h"
#include "CompoundEntity.h"
#include "AdvancedTIE.h"
#include "EntityWithLight.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace glm;

void Scene7::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	addLights();

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	// Planeta a la escena
	Sphere* Tatooine = new Sphere(200.0f, 40, 40);
	Tatooine->setMaterial(new Material({1.0f,0.9f,0.0f})); //255,233,0
	gObjects.push_back(Tatooine);

	// Entidad compuesta
	Node = new CompoundEntity();
	// Nodo auxiliar
	CompoundEntity* NodeAuxRot = new CompoundEntity();

	// Rotaci�n con el nodo fantasma/auxiliar
	//mat4 TIErot = rotate(mat4(1.0f), radians(90.0f), vec3(0.f, 1.f, 0.f));
	//NodeAuxRot->setModelMat(NodeAuxRot->modelMat() * TIErot);
	//Node->addEntity(NodeAuxRot);

	// Creaci�n y colocaci�n del TIE
	AdvancedTIE* FighterTIE = new AdvancedTIE();
	mat4 TIEtras = translate(mat4(1.0f), vec3(0.0f, 1120.0f, 0.0f));
	mat4 TIEscale = scale(mat4(1.0f), vec3(0.2f, 0.2f, 0.2f));
	FighterTIE->setModelMat(FighterTIE->modelMat() * TIEscale * TIEtras);
	Node->addEntity(FighterTIE);

	EntityWithLight* FighterTIElight = new EntityWithLight(foco);
	gLights.push_back(FighterTIElight->getLight());
	Node->addEntity(FighterTIElight);

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
	case 'r':
		focoOn = !focoOn;
		std::cout << "Foco " << (focoOn ? "on" : "off") << std::endl;
		foco->setEnabled(focoOn);
		break;
	case 't':
		posLightOn = !posLightOn;
		std::cout << "PosLight " << (posLightOn ? "on" : "off") << std::endl;
		posLight->setEnabled(posLightOn);
		break;
	case 'y':
		spotLightOn = !spotLightOn;
		std::cout << "SpotLight " << (spotLightOn ? "on" : "off") << std::endl;
		spotLight->setEnabled(spotLightOn);
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

void Scene7::addLights()
{
	// Directional light
	DirLight* dirLight = new DirLight(0);
	dirLight->setEnabled(false);
	// Componentes
	dirLight->setAmb({ 0.25f, 0.25f, 0.25f });
	dirLight->setDiff({ 0.6f, 0.6f, 0.6f });
	dirLight->setSpec({ 0.0f, 0.2f, 0.0f });
	// Transformaciones
	dirLight->setDirection({ -1.0f, -1.0f, -1.0f });
	// Vector
	gLights.push_back(dirLight);


	// Positional light
	posLight = new PosLight(0);
	posLight->setEnabled(false);
	// Componentes
	posLight->setAmb({ 0.25f, 0.25f, 0.25f });
	posLight->setSpec({ 0.0f, 0.2f, 0.0f });
	posLight->setDiff({ 1.0f, 1.0f, 0.0f });
	// Transformaciones
	posLight->setPosition({ -200.0f, 200.0f, 200.0f }); // Derecha y arriba
	// Vector
	gLights.push_back(posLight);


	// Spot light
	spotLight = new SpotLight({ 0, 0, 0 }, 0);
	spotLight->setEnabled(false);
	// Componentes
	spotLight->setAmb({ 0.25f, 0.25f, 0.25f });
	spotLight->setDiff({ 0.6f, 0.6f, 0.6f });
	spotLight->setSpec({ 0.0f, 0.2f, 0.0f });
	// Transformaciones
	spotLight->setPosition({ 175.0f, 175.0f, 175.0f }); // Izquierda y arriba
	spotLight->setDirection({ -1.0f, -1.0f, -1.0f });
	spotLight->setAttenuation(0.6f, 0.003f, 0.0f); // Constante, linear, cuadratica (cuanto mas, menos se expande)
	// Vector
	gLights.push_back(spotLight);


	// Foco
	foco = new SpotLight({ 0, 0, 0 }, 1);
	foco->setEnabled(false);
	// Componentes
	foco->setAmb({ 0.25f, 0.25f, 0.25f });
	foco->setDiff({ 0.6f, 0.6f, 0.6f });
	foco->setSpec({ 0.0f, 0.2f, 0.0f });
	// Transformaciones
	foco->setPosition({ 0.0f, 235, 0.0f });
	foco->setDirection({ 0.0f, -1.0f, 0.0f });
	//foco->setCutoff(10.0f, 30.0f); // Angulo interno y externo
	foco->setAttenuation(0.6f, 0.003f, 0.0f);
	// Vector
	gLights.push_back(foco);
}