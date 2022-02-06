#include "testTextureNoAbstraction.h"

#include "../Engine/Core/GLErrorHandler.h"

#include <imgui.h>

test::testTextureNoAbstraction::testTextureNoAbstraction(int width, int height) {
}

test::testTextureNoAbstraction::testTextureNoAbstraction() {
	float vertices[] = {
					0.5f, 0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					-0.5f, -0.5f, 0.0f,
					-0.5f, 0.5f, 0.0f
	};
	unsigned int indices[] = {
					0, 1, 3,
					1, 2, 3
	};
	unsigned int EBO;
	GLCall(glGenBuffers(1, &EBO));
	unsigned int VBO = 0;
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), indices, GL_STATIC_DRAW));

	const char* vertexShaderSource = "#version 330 core\n"
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
	}
	else {
		std::cout << "VERTEX SHADERS COMPILED.\n";
	}

	const char* fragmentShaderSource = "#version 330 core\n"
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
	}
	else {
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
	}
	else {
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
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glEnableVertexAttribArray(0));
	m_ShaderProgram = shaderProgram;
	m_VAO = VAO;
	m_EBO = EBO;
	m_VBO = VBO;
	/*streamline code:
	unsigned int VBO, VAO, EBO;
	 glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	*/
}

test::testTextureNoAbstraction::~testTextureNoAbstraction() {
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteProgram(m_ShaderProgram);
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTextureNoAbstraction::onUpdate(timestep deltaTime) {
	test::onUpdate(deltaTime);
}

void test::testTextureNoAbstraction::onRender() {
	//draw
	GLCall(glUseProgram(m_ShaderProgram));
	GLCall(glBindVertexArray(m_VAO));
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void test::testTextureNoAbstraction::onImGuiRender() {
	ImGui::Text("Polygon mode:");
	if (ImGui::Button("Enable")) {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	}
	if (ImGui::Button("Disable")) {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	}
}
