#pragma once

#include <string>
#include <vector>

namespace Engine
{
class IOManager
{
public:
    static bool readFileToBuffer(const std::string &filePath, std::vector<unsigned char> &buffer);
};

} // namespace Engine
