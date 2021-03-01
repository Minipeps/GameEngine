#pragma once

#include "TextureCache.h"
#include "GLTexture.h"


class ResourceManager
{
public:
    static GLTexture getTexture(std::string texturePath);
    
private:
    static TextureCache _textureCache;
};