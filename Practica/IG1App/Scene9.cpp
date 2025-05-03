#include "Scene9.h"

#include "Sphere.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace glm;

void Scene9::init()
{
	//setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	//se hace el init de la escena padre, haciendo que añada el dirLight al array de lights
	Scene::init();

	//// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	//
	//dirLight = new DirLight(0); //Luz direccional
	//dirLight->setEnabled(true); //Activamos la luz direccional
	//
	//dirLight->setAmb({ 0.25f, 0.25f, 0.25f });
	//dirLight->setDiff({ 0.6f, 0.6f, 0.6f });
	//dirLight->setSpec({ 0.0f, 0.2f, 0.0f });
	//
	////dirLight->setDirection({ -1.0f, -1.0f, -1.0f });
	//
	//lightShader = Shader::get("light");
	//if (lightShader) {
	//	lightShader->use();
	//	lightShader->setUniform("lightDir", vec4(normalize(vec3(-1.0f, -1.0f, -1.0f)), 0.0f));
	//}
	//
	//gLights.push_back(dirLight); //Guardamos la luz direccional en el vector de luces
	////En render cargamos las luces con upload

	Sphere* tat1 = new Sphere(100.0f, 40, 40);
	tat1->setMaterial(new Material({ 1, 1, 0 }));
	tat1->setModelMat(translate(mat4(1), vec3(-150, 0, 0)));
	gObjects.push_back(tat1);

	Sphere* tat2 = new Sphere(100.0f, 40, 40);
	//Copper material, asignamos los valores directamente
	Material* copperMaterial = new Material({ 1, 1, 0 });
	copperMaterial->setCopper();
	tat2->setMaterial(copperMaterial);
	tat2->setModelMat(translate(mat4(1), vec3(150, 0, 0)));
	gObjects.push_back(tat2);

}