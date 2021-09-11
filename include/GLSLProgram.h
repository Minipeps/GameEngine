#pragma once

#include <string>

#include "glad/glad.h"

namespace Engine
{
/*
 * This class handles the compilation, linking, and usage of a GLSL shader program.
 * Reference: http://www.opengl.org/wiki/Shader_Compilation
 */
class GLSLProgram
{
public:
    GLSLProgram();

    void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilepath);

    void linkShaders();

    void addAttribute(const std::string &attributeName);

    GLuint getUniformLocation(const std::string &uniformName);

    void use();
    void unuse();

private:
    void compileShader(const std::string &filePath, GLuint id);

    int m_numAttributes;

    GLuint m_programID;

    GLuint m_fragmentShaderID;
    GLuint m_vertexShaderID;
};

} // namespace Engine
