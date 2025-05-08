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

	//Añadimos luces, metodo virtual para modificar en caso de ser necesario, haciendo que añada el dirLight al array de lights
	addLights();

	//// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	Sphere* tat1 = new Sphere(100.0f, 40, 40);
	Material* goldMaterial = new Material({ 1, 1, 0 });
	goldMaterial->setGold();
	gMaterials.push_back(goldMaterial);
	tat1->setMaterial(goldMaterial);
	tat1->setModelMat(translate(mat4(1), vec3(-150, 0, 0)));
	gObjects.push_back(tat1);

	Sphere* tat2 = new Sphere(100.0f, 40, 40);
	//Copper material, asignamos los valores directamente
	Material* copperMaterial = new Material({ 1, 1, 0 });
	copperMaterial->setCopper();
	gMaterials.push_back(copperMaterial);
	tat2->setMaterial(copperMaterial);
	tat2->setModelMat(translate(mat4(1), vec3(150, 0, 0)));
	gObjects.push_back(tat2);

}