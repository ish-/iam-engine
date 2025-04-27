#include "Shader.hpp"
#include <string>
#include <glad/glad.h>
#include <SDL3/SDL_log.h>
#include "../common/LOG.hpp"

GLuint Shader::loadComputeShader (string& compShaderCode)
{
  GLuint ComputeShaderID = glCreateShader(GL_COMPUTE_SHADER);

  GLint Result = GL_FALSE;
  int InfoLogLength;

  printf("Compiling shader : %s\n", "compute");
  char const* ComputeSourcePointer = compShaderCode.c_str();
  glShaderSource(ComputeShaderID, 1, &ComputeSourcePointer, NULL);
  glCompileShader(ComputeShaderID);

  // Check Compute Shader
  glGetShaderiv(ComputeShaderID, GL_COMPILE_STATUS, &Result);
  glGetShaderiv(ComputeShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::string ComputeShaderErrorMessage("", InfoLogLength + 1);
    glGetShaderInfoLog(ComputeShaderID, InfoLogLength, NULL, ComputeShaderErrorMessage.data());
    printf("%s\n", ComputeShaderErrorMessage.c_str());
  }

  printf("Linking program\n");
  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, ComputeShaderID);
  glLinkProgram(ProgramID);

  glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
  glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
  if (InfoLogLength > 0) {
    std::string ProgramErrorMessage("", InfoLogLength + 1);
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage.data());
    auto* errMsg = ProgramErrorMessage.c_str();
    printf("%s\n", errMsg);
    std::string errCheckStr = "ERROR:";
    if (strncmp(errMsg, errCheckStr.c_str(), errCheckStr.size()) == 0)
      return 0;
  }

  glDetachShader(ProgramID, ComputeShaderID);
  glDeleteShader(ComputeShaderID);

  return ProgramID;
}

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
    auto* errMsg = ProgramErrorMessage.c_str();
    printf("%s\n", errMsg);
    std::string errCheckStr = "ERROR:";
    if (strncmp(errMsg, errCheckStr.c_str(), errCheckStr.size()) == 0)
      return 0;
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

    for (int i = 0; i < count; i++)
    {
        glGetActiveAttrib(ProgramID, (GLuint)i, bufSize, &length, &size, &type, name);

        printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
    }

    glGetProgramiv(ProgramID, GL_ACTIVE_UNIFORMS, &count);
    printf("Active Uniforms: %d\n", count);

    for (int i = 0; i < count; i++)
    {
        glGetActiveUniform(ProgramID, (GLuint)i, bufSize, &length, &size, &type, name);
        printf("Uniform #%d Type: %u Size: %u Length: %u Name: %s\n", i, type, size, length, name);
    }
  }

  glDetachShader(ProgramID, VertexShaderID);
  glDetachShader(ProgramID, FragmentShaderID);

  glDeleteShader(VertexShaderID);
  glDeleteShader(FragmentShaderID);

  return ProgramID;
}
