#include "testMultipleRectangleTextures.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

test::testMultipleRectangleTextures::testMultipleRectangleTextures()
				: m_Renderer(std::make_unique<renderer>()), width(1920), height(1080),
						m_Proj(glm::ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f, 1.0f)),
						m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(0, 0, 0),
						m_TranslationB(100, 200, 0) {
		float positions[] = {
						-50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 0.0f,//0
						-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f,//1
						50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f,//2
						50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f,//3

		};
		unsigned int indices[] = {
						0, 1, 2,
						2, 3, 0
		};

		m_VAO = std::make_unique<vertexArray>();
		m_VBO = std::make_unique<vertexBuffer>(positions, 4 * 6 * sizeof(float));
		vertexBufferLayout layout;
		layout.PushFloat(4);
		layout.PushFloat(2);
		m_VAO->addBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<indexBuffer>(indices, 6);
		m_Shader = std::make_unique<shader>("res/shaders/multipleProjectionMetricesWithTextures.shader");
		m_Shader->Bind();
		m_Texture = std::make_unique<texture>("res/textures/jim.jpg");
		m_Texture->Bind(0);
		m_Shader->setUniform1i("u_Texture", 0);

}

test::testMultipleRectangleTextures::~testMultipleRectangleTextures() {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testMultipleRectangleTextures::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testMultipleRectangleTextures::onRender() {

		m_Texture->Bind();
		{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
				glm::mat4 mvp = m_Proj * m_View * model;
				m_Shader->Bind();
				m_Shader->setUniformMat4f("u_MVP", mvp);
				m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
		}
		{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
				glm::mat4 mvp = m_Proj * m_View * model;
				m_Shader->Bind();
				m_Shader->setUniformMat4f("u_MVP", mvp);
				m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
		}
}

void test::testMultipleRectangleTextures::onImGuiRender() {
		ImGui::Text("Polygon mode:");
		if (ImGui::Button("Enable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		if (ImGui::Button("Disable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, width);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, width);

}
