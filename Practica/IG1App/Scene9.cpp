#include "Scene9.h"

#include "Sphere.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;

void Scene9::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	//A�adimos luces, metodo virtual para modificar en caso de ser necesario, haciendo que a�ada el dirLight al array de lights
	addLights();

	//// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	Sphere* tat1 = new Sphere(100.0f, 40, 40);
	Material goldMaterial = Material({ 1, 1, 0 });
	goldMaterial.setGold();
	gMaterials.push_back(goldMaterial);
	tat1->setMaterial(goldMaterial);
	tat1->setModelMat(translate(mat4(1), vec3(-150, 0, 0)));
	gObjects.push_back(tat1);

	Sphere* tat2 = new Sphere(100.0f, 40, 40);
	//Copper material, asignamos los valores directamente
	Material copperMaterial = Material({ 1, 1, 0 });
	copperMaterial.setCopper();
	gMaterials.push_back(copperMaterial);
	tat2->setMaterial(copperMaterial);
	tat2->setModelMat(translate(mat4(1), vec3(150, 0, 0)));
	gObjects.push_back(tat2);

}

void Scene9::addLights() {
	
	dirLight = new DirLight(0); //Luz direccional ///El parametro es una id �nica, cuidado
	dirLight->setEnabled(true); //Activamos la luz direccional
	dirLight->setAmb({ 0.25f, 0.25f, 0.25f });
	dirLight->setDiff({ 0.6f, 0.6f, 0.6f });
	dirLight->setSpec({ 0.0f, 0.2f, 0.0f });
	//Se hace por defecto
	dirLight->setDirection({ -1.0f, -1.0f, -1.0f });
	
	gLights.push_back(dirLight);
}