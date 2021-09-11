#pragma once

#include <string>

#include "GLTexture.h"

namespace Engine
{
// A 2D quad that can be rendered to the screen
class Sprite
{
public:
    ~Sprite();

    void init(float x, float y, float width, float height, const std::string &texturePath);

    void draw() const;

private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    GLuint m_vboID{0};
    GLTexture m_texture;
};

} // namespace Engine
