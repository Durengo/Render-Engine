#include "testTriangleColor.h"

#include <imgui.h>

test::testTriangleColor::testTriangleColor()
				: m_Renderer(std::make_unique<renderer>()), rgba{1.0f, 1.0f, 1.0f, 1.0f} {

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		float positions[] = {
						-0.5f, -0.5f, 0.0f, 0.0f,
						0.0f, 0.5f, 0.0f, 0.0f,
						0.5f, -0.5f, 0.0f, 0.0f
		};
		unsigned int indices[] = {
						0, 1, 2
		};

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

test::testTriangleColor::~testTriangleColor() {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTriangleColor::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testTriangleColor::onRender() {
		m_Shader->Bind();
		m_Shader->setUniform4f("u_Color", rgba[0], rgba[1], rgba[2], rgba[3]);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
}

void test::testTriangleColor::onImGuiRender() {
		ImGui::ColorEdit4("Triangle Color", rgba);
		{
				ImGui::Text("Polygon mode:");
				if (ImGui::Button("Enable")) {
						GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
				}
				if (ImGui::Button("Disable")) {
						GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
				}
		}
}
