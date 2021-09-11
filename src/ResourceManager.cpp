#include "ResourceManager.h"

namespace Engine
{
TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
    return m_textureCache.getTexture(texturePath);
}

} // namespace Engine
