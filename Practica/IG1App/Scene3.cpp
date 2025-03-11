#include "Scene3.h"
#include "Ground.h"

#include "Cube.h"
#include "BoxOutline.h"

#include "RGBTriangle.h"

#include "RegularPolygon.h"

#include "RGBRectangle.h"

#include "RGBCube.h"

#include "Star3D.h"

#include "Box.h"

#include "GlassParapet.h"
#include "Photo.h"

#include "Grass.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene3::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0f));

	Ground* ground = new Ground();
	Texture* tex = new Texture();
	tex->load("../assets/images/baldosaC.png", 255);
	ground->setTexture(tex);
	gObjects.push_back(ground);

	//BoxOutline* box = new BoxOutline(100.f,"../assets/images/container.jpg","../assets/images/papelE.png");
	//gObjects.push_back(box);

	Box* boxComplete = new Box(50.f);
	mat4 boxTras = translate(mat4(1.0f), vec3(0.0f, 25.0f, 0.0f));
	boxComplete->setModelMat(boxTras * boxComplete->modelMat());
	gObjects.push_back(boxComplete);

	Grass* grass = new Grass(20.f, 20.f, 10.f, 10.f, 10.f, "../assets/images/grass_alpha.png");
	gObjects.push_back(grass);

	GlassParapet* glass = new GlassParapet(200.f, "../assets/images/windowV.jpg");
	mat4 glassTras = translate(mat4(1.0f), vec3(0.0f, -100.0f, 0.0f));
	glass->setModelMat(glassTras * glass->modelMat());
	gObjects.push_back(glass);

	Star3D* star = new Star3D(25.f, 16, 25.f, "../assets/images/baldosaP.png");
	mat4 starTras = translate(mat4(1.0f), vec3(-25.0f, -25.0f, 50.0f));
	star->setModelMat(starTras * star->modelMat());
	gObjects.push_back(star);

	Photo* photo = new Photo();
	mat4 photoRot = rotate(mat4(1.0f), glm::radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	mat4 photoTras = translate(mat4(1.0f), vec3(0.0f, 0.0f, -100.0f));
	photo->setModelMat(photoTras * photoRot * photo->modelMat());
	gObjects.push_back(photo);
}