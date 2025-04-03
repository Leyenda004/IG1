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

	//CRISTALERA - Medida de los lados en ancho y alto, archivo a cargar
	GlassParapet* glass = new GlassParapet(200.f, "../assets/images/windowV.jpg");
	gObjectsTranslucid.push_back(glass);

	//SUELO
	Ground* ground = new Ground();
	Texture* tex = new Texture();
	tex->load("../assets/images/baldosaC.png", 255);
	ground->setTexture(tex);
	gObjects.push_back(ground);

	//CAJA VACIA - Medida de los lados en ancho y alto, archivo a cargar para caras externas, archivo a cargar para caras internas
	//BoxOutline* box = new BoxOutline(100.f,"../assets/images/container.jpg","../assets/images/papelE.png");
	//gObjects.push_back(box);

	//CAJA - Medida de los lados en ancho y alto, PosicionX, PosicionY, PosicionZ
	Box* boxComplete = new Box(75.f, -62.5f, 37.5f, -62.5f);
	gObjects.push_back(boxComplete);

	//HIERBA - Anchura, Altura, PosicionX, PosicionY, PosicionZ, archivo a cargar
	Grass* grass1 = new Grass(25.f, 25.f, -25.f/2, 12.5f, -25.f/2, "../assets/images/grass_alpha.png");
	Grass* grass2 = new Grass(25.f, 25.f, -25.f/2, 12.5f, 25.f/2, "../assets/images/grass_alpha.png");
	Grass* grass3 = new Grass(25.f, 25.f, 25.f/2, 12.5f, -25.f/2, "../assets/images/grass_alpha.png");
	Grass* grass4 = new Grass(25.f, 25.f, 25.f/2, 12.5f, 25.f/2, "../assets/images/grass_alpha.png");
	gObjects.push_back(grass1);
	gObjects.push_back(grass2);
	gObjects.push_back(grass3);
	gObjects.push_back(grass4);

	//ESTRELLA - Radio exterior, numero de puntas, distancia desde el centro de la estrella, PosicionX, PosicionY, PosicionZ, archivo a cargar
	Star3D* star = new Star3D(25.f, 16, 25.f, -62.5f, 100.0f, -62.5f,"../assets/images/baldosaP.png");
	gObjects.push_back(star);

	//FOTO - Anchura, Altura
	Photo* photo = new Photo(40,30);
	mat4 photoTras = translate(mat4(1.0f), vec3(50.0f, 10.0f, 50.0f));
	photo->setModelMat(photoTras * photo->modelMat());
	gObjects.push_back(photo);

}