#pragma once

#include <string>
#include <unordered_map>

#include <glm.hpp>

struct ShaderProgramSource {
				std::string VertexSource;
				std::string FragmentSource;
};

class shader {
private:
				std::string m_Filepath;

				unsigned int m_RendererID;

				std::unordered_map<std::string, int> m_UniformLocationCache;
//caching system
public:

				shader(const std::string &filepath);

				~shader();

				void Bind() const;

				void Unbind() const;

// Set uniforms
				void setUniform1i(const std::string &name, int value);

				void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

				void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

				void isCacheEmpty();

private:
				ShaderProgramSource ParseShader(const std::string &filepath);

				unsigned int CompileShader(unsigned int type, const std::string &source);

				unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

				int getUniformLocation(const std::string &name);

};
