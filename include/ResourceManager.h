#pragma once

#include "TextureCache.h"
#include "GLTexture.h"

namespace Engine {
class ResourceManager
{
public:
    static GLTexture getTexture( std::string texturePath );

private:
    static TextureCache _textureCache;
};

} // namespace Engine
