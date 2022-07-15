#include "testTriangleRainbow.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

test::testTriangleRainbow::testTriangleRainbow()
	: m_Renderer(std::make_unique<renderer>()), width(1920), height(1080),
	  m_Proj(glm::ortho(0.0f, (float)width, 0.0f, (float)height, -10.0f, 10.0f)),
	  // m_Proj(glm::perspective(glm::radians(15.0f), 800.0f / 600.0f, 0.1f, 100.0f)),
	  m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(960, 540, 0),
	  cam{0.0f, 0.0f, 0.0f}, autorotate(false), rotatespeed(10), rpm(0.0f),
	  radians(0.0f), prevrads(0.0f), scale{1.0f, 1.0f, 1.0f}, scale2(1.0f)
{

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	float positions[] = {
		-50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 50.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
	unsigned int indices[] = {
		0, 1, 2};

	m_VAO = std::make_unique<vertexArray>();

	m_VBO = std::make_unique<vertexBuffer>(positions, 3 * 8 * sizeof(float));

	vertexBufferLayout layout;
	layout.PushFloat(4);
	layout.PushFloat(4);

	m_VAO->addBuffer(*m_VBO, layout);

	m_IBO = std::make_unique<indexBuffer>(indices, 3);

	m_Shader = std::make_unique<shader>("res/shaders/triangleRainbow.shader");
	m_Shader->Bind();
}

test::testTriangleRainbow::~testTriangleRainbow()
{
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testTriangleRainbow::onUpdate(timestep deltaTime)
{
	if (autorotate)
	{
		prevrads = deltaTime.getSeconds() * ((rpm) * (2 * glm::pi<float>()));
		radians += prevrads;
	}
}

void test::testTriangleRainbow::onRender()
{
	{
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(cam[0], cam[1], cam[2]));
		model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		model = glm::rotate(model, glm::radians(radians), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]) * scale2);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}
}

void test::testTriangleRainbow::onImGuiRender()
{
	ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0 - width, width);
	if (ImGui::Button("Reset Translations"))
	{
		m_TranslationA[0] = 960;
		m_TranslationA[1] = 540;
		m_TranslationA[2] = 0;
	}
	ImGui::SliderFloat3("Camera", cam, 0 - width, width);
	if (ImGui::Button("Reset Camera"))
	{
		cam[0] = 0.0f;
		cam[1] = 0.0f;
		cam[2] = 0.0f;
	}
	ImGui::Checkbox("Toggle Automatic Triangle Rotation", &autorotate);
	ImGui::SliderFloat("Rotation Speed", &rpm, 0.0f, 100.0f);
	ImGui::SliderFloat("Triangle Rotation", &radians, -360.0f, 360.0f);
	ImGui::Text("%f RPM", rpm);
	if (ImGui::Button("Reset RPM Value"))
	{
		rpm = 0.0f;
	}
	if (ImGui::Button("Reset Triangle Rotation"))
	{
		radians = 0.0f;
	}
	ImGui::SliderFloat3("Triangle Vector Scale", scale, 0.0f, 50.0f);
	ImGui::SliderFloat("Trinagle Ratio Scale", &scale2, -0.0f, 10.0f);
	if (ImGui::Button("Reset Vector Scaling"))
	{
		scale[0] = 1.0f;
		scale[1] = 1.0f;
		scale[2] = 1.0f;
	}
	if (ImGui::Button("Reset Ratio Scaling"))
	{
		scale2 = 1.0f;
	}
}
