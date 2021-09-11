#include "GLSLProgram.h"

#include <fstream>
#include <vector>

#include "Errors.h"

namespace Engine
{

void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath,
                                 const std::string &fragmentShaderFilepath)
{
    // Get a program object.
    m_programID = glCreateProgram();

    // Create the vertex shader object, and store its ID
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0)
    {
        fatalError("Vertex shader failed to be created!");
    }

    // Create the fragment shader object, and store its ID
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0)
    {
        fatalError("Fragment shader failed to be created!");
    }

    // Compile each shader
    compileShader(vertexShaderFilePath, m_vertexShaderID);
    compileShader(fragmentShaderFilepath, m_fragmentShaderID);
}

void GLSLProgram::linkShaders() const
{
    // Attach our shaders to our program
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    // Link our program
    glLinkProgram(m_programID);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(m_programID);
        // Don't leak shaders either.
        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);

        // print the error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link!");
    }

    // Always detach shaders after a successful link.
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

// Adds an attribute to our shader. SHould be called between compiling and linking.
void GLSLProgram::addAttribute(const std::string &attributeName)
{
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const std::string &uniformName) const
{
    GLuint location = glGetUniformLocation(m_programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX)
    {
        fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;
}

// enable the shader, and all its attributes
void GLSLProgram::use() const
{
    glUseProgram(m_programID);
    // enable all the attributes we added with addAttribute
    for (int i = 0; i < m_numAttributes; i++)
    {
        glEnableVertexAttribArray(i);
    }
}

// disable the shader
void GLSLProgram::unuse() const
{
    glUseProgram(0);
    for (int i = 0; i < m_numAttributes; i++)
    {
        glDisableVertexAttribArray(i);
    }
}

// Compiles a single shader file
void GLSLProgram::compileShader(const std::string &filePath, GLuint id) const
{
    // Open the file
    std::ifstream shaderFile(filePath);
    if (shaderFile.fail())
    {
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath);
    }

    // File contents stores all the text in the file
    std::string fileContents = "";
    // line is used to grab each line of the file
    std::string line;

    // Get all the lines in the file and add it to the contents
    while (std::getline(shaderFile, line))
    {
        fileContents += line + "\n";
    }

    shaderFile.close();

    // get a pointer to our file contents c string
    const char *contentsPtr = fileContents.c_str();
    // tell opengl that we want to use fileContents as the contents of the shader file
    glShaderSource(id, 1, &contentsPtr, nullptr);

    // compile the shader
    glCompileShader(id);

    // check for errors
    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(id); // Don't leak the shader.

        // Print error log and quit
        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader " + filePath + " failed to compile");
    }
}

} // namespace Engine
