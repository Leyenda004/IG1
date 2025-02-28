#pragma once
#include "Entity.h"
class SingleColorEntity :
    public Abs_Entity
{
private:
    glm::dvec4 mColor;
public:
    SingleColorEntity();
    SingleColorEntity(glm::dvec4 color);

    inline glm::dvec4 color() const { return mColor; }
    inline void setColor(glm::dvec4 color) { mColor = color; }

    void render(const glm::mat4&) const override;
};