#include "Texture.h"

#include "Image.h"

#include <vector>

Texture::~Texture()
{
	if (mId != 0)
		glDeleteTextures(1, &mId);
}

void Texture::loadColorBuffer(GLsizei width, GLsizei height, GLuint buffer)
{
	if (mId == 0) init();

	mWidth = width;
	mHeight = height;

	glReadBuffer(buffer);

	glBindTexture(GL_TEXTURE_2D, mId);

	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, mWidth, mHeight, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::savePhoto(const std::string& filename, GLubyte alpha)
{
	if (mId == 0) return;

	// Obtener las dimensiones de la textura
	GLint width = mWidth;
	GLint height = mHeight;

	if (width == 0 || height == 0) return;

	// Crear un buffer para almacenar los datos de la textura
	std::vector<Image::rgba_color> pixels(width * height);

	glBindTexture(GL_TEXTURE_2D, mId);
	//Obtenemos los datos de la textura y lo guardamos en un vector de pixeles tipo image::rgba_color
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	glBindTexture(GL_TEXTURE_2D, 0);

	Image image;
	image.load(pixels.data(), width, height);

	if (alpha != 255)
		image.setAlpha(alpha);

	image.save(filename);
}

void
Texture::init()
{
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);

	// Filters and clamping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // GL_CLAMP
}

void
Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, mId);
}

void
Texture::load(const std::string& name, GLubyte alpha)
{
	if (mId == 0)
		init();

	Image image;
	image.load(name);

	if (alpha != 255)
		image.setAlpha(alpha);

	mWidth = image.width();
	mHeight = image.height();

	GLint level = 0;  // Base image level
	GLint border = 0; // No border

	glBindTexture(GL_TEXTURE_2D, mId);
	glTexImage2D(GL_TEXTURE_2D,
	             level,
	             GL_RGBA,
	             mWidth,
	             mHeight,
	             border,
	             GL_RGBA,
	             GL_UNSIGNED_BYTE,
	             image.data());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void
Texture::setWrap(GLuint wp) // GL_REPEAT, GL_CLAMP_TO_EDGE, ...
{
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wp);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wp);
	glBindTexture(GL_TEXTURE_2D, 0);
}