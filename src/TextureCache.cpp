#include "TextureCache.h"

#include <iostream>

#include "ImageLoader.h"

namespace Engine
{
GLTexture TextureCache::getTexture(const std::string &texturePath)
{
    if (auto mit = m_textureMap.find(texturePath); mit == m_textureMap.end())
    {
        // Load a new texture
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        m_textureMap[texturePath] = newTexture;

        std::cout << "Loaded texture !" << std::endl;
        return newTexture;
    }
    else
    {
        std::cout << "Using cached texture !" << std::endl;
        return mit->second;
    }
}

} // namespace Engine
