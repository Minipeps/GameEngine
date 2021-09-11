#include "TextureCache.h"

#include <iostream>

#include "ImageLoader.h"

namespace Engine
{
GLTexture TextureCache::getTexture(const std::string &texturePath)
{
    auto mit = m_textureMap.find(texturePath);

    if (mit == m_textureMap.end())
    {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        m_textureMap.insert(make_pair(texturePath, newTexture));

        std::cout << "Loaded texture !" << std::endl;
        return newTexture;
    }

    std::cout << "Using cached texture !" << std::endl;
    return mit->second;
}

} // namespace Engine
