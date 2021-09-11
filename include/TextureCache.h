#pragma once

#include <map>
#include <string>

#include "GLTexture.h"

namespace Engine
{
class TextureCache
{
public:
    GLTexture getTexture(const std::string &texturePath);

private:
    std::map<std::string, GLTexture> m_textureMap;
};

} // namespace Engine
