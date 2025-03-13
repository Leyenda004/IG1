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

#include "IG1App.h"

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

	Box* boxComplete = new Box(75.f, -62.5f, 37.5f, -62.5f);
	gObjects.push_back(boxComplete);

	Grass* grass1 = new Grass(25.f, 25.f, -25.f/2, 12.5f, -25.f/2, "../assets/images/grass_alpha.png");
	Grass* grass2 = new Grass(25.f, 25.f, -25.f/2, 12.5f, 25.f/2, "../assets/images/grass_alpha.png");
	Grass* grass3 = new Grass(25.f, 25.f, 25.f/2, 12.5f, -25.f/2, "../assets/images/grass_alpha.png");
	Grass* grass4 = new Grass(25.f, 25.f, 25.f/2, 12.5f, 25.f/2, "../assets/images/grass_alpha.png");
	//mat4 grassTras = translate(mat4(1.0f), vec3(-75.0f, 25.0f, -75.0f));
	//grass->setModelMat(grassTras * grass->modelMat());
	gObjects.push_back(grass1);
	gObjects.push_back(grass2);
	gObjects.push_back(grass3);
	gObjects.push_back(grass4);

	Star3D* star = new Star3D(25.f, 16, 25.f, -62.5f, 100.0f, -62.5f,"../assets/images/baldosaP.png");
	gObjects.push_back(star);

	Photo* photo = new Photo(40,30);
	//mat4 photoRot = rotate(mat4(1.0f), glm::radians(-90.f), vec3(1.0f, 0.0f, 0.0f));
	mat4 photoTras = translate(mat4(1.0f), vec3(50.0f, 10.0f, 50.0f));
	photo->setModelMat(photoTras * photo->modelMat());
	gObjects.push_back(photo);

	GlassParapet* glass = new GlassParapet(200.f, "../assets/images/windowV.jpg");
	gObjects.push_back(glass);
}