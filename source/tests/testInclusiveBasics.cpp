#include "testInclusiveBasics.h"

#include <imgui.h>
#include <gtc/matrix_transform.hpp>

test::testInclusiveBasics::testInclusiveBasics()
				: m_Renderer(std::make_unique<renderer>()), width(1920), height(1080),
						m_Proj(glm::ortho(0.0f, (float) width, 0.0f, (float) height, -1.0f, 1.0f)),
						m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), camx(0.0f), camy(0.0f),
						m_ClearColor{0.0f, 0.0f, 0.0f, 1.0f}, rgba{1.0f, 1.0f, 1.0f, 1.0f}, m_TranslationA(0, 0, 0),
						m_TranslationB(0, 0, 0), m_TranslationC(0, 0, 0) {
		//Rectangle (BUFFER 0):
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
		m_Shader = std::make_unique<shader>("../source/res/shaders/multipleProjectionMetricesWithTextures.shader");
		m_Shader->Bind();
		m_Texture = std::make_unique<texture>("../source/res/textures/jim.jpg");
		m_Texture->Bind(0);
		m_Shader->setUniform1i("u_Texture", 0);
		//Triangle (BUFFER 1):
		float positionsTriangle[] = {
						-50.0f, -50.0f, 0.0f, 1.0f,
						0.0f, 50.0f, 0.0f, 1.0f,
						50.0f, -50.0f, 0.0f, 1.0f
		};
		unsigned int indicesTriangle[] = {
						0, 1, 2
		};
		m_VAO1 = std::make_unique<vertexArray>();

		m_VBO1 = std::make_unique<vertexBuffer>(positionsTriangle, 3 * 4 * sizeof(float));

		vertexBufferLayout layout2;
		layout.PushFloat(4);

		m_VAO1->addBuffer(*m_VBO1, layout2);

		m_IBO1 = std::make_unique<indexBuffer>(indicesTriangle, 3);

		m_Shader1 = std::make_unique<shader>("../res/shaders/projectionMetrices.shader");
		m_Shader1->Bind();
		m_Shader1->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
}

test::testInclusiveBasics::~testInclusiveBasics() {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testInclusiveBasics::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testInclusiveBasics::onRender() {
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(camx, camy, 0));

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
		{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationC);
				glm::mat4 mvp = m_Proj * m_View * model;
				m_Shader1->Bind();
				m_Shader1->setUniformMat4f("u_MVP", mvp);
				m_Renderer->draw(*m_VAO1, *m_IBO1, *m_Shader1);
		}
}

void test::testInclusiveBasics::onImGuiRender() {
		ImGui::Text("Polygon mode:");
		if (ImGui::Button("Enable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		if (ImGui::Button("Disable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, width);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, width);
		ImGui::SliderFloat3("Translation C", &m_TranslationC.x, 0.0f, width);
		ImGui::Text("Application avarage %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
														ImGui::GetIO().Framerate);
		ImGui::SliderFloat2("Camera", &camx, 0.0f, width);

}