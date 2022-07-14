#include "testTriangleAbstraction.h"

#include <imgui.h>

test::testTriangleAbstraction::testTriangleAbstraction()
	: m_Renderer(std::make_unique<renderer>())
{
	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f};
	unsigned int indices[] = {
		0, 1, 2};

	// here VAO stuff
	m_VAO = std::make_unique<vertexArray>();
	// vertexArray VAO;
	// auto bound!!!
	m_VBO = std::make_unique<vertexBuffer>(positions, 3 * 4 * sizeof(float));
	// vertexBuffer VBO(positions, 3 * 2 * sizeof(float));
	// va.addBuffer(vb);
	// layout here
	vertexBufferLayout layout;
	layout.PushFloat(2);
	layout.PushFloat(2);
	m_VAO->addBuffer(*m_VBO, layout);
	// VAO.addBuffer(VBO, layout);
	// here vertexattribpointer and enablevertexattribarray

	m_IBO = std::make_unique<indexBuffer>(indices, 3);
	// indexBuffer IBO(indices, 3);

	// shader

	m_Shader = std::make_unique<shader>("res/shaders/triangle.shader");
	m_Shader->Bind();
	m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	m_VAO->Unbind();
	m_IBO->Unbind();
	m_VBO->Unbind();
	m_Shader->Unbind();

	//		shader shader("../res/shaders/another.shader");
	//		shader.Bind();
	//		shader.setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	// unbind everything but then rebind everything in loop!!!!! VAO/VBO/IBO/shader
	// renderer.draw automatically binds VAO IBO and shader!!!!!
}

test::testTriangleAbstraction::~testTriangleAbstraction()
{
	// destructors called in VAO VBO IBO Shader = unbind;
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTriangleAbstraction::onUpdate(timestep deltaTime)
{
	test::onUpdate(deltaTime);
}

void test::testTriangleAbstraction::onRender()
{
	// draw
	// GLCall(glUseProgram(m_ShaderProgram));
	// GLCall(glBindVertexArray(m_VAO)); this is bound by va.Bind

	// if making color change everyframe first bind shader then set uniform!

	// shader.bind?
	// setuniform4f?
	//		va.Bind();
	//		ib.Bind();
	// renderer binds everything automatically.
	m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	// renderer.draw(VAO, IBO, shader);
}

void test::testTriangleAbstraction::onImGuiRender()
{
	ImGui::Text("Polygon mode:");
	if (ImGui::Button("Enable"))
	{
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	}
	if (ImGui::Button("Disable"))
	{
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	}
}
