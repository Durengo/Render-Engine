#include "testProjectionMetrices.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

test::testProjectionMetrices::testProjectionMetrices()
				: m_Renderer(std::make_unique<renderer>()), width(1920), height(1080),
						m_Proj(glm::ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f, 1.0f)),
						m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(0, 0, 0) {
		float positions[] = {
						-50.0f, -50.0f, 0.0f, 1.0f,
						0.0f, 50.0f, 0.0f, 1.0f,
						50.0f, -50.0f, 0.0f, 1.0f
		};
		unsigned int indices[] = {
						0, 1, 2
		};

		m_VAO = std::make_unique<vertexArray>();

		m_VBO = std::make_unique<vertexBuffer>(positions, 3 * 4 * sizeof(float));

		vertexBufferLayout layout;
		layout.PushFloat(4);
		m_VAO->addBuffer(*m_VBO, layout);

		m_IBO = std::make_unique<indexBuffer>(indices, 3);

		//m_Shader = std::make_unique<shader>("../res/shaders/triangle.shader");
		m_Shader = std::make_unique<shader>("../source/res/shaders/projectionMetrices.shader");

		m_Shader->Bind();
		m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

}

test::testProjectionMetrices::~testProjectionMetrices() {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testProjectionMetrices::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testProjectionMetrices::onRender() {

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
}

void test::testProjectionMetrices::onImGuiRender() {
		ImGui::Text("Using orthographic matrix (Z Axis unavailable)");
		ImGui::Text("Polygon mode:");
		if (ImGui::Button("Enable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		if (ImGui::Button("Disable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, width);
}
