#include "testTexture.h"

#include "imgui.h"

test::testTexture::testTexture()
				: m_Renderer(std::make_unique<renderer>()) {
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		float positions[] = {
						-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,//0
						-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,//1
						0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,//2
						0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f//3
		};
		unsigned int indices[] = {
						0, 1, 3,
						3, 2, 1
		};
		m_VAO = std::make_unique<vertexArray>();
		m_VBO = std::make_unique<vertexBuffer>(positions, 4 * 6 * sizeof(float));
		vertexBufferLayout layout;
		layout.PushFloat(4);
		layout.PushFloat(2);
		m_VAO->addBuffer(*m_VBO, layout);
		m_IBO = std::make_unique<indexBuffer>(indices, 6);
		m_Shader = std::make_unique<shader>("../source/res/shaders/rectangleTexture.shader");
		m_Shader->Bind();
		//m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		m_Texture = std::make_unique<texture>("../source/res/textures/jim.jpg");
		m_Texture->Bind(0);
		m_Shader->setUniform1i("u_Texture", 0);
}

test::testTexture::~testTexture() {
		GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTexture::onUpdate(timestep deltaTime) {
		test::onUpdate(deltaTime);
}

void test::testTexture::onRender() {
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
}

void test::testTexture::onImGuiRender() {
		ImGui::Text("Polygon mode:");
		if (ImGui::Button("Enable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
		}
		if (ImGui::Button("Disable")) {
				GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
		}
}
