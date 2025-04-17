#include "ColorMaterialEntity.h"

using namespace glm;

ColorMaterialEntity::ColorMaterialEntity() {
	mShader = Shader::get("simple_light");
    mShaderAux = Shader::get("normals");
}

void ColorMaterialEntity::render(mat4 const& modelViewMat) const {
    if (mMesh != nullptr) {
        mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
        mShader->use();
        mShader->setUniform("simple_light", modelViewMat);
        upload(aMat);
        mMesh->render();
    }
    
    if (mMesh != nullptr && mShowNormals) {
       mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
       mShaderAux->use();
       mShaderAux->setUniform("normals", modelViewMat);
       upload(aMat);
       mMesh->render();
    }
}