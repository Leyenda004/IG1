#include "Scene.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();
}

void
Scene::unload()
{
	for (Abs_Entity* obj : gObjects)
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

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
}


void
Scene::update() {
	for (Abs_Entity* el : gObjects) {
		el->update();
	}
}

void 
Scene::takePhoto()
{
	//Texture* t = new Texture();
	//GLuint texture_map;
	//char* archivo = "archivo";
	//t->loadColorBuffer(800.f, 600.f);
	//glGenTextures(1, &texture_map);
	//glBindTexture(GL_TEXTURE_2D, texture_map);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 800.f, 600.f, 0, GL_RGB, GL_UNSIGNED_BYTE, "../assets/Prueba.bmp");
	//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, t);
	//delete t;
}