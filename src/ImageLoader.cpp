#include "ImageLoader.h"
#include "Errors.h"
#include "picoPNG.h"
#include "IOManager.h"

#include "glad/glad.h"

GLTexture ImageLoader::loadPNG(std::string filePath) {
    GLTexture texture = {};
    
    std::vector<unsigned char> inData;
    std::vector<unsigned char> outData;
    unsigned long width, height;
    
    if (IOManager::readFileToBuffer(filePath, inData) == false) {
        fatalError("failed to load PNG file to buffer !");
    };
    
    int errorCode = decodePNG(outData, width, height, &(inData[0]), inData.size());
    if (errorCode != 0) {
        fatalError("decodePNG failed with error : " + std::to_string(errorCode));
    }
    
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int) width, (int) height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(outData[0]));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    
    texture.width = (int) width;
    texture.height = (int) height;
    
    return texture;
}
