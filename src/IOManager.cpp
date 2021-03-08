#include "IOManager.h"

#include <fstream>

namespace Engine {

bool IOManager::readFileToBuffer( std::string filePath, std::vector<unsigned char>& buffer )
{
    std::ifstream file( filePath, std::ios::binary );
    if (file.fail())
    {
        perror( filePath.c_str() );
        return false;
    }

    // Seek to the end of the file
    file.seekg( 0, std::ios::end );
    // File size
    int fileSize = (int)file.tellg();
    file.seekg( 0, std::ios::beg );
    // Safety
    fileSize -= file.tellg();

    // Read file to buffer
    buffer.resize( fileSize );
    file.read( (char*)&(buffer[0]), fileSize );

    file.close();

    return true;
}

} // namespace Engine
