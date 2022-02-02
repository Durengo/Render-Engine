#include "testRectangleAbstraction.h"

#include <imgui.h>

test::testRectangleAbstraction::testRectangleAbstraction()
				: m_Renderer(std::make_unique<renderer>()) {
		float positions[] = {
						-0.5f, -0.5f, 0.0f, 0.0f, //0
						-0.5f, 0.5f, 0.0f, 0.0f, //1
						0.5f, 0.5f, 0.0f, 0.0f, //2
						0.5f, -0.5f, 0.0f, 0.0f //3
		};
		unsigned int indices[] = {
						0, 1, 3,
						3, 2, 1
		};
		m_VAO = std::make_unique<vertexArray>();
		m_VBO = std::make_unique<vertexBuffer>(positions, 4 * 4 * sizeof(float));
		vertexBufferLayout layout;
		layout.PushFloat(2);
		layout.PushFloat(2);
		m_VAO->addBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<indexBuffer>(indices, 6);
		m_Shader = std::make_unique<shader>("../source/res/shaders/triangle.shader");
		m_Shader->Bind();
		m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

test::testRectangleAbstraction::~testRectangleAbstraction() {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testRectangleAbstraction::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testRectangleAbstraction::onRender() {
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
}

void test::testRectangleAbstraction::onImGuiRender() {
		ImGui::Text("Polygon mode:");
		if (ImGui::Button("Enable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		if (ImGui::Button("Disable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
}
