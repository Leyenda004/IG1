#pragma once
#include "SingleColorEntity.h"
// !!
#include "Shader.h"
class ColorMaterialEntity :
    public SingleColorEntity
{
public:
    ColorMaterialEntity();
    ~ColorMaterialEntity() {};
    void render(glm::mat4 const& modelViewMat) const override;
    static void toggleShowNormals() { mShowNormals = !mShowNormals; }
private:
    inline static bool mShowNormals = true;
    Shader* mShaderAux; // shader adicional para normales
};

