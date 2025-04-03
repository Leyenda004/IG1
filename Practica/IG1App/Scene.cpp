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
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) //delete a los objetos opacos
		delete el;
	for (Abs_Entity* el : gObjectsTranslucid) //delete a los objetos translucidos
		delete el;

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

void
Scene::render(Camera const& cam) const
{
	cam.upload();

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