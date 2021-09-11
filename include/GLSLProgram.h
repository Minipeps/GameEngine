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
    GLSLProgram() = default;

    void compileShaders(const std::string &vertexShaderFilePath,
                        const std::string &fragmentShaderFilepath);

    void linkShaders() const;

    void addAttribute(const std::string &attributeName);

    GLuint getUniformLocation(const std::string &uniformName) const;

    void use() const;
    void unuse() const;

private:
    void compileShader(const std::string &filePath, GLuint id) const;

    int m_numAttributes{0};

    GLuint m_programID{0};

    GLuint m_fragmentShaderID{0};
    GLuint m_vertexShaderID{0};
};

} // namespace Engine
