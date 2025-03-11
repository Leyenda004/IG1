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

	BoxOutline* box = new BoxOutline(100.f,"../assets/images/container.jpg","../assets/images/papelE.png");
	gObjects.push_back(box);
	//
	Star3D* star = new Star3D(100.f, 16, 100.f,"../assets/images/baldosaP.png");
	gObjects.push_back(star);

	Photo* photo = new Photo();
	gObjects.push_back(photo);
	
	GlassParapet* glass = new GlassParapet(200.f, "../assets/images/windowV.jpg");
	gObjects.push_back(glass);

	//Box* boxComplete = new Box(100.f);
	//gObjects.push_back(boxComplete);
}