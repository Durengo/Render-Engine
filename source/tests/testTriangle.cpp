#include "testTriangle.h"

#include <imgui.h>

#include "../Engine/Core/GLErrorHandler.h"

test::testTriangle::testTriangle(int width, int height) {
}

test::testTriangle::testTriangle() {
		float vertices[] = {
						-0.5f, -0.5f, 0.0f,
						0.5f, -0.5f, 0.0f,
						0.0f, 0.5f, 0.0f
		};
		unsigned int VBO;
		GLCall(glGenBuffers(1, &VBO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

		const char *vertexShaderSource = "#version 330 core\n"
																																			"layout (location = 0) in vec3 aPos;\n"
																																			"\n"
																																			"void main()\n"
																																			"{\n"
																																			"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
																																			"}\0";
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLCall(glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr));
		GLCall(glCompileShader(vertexShader));
		int success;
		char infoLog[512];
		GLCall(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));
		if (!success) {
				glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		} else {
				std::cout << "VERTEX SHADERS COMPILED.\n";
		}

		const char *fragmentShaderSource = "#version 330 core\n"
																																					"out vec4 FragColor;\n"
																																					"\n"
																																					"void main()\n"
																																					"{\n"
																																					"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
																																					"}";
		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		GLCall(glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr));
		GLCall(glCompileShader(fragmentShader));
		GLCall(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));
		if (!success) {
				glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		} else {
				std::cout << "FRAGMENT SHADERS COMPILED.\n";
		}
		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();
		GLCall(glAttachShader(shaderProgram, vertexShader));
		GLCall(glAttachShader(shaderProgram, fragmentShader));
		GLCall(glLinkProgram(shaderProgram));
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
				glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
				std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
		} else {
				std::cout << "LINKING SHADERS COMPILED.\n";
		}
		GLCall(glUseProgram(shaderProgram));
		GLCall(glDeleteShader(vertexShader));
		GLCall(glDeleteShader(fragmentShader));
		unsigned int VAO;
		GLCall(glGenVertexArrays(1, &VAO));
		GLCall(glBindVertexArray(VAO));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0));
		GLCall(glEnableVertexAttribArray(0));
		m_ShaderProgram = shaderProgram;
		m_VAO = VAO;
		m_VBO = VBO;
}

test::testTriangle::~testTriangle() {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		glDeleteProgram(m_ShaderProgram);
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTriangle::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testTriangle::onRender() {
		//draw
		GLCall(glUseProgram(m_ShaderProgram));
		GLCall(glBindVertexArray(m_VAO));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void test::testTriangle::onImGuiRender() {
		ImGui::Text("Polygon mode:");
		if (ImGui::Button("Enable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		if (ImGui::Button("Disable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
}
