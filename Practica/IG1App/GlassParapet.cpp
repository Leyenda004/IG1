#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length, std::string mTextureOut)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
	mShader = Shader::get("texture");


	mTextureAux = new Texture();
	mTextureAux->load(mTextureOut, 255);
	setTexture(mTextureAux);
}
