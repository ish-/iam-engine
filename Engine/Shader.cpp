#include "Shader.hpp"
#include <string>
#include <glad/glad.h>
#include <SDL3/SDL_log.h>
#include "../util/LOG.hpp"

GLuint Shader::loadShader(std::string& vertexShaderCode, std::string& fragmentShaderCode)
{
  GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

  GLint Result = GL_FALSE;
  int InfoLogLength;

  printf("Compiling shader : %s\n", "vertex");
  char const* VertexSourcePointer = vertexShaderCode.c_str();
  glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
  glCompileShader(VertexShaderID);

  glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::string VertexShaderErrorMessage("", InfoLogLength + 1);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, VertexShaderErrorMessage.data());
    printf("%s\n", VertexShaderErrorMessage.c_str());
  }

  printf("Compiling shader : %s\n", "fragment");
  char const* FragmentSourcePointer = fragmentShaderCode.c_str();
  glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
  glCompileShader(FragmentShaderID);

  // Check Fragment Shader
  glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::string FragmentShaderErrorMessage("", InfoLogLength + 1);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, FragmentShaderErrorMessage.data());
    printf("%s\n", FragmentShaderErrorMessage.c_str());
  }

  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, VertexShaderID);
  glAttachShader(ProgramID, FragmentShaderID);
  glLinkProgram(ProgramID);

  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::string ProgramErrorMessage("", InfoLogLength + 1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage.data());
    printf("%s\n", ProgramErrorMessage.c_str());
  }

  {
    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 16; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(ProgramID, GL_ACTIVE_ATTRIBUTES, &count);
    printf("Active Attributes: %d\n", count);

    for (uint i = 0; i < count; i++)
    {
        glGetActiveAttrib(ProgramID, (GLuint)i, bufSize, &length, &size, &type, name);

        printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
    }

    glGetProgramiv(ProgramID, GL_ACTIVE_UNIFORMS, &count);
    printf("Active Uniforms: %d\n", count);

    for (uint i = 0; i < count; i++)
    {
        glGetActiveUniform(ProgramID, (GLuint)i, bufSize, &length, &size, &type, name);
        printf("Uniform #%d Type: %u Size: %u Length: %u Name: %s\n", i, type, size, length, name);
    }
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  if (!ProgramID) {
    SDL_Log("loadShaders() == 0");
    std::printf("loading vert(%s) frag(%s)", "vertex", "fragment");
    return EXIT_FAILURE;
  }

  return ProgramID;
}
