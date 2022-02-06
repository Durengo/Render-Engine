#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "renderer.h"

shader::shader(const std::string& filepath) :
	m_Filepath(filepath), m_RendererID(0) {
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
	isCacheEmpty();
}

shader::~shader() {
	GLCall(glDeleteProgram(m_RendererID));
	isCacheEmpty();
}

ShaderProgramSource shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		//char message[length]; //this does not work with visual studio compiler!!!
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!"
			<< std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void shader::Bind() const {
	GLCall(glUseProgram(m_RendererID));
}

void shader::Unbind() const {
	GLCall(glUseProgram(0));
}

void shader::setUniform1i(const std::string& name, int value) {
	GLCall(glUniform1i(getUniformLocation(name), value));
}

void shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
	GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,
		&matrix[0][0])); //transpose if matrix is by row in this case it is column major
}

int shader::getUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "'doesn't exist!\n";
	m_UniformLocationCache[name] = location;

	//maybe caching is breaking this code?

	return location;
}

void shader::isCacheEmpty() {
	bool locale = m_UniformLocationCache.empty();
	if (locale == 0) {
		std::cout << "CACHE IS EMPTY.\n";
	}
	else {
		std::cout << "CACHE IS NOT EMPTY\n OUTPUT: " << locale << std::endl;
	}
}
