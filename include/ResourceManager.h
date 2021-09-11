#pragma once

#include "GLTexture.h"
#include "TextureCache.h"

namespace Engine
{
class ResourceManager
{
public:
    static GLTexture getTexture(std::string texturePath);

private:
    static TextureCache m_textureCache;
};

} // namespace Engine
