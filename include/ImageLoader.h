#pragma once

#include <string>

#include "GLTexture.h"

namespace Engine
{
class ImageLoader
{
public:
    static GLTexture loadPNG(const std::string &filePath);
};

} // namespace Engine
