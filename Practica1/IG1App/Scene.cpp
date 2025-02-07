#include "Scene.h"
#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	//gObjects.push_back(new RGBAxes(400.0));
	//gObjects.push_back(new RGBAxes(1200.0));

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// COLOR , LADOS, DISTANCIA DESDE EL CENTRO
	//gObjects.push_back(new RegularPolygon(dvec4(0.0f,1.0f,1.0f,1.0f),3,200.0f));
	//gObjects.push_back(new RegularPolygon(dvec4(1.0f,0.0f,1.0f,1.0f),32,200.0f));
	//gObjects.push_back(new RGBTriangle(100.0f));
	//gObjects.push_back(new RGBRectangle(200.0f, 100.0f));
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
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
}
