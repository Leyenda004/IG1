#pragma once
#include "SingleColorEntity.h"
#include "Shader.h"
class ColorMaterialEntity :
    public SingleColorEntity
{
public:
    ColorMaterialEntity();
    ColorMaterialEntity(float r ,float g, float b);
    ColorMaterialEntity(float r ,float g, float b, float a);
    ~ColorMaterialEntity() {};
    void render(glm::mat4 const& modelViewMat) const override;
    static void toggleShowNormals() { mShowNormals = !mShowNormals; }
private:
    inline static bool mShowNormals = false;
    Shader* mShaderAux; // shader adicional para normales
};

