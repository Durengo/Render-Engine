#include "testTriangleColorAnimation.h"

#include <imgui.h>

test::testTriangleColorAnimation::testTriangleColorAnimation()
	: m_Renderer(std::make_unique<renderer>()), r(0.0f), g(0.0f), b(0.0f), br(false), bg(false), bb(false), incrR(0.0f),
	  incrB(0.0f), incrG(0.0f)
{
	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f};
	unsigned int indices[] = {
		0, 1, 2};
	m_VAO = std::make_unique<vertexArray>();
	m_VBO = std::make_unique<vertexBuffer>(positions, 3 * 4 * sizeof(float));
	vertexBufferLayout layout;
	layout.PushFloat(2);
	layout.PushFloat(2);
	m_VAO->addBuffer(*m_VBO, layout);
	m_IBO = std::make_unique<indexBuffer>(indices, 3);
	m_Shader = std::make_unique<shader>("res/shaders/triangle.shader");
	m_Shader->Bind();
	m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

test::testTriangleColorAnimation::~testTriangleColorAnimation()
{
	// destructors called in VAO VBO IBO Shader = unbind;
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTriangleColorAnimation::onUpdate(timestep deltaTime)
{
	if (br)
	{
		if (r >= 1.0f)
		{
			incrR = 0.0f - deltaTime.getSeconds();
		}
		else if (r <= 0.0f)
		{
			incrR = deltaTime.getSeconds();
		}
		r += incrR;
	}
	if (bg)
	{
		if (g >= 1.0f)
		{
			incrG = 0.0f - deltaTime.getSeconds();
		}
		else if (g <= 0.0f)
		{
			incrG = deltaTime.getSeconds();
		}
		g += incrG;
	}
	if (bb)
	{
		if (b >= 1.0f)
		{
			incrB = 0.0f - deltaTime.getSeconds();
		}
		else if (b <= 0.0f)
		{
			incrB = deltaTime.getSeconds();
		}
		b += incrB;
	}
	// std::cout << "R: " << r << " | G: " << g << " | B: " << b << "\n";
}

void test::testTriangleColorAnimation::onRender()
{
	m_Shader->Bind();
	m_Shader->setUniform4f("u_Color", r, g, b, 1.0f);
	m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
}

void test::testTriangleColorAnimation::onImGuiRender()
{
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
	{
		if (ImGui::Checkbox("Cycle red color", &br))
		{
		}
		if (ImGui::Checkbox("Cycle green color", &bg))
		{
		}
		if (ImGui::Checkbox("Cycle blue color", &bb))
		{
		}
	}
}
