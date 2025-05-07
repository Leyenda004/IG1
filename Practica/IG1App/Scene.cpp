#include "Scene.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"

using namespace glm;

// SCENE ACTUALIZA TODOS LOS OBJETOS DENTRO DE ELLA EN SUS HIJOS

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene

	//IDEAS DE IMPLEMENTACION DE LUCES, QUITAR PARA ENTREGA

	//En camera.cpp
	//Shader* lightShader = Shader::get("simple_light");
	//lightShader->use();
	//lightShader->setUniform("lightDir", vec4(normalize(vec3(mViewMat * vec4(-1, -1, -1, 0))), 0.0f));

	//FUNCIONA
	//DirLight* dirLight = new DirLight(0); //Luz direccional
	//dirLight->setEnabled(true); //Activamos la luz direccional
	//dirLight->setAmb({ 0.25f, 0.25f, 0.25f });
	//dirLight->setDiff({ 0.6f, 0.6f, 0.6f });
	//dirLight->setSpec({ 0.0f, 0.2f, 0.0f });

	//Se hace por defecto
	//dirLight->setDirection({ -1.0f, -1.0f, -1.0f });

	//Aplicamos el shader de simple_light como lo teniamos en camera.cpp
	//lightShader = Shader::get("light");
	//if (lightShader) {
	//lightShader->use();
	//	lightShader->setUniform("lightDir", vec4(normalize(vec3(-1.0f, -1.0f, -1.0f)), 0.0f));
	//}
	
	//lightShader = Shader::get("light");
	//gLights.push_back(dirLight); //Guardamos la luz direccional en el vector de luces
	//En render cargamos las luces con upload
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) delete el; //delete a los objetos opacos

	for (Abs_Entity* el : gObjectsTranslucid) delete el; //delete a los objetos translucidos
	
	// for (Texture* t : gTextures) delete t; //delete a las texturas

	for (Light* l : gLights) delete l; //delete a las luces

	for (Material* m : gMaterials) delete m; //delete a los materiales

	gObjects.clear(); //Vaciando el vector de objetos opacos
	gObjectsTranslucid.clear(); //Vaciando el vector de objetos translucidos
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects) //load a los objetos opacos
		obj->load();

	for (Abs_Entity* obj : gObjectsTranslucid) //load a los objetos translucidos
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects) //unload a los objetos opacos
		obj->unload();

	for (Abs_Entity* obj : gObjectsTranslucid) //unload a los objetos translucidos
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	//glEnable(GL_TEXTURE_2D);	// enable textures
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	//glDisable(GL_TEXTURE_2D);	// disable textures
}

void Scene::uploadLights(Camera const& cam) const
{
	Shader* lightShader = Shader::get("light");
	//upload a las luces
	for (Light* l : gLights) 
		if (lightShader != nullptr) {
			if (l->enabled()) l->upload(*lightShader, cam.viewMat());
		}
}

void Scene::addLights()
{
	DirLight* dirLight = new DirLight(0); //Luz direccional ///El parametro es una id única, cuidado
	dirLight->setEnabled(true); //Activamos la luz direccional
	dirLight->setAmb({ 0.25f, 0.25f, 0.25f });
	dirLight->setDiff({ 0.6f, 0.6f, 0.6f });
	dirLight->setSpec({ 0.0f, 0.2f, 0.0f });
	//Se hace por defecto
	dirLight->setDirection({ -1.0f, -1.0f, -1.0f });

	gLights.push_back(dirLight); 


}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	//Cargamos las luces antes de renderizar objetos opacos y translucidos
	
	uploadLights(cam);

	for (Abs_Entity* el : gObjects) //renderizamos los objetos opacos
		el->render(cam.viewMat());

	for (Abs_Entity* el : gObjectsTranslucid) //renderizamos los objetos translucidos
		el->render(cam.viewMat());	
}


void
Scene::update() {

	for (Abs_Entity* el : gObjects) { //updateamos los objetos opacos
		el->update();
	}
	for (Abs_Entity* el : gObjectsTranslucid) //updateamos los objetos translucidos
		el->update();
}

void
Scene::takePhoto()
{
	//Creamos una textura nueva
	Texture* t = new Texture();
	//Guardamos la imagen de la pantalla actual
	t->loadColorBuffer(IG1App::s_ig1app.getWinWidth(), IG1App::s_ig1app.getWinHeight());
	//Guardamos la foto en una direccion designada
	t->savePhoto("../assets/images/example.bmp");
	//Borramos la textura por crearla aparte
	delete t;
}
