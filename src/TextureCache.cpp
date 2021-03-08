#include "TextureCache.h"

#include "ImageLoader.h"

#include <iostream>

namespace Engine {

GLTexture TextureCache::getTexture( const std::string& texturePath )
{
    auto mit = _textureMap.find( texturePath );

    if (mit == _textureMap.end())
    {
        GLTexture newTexture = ImageLoader::loadPNG( texturePath );

        _textureMap.insert( make_pair( texturePath, newTexture ) );

        std::cout << "Loaded texture !" << std::endl;
        return newTexture;
    }

    std::cout << "Using cached texture !" << std::endl;
    return mit->second;
}

} // namespace Engine
