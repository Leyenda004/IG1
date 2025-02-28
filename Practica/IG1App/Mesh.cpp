#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
 , mTCO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}

		//EDITABLE

		if (vTexCoords.size() > 0) {
			glGenBuffers(1, &mTCO);
			glBindBuffer(GL_ARRAY_BUFFER, mTCO);
			glBufferData(GL_ARRAY_BUFFER, vTexCoords.size() * sizeof(vec2), vTexCoords.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), nullptr);
			glEnableVertexAttribArray(2);
		}
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}

		//EDITABLE 

		if (mTCO != NONE) {
			glDeleteBuffers(1, &mTCO);
			//DUDA
			mTCO = NONE;
		}
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

//EDITABLE

// Crea un polígono regular de n lados y radio r
Mesh*
Mesh::generateRegularPolygon(GLuint num, GLdouble r) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;
	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	//PLANO X, PLANO Y, PLANO Z
	GLdouble ang = 90.0f;
	GLdouble diff = 360.0f / num;
	GLdouble x = 0.0f, y = 0.0f;
	for (GLint i = 0; i < num; ++i) {
		x = r * cos(radians(ang));
		y = r * sin(radians(ang));
		ang += diff;
		mesh->vVertices.emplace_back(x, y, 0.0f);
	}
	return mesh;
}

// Crea un triángulo equilátero de colores de lado r partiendo de la maya de un polígono regular de 3 lados
Mesh*
Mesh::generateRGBTriangle(GLdouble r) {	
	Mesh* mesh = Mesh::generateRegularPolygon(3, r);
	mesh->mPrimitive = GL_TRIANGLES;
	mesh->vColors.reserve(3);
	mesh->vColors.emplace_back(1.0f, 0.0f, 0.0f, 1.0f);
	mesh->vColors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->vColors.emplace_back(0.0f, 0.0f, 1.0f, 1.0f);
	return mesh;
}

// Crea un rectángulo de lados w y h
Mesh*
Mesh::generateRectangle(GLdouble w, GLdouble h) {
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 4;
	//PLANO X, PLANO Y, PLANO Z
	GLdouble x = w, y = h, z = 0.f;

	mesh->vVertices.emplace_back(x, y, z);
	mesh->vVertices.emplace_back(-x, y, z);
	mesh->vVertices.emplace_back(x, -y, z);
	mesh->vVertices.emplace_back(-x, -y, z);

	// En este orden devuelve el rectángulo relleno?
	//mesh->vVertices.emplace_back(x, -y, z);
	//mesh->vVertices.emplace_back(-x, -y, z);
	//mesh->vVertices.emplace_back(x, y, z);
	//mesh->vVertices.emplace_back(-x, y, z);

	return mesh;
}

// Crea un rectángulo de lados w y h con colores
Mesh*
Mesh::generateRGBRectangle(GLdouble w, GLdouble h) {
	Mesh* mesh = generateRectangle(w, h);
	mesh->vVertices.reserve(4);
	mesh->vColors.emplace_back(1.0f, 0.0f, 0.0f, 1.0f);
	mesh->vColors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->vColors.emplace_back(0.0f, 1.0f, 0.0f, 1.0f);
	mesh->vColors.emplace_back(0.0f, 0.0f, 1.0f, 1.0f);
	return mesh;
}

// Crea un cubo de lado length
Mesh*
Mesh::generateCube(GLdouble length) {
	int l = length/2;
	Mesh* mesh = new Mesh();

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);

	//-Y
	mesh->vVertices.emplace_back(-l, -l, -l);//0
	mesh->vVertices.emplace_back(l, -l, -l);//1
	mesh->vVertices.emplace_back(l, -l, l);//2
	mesh->vVertices.emplace_back(-l, -l, -l);//0
	mesh->vVertices.emplace_back(l, -l, l);//2
	mesh->vVertices.emplace_back(-l, -l, l);//3

	//-X
	mesh->vVertices.emplace_back(-l, -l, l);//3
	mesh->vVertices.emplace_back(-l, l, l);//4
	mesh->vVertices.emplace_back(-l, l, -l);//5
	mesh->vVertices.emplace_back(-l, -l, l);//3
	mesh->vVertices.emplace_back(-l, l, -l);//5
	mesh->vVertices.emplace_back(-l, -l, -l);//0

	//-Z
	mesh->vVertices.emplace_back(-l, -l, -l);//0
	mesh->vVertices.emplace_back(-l, l, -l);//5
	mesh->vVertices.emplace_back(l, -l, -l);//1
	mesh->vVertices.emplace_back(l, -l, -l);//1
	mesh->vVertices.emplace_back(-l, l, -l);//5
	mesh->vVertices.emplace_back(l, l, -l);//6

	//Y
	mesh->vVertices.emplace_back(-l, l, l);//4
	mesh->vVertices.emplace_back(l, l, -l);//6
	mesh->vVertices.emplace_back(-l, l, -l);//5
	mesh->vVertices.emplace_back(-l, l, l);//4
	mesh->vVertices.emplace_back(l, l, l);//7
	mesh->vVertices.emplace_back(l, l, -l);//6

	//X
	mesh->vVertices.emplace_back(l, l, -l);//6
	mesh->vVertices.emplace_back(l, l, l);//7
	mesh->vVertices.emplace_back(l, -l, -l);//1
	mesh->vVertices.emplace_back(l, -l, -l);//1
	mesh->vVertices.emplace_back(l, l, l);//7
	mesh->vVertices.emplace_back(l, -l, l);//2

	//Z
	mesh->vVertices.emplace_back(l, -l, l);//2
	mesh->vVertices.emplace_back(l, l, l);//7
	mesh->vVertices.emplace_back(-l, -l, l);//3
	mesh->vVertices.emplace_back(l, l, l);//7
	mesh->vVertices.emplace_back(-l, l, l);//4
	mesh->vVertices.emplace_back(-l, -l, l);//3


	mesh->mPrimitive = GL_TRIANGLES;
	return mesh;

	// PRUEBA MENOS VÉRTICES, A OPTIMIZAR EN FUTURO
	//mesh->vVertices.emplace_back(l, l, l);		//1
	//mesh->vVertices.emplace_back(-l, l, l);	//2
	//mesh->vVertices.emplace_back(-l, l, -l);	//3
	//mesh->vVertices.emplace_back(-l, -l, -l);	//4
	//mesh->vVertices.emplace_back(l, l, -l);	//5
	//mesh->vVertices.emplace_back(l, -l, -l);		//6
	//mesh->vVertices.emplace_back(l, -l, l);		//7
	//mesh->vVertices.emplace_back(-l, -l, l);		//8
	//mesh->vVertices.emplace_back(l, l, l);		//1
	//mesh->vVertices.emplace_back(-l, l, l);	//2
	//mesh->vVertices.emplace_back(-l, -l, l);		//8
	//mesh->vVertices.emplace_back(-l, l, -l);	//4

}

// Crea un cubo a partir del método GenerateCube y le asigna colores a cada cara
Mesh* 
Mesh::generateRGBCubeTriangles(GLdouble length) {
	Mesh* mesh = generateCube(length);
	// Reservar los vértices a los que les vas a asignar color
	mesh->vColors.reserve(36);

	// Definir los colores de cada cara y los números de vértices en los que se cambia de cara
	int r = 0, g = 0, b = 0;
	int minusYI = 0, minusYF = 5, minusXI = 6, minusXF = 11, minusZI = 12, minusZF = 17,
		YI = 18, YF = 23, XI = 24, XF = 29, ZI = 30, ZF = 35;

	// Asignar colores a cada vértice
	for (int i = 0; i < 36; ++i) {
		if ((i >= minusYI && i <= minusYF) || (i >= YI && i <= YF)) { r = 0; g = 0; b = 1; }
		if ((i >= minusXI && i <= minusXF) || (i >= XI && i <= XF)) { r = 0; g = 1; b = 0; }
		if ((i >= minusZI && i <= minusZF) || (i >= ZI && i <= ZF)) { r = 1; g = 0; b = 0; }
		mesh->vColors.emplace_back(r, g, b, 1.0f);
	}

	return mesh;
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h)
{
	Mesh* mesh = generateRectangle(w,h);
	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(1, 1); //1
	mesh->vTexCoords.emplace_back(0, 1); //2
	mesh->vTexCoords.emplace_back(1, 0); //3
	mesh->vTexCoords.emplace_back(0, 0); //4
	return mesh;
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
	Mesh* mesh = generateRectangle(w, h);
	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(rw, rh); //1
	mesh->vTexCoords.emplace_back(0, rh); //2
	mesh->vTexCoords.emplace_back(rw, 0); //3
	mesh->vTexCoords.emplace_back(0, 0); //4
	return mesh;
}

Mesh* Mesh::generateBoxOutline(GLdouble length)
{
	Mesh* mesh = new Mesh();
	int l = length / 2;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	//4,8,7,6,5,1,2,3,4,8

	//mesh->vVertices.emplace_back(-l, -l, -l);
	//mesh->vVertices.emplace_back(-l, -l, l);
	//mesh->vVertices.emplace_back(l, -l, l);
	//mesh->vVertices.emplace_back(l, -l, -l);
	//mesh->vVertices.emplace_back(l, l, -l);
	//mesh->vVertices.emplace_back(l, l, l);
	//mesh->vVertices.emplace_back(-l, l, l);
	//mesh->vVertices.emplace_back(-l, l, -l);
	//mesh->vVertices.emplace_back(-l, -l, -l);
	//mesh->vVertices.emplace_back(-l, -l, l);
	//
	//mesh->vVertices.emplace_back(-l, l, l);
	//mesh->vVertices.emplace_back(-l, -l, l);
	//mesh->vVertices.emplace_back(l, l, l);
	//mesh->vVertices.emplace_back(l, l, l);
	
	mesh->vVertices.emplace_back(-l, l, -l);
	mesh->vVertices.emplace_back(-l, -l, -l);
	mesh->vVertices.emplace_back(l, l, -l);
	mesh->vVertices.emplace_back(l, -l, -l);
	mesh->vVertices.emplace_back(l, l, l);
	mesh->vVertices.emplace_back(l, -l, l);
	mesh->vVertices.emplace_back(-l, l, l);
	mesh->vVertices.emplace_back(-l, -l, l);
	mesh->vVertices.emplace_back(-l, l, -l);
	mesh->vVertices.emplace_back(-l, -l, -l);




	//mesh->vVertices.emplace_back(l, l, l);		//1
	//mesh->vVertices.emplace_back(-l, l, l);	//2
	//mesh->vVertices.emplace_back(-l, l, -l);	//3
	//mesh->vVertices.emplace_back(-l, -l, -l);	//4		
	//mesh->vVertices.emplace_back(l, l, -l);	//5
	//mesh->vVertices.emplace_back(l, -l, -l);		//6
	//mesh->vVertices.emplace_back(l, -l, l);		//7
	//mesh->vVertices.emplace_back(-l, -l, l);		//8

	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	return mesh;


	return nullptr;
}

Mesh* Mesh::generateBoxOutlineTexCor(GLdouble length)
{
	Mesh* mesh = generateBoxOutline(length);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	for (int i = 0; i < 5; ++i) {
		mesh->vTexCoords.emplace_back(i * 0.25, 0);
		mesh->vTexCoords.emplace_back(i * 0.25, 1);
	}

	return mesh;
}
