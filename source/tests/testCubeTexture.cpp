#include "testCubeTexture.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

test::testCubeTexture::testCubeTexture()
	: m_Renderer(std::make_unique<renderer>()), width(1920), height(1080),
	//m_Proj(glm::ortho(0.0f, (float) width, 0.0f, (float) height, -1920.0f, 1920.0f)),
	m_Proj(glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 10000.0f)),
	m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_TranslationA(0, 0, 0), m_TranslationB(1000, 0, 0),
	m_ClearColor{ 0.0f, 0.0f, 0.0f, 0.0f }, rgba{ 1.0f, 1.0f, 1.0f, 1.0f }, cam{ 0.0f, 0.0f, 0.0f },
	autorotate{ false, false, false }, rotatespeed{ 10.0f, 10.0f, 10.0f }, rpm{ 0.0f, 0.0f, 0.0f },
	radians{ 0.0f, 0.0f, 0.0f }, scale{ 1.0f, 1.0f, 1.0f }, scale2(1.0f) {

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	GLCall(glEnable(GL_DEPTH_TEST));

	float positions[] = {
					-50.0f, 50.0f, 0.0f, 1.0f, 1.0f, 1.0f,
					-50.0f, -50.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					50.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f,
					50.0f, -50.0f, 0.0f, 1.0f, 1.0f, 1.0f,
					-50.0f, 50.0f, -100.0f, 1.0f, 1.0f, 1.0f,
					-50.0f, -50.0f, -100.0f, 1.0f, 1.0f, 1.0f,
					50.0f, 50.0f, -100.0f, 1.0f, 1.0f, 0.0f,
					50.0f, -50.0f, -100.0f, 1.0f, 1.0f, 0.0f
	};
	unsigned int indices[] = {
					0, 2, 3, 0, 3, 1,
					2, 6, 7, 2, 7, 3,
					6, 4, 5, 6, 5, 7,
					4, 0, 1, 4, 1, 5,
					0, 4, 6, 0, 6, 2,
					1, 5, 7, 1, 7, 3
	};

	m_VAO = std::make_unique<vertexArray>();

	m_VBO = std::make_unique<vertexBuffer>(positions, 8 * 6 * sizeof(float));

	vertexBufferLayout layout;
	layout.PushFloat(4);
	layout.PushFloat(2);

	m_VAO->addBuffer(*m_VBO, layout);

	m_IBO = std::make_unique<indexBuffer>(indices, 36);

	m_Shader = std::make_unique<shader>("res/shaders/cubeTexture.shader");
	m_Shader->Bind();
	//m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	m_Texture = std::make_unique<texture>("res/textures/jim.jpg");
	m_Texture->Bind(0);
	m_Shader->setUniform1i("u_Texture", 0);
}

test::testCubeTexture::~testCubeTexture() {
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testCubeTexture::onUpdate(timestep deltaTime) {
	if (autorotate[0]) {
		radians[0] = deltaTime.getMilliseconds() * 10 / rotatespeed[0];
		rpm[0] = radians[0] / deltaTime.getSeconds();
		if (rpm[0] < 0) {
			rpm[0] = rpm[0] / -1;
		}
	}
	if (autorotate[1]) {
		radians[1] = deltaTime.getMilliseconds() * 10 / rotatespeed[1];
		rpm[1] = radians[1] / deltaTime.getSeconds();
		if (rpm[1] < 0) {
			rpm[1] = rpm[1] / -1;
		}
	}
	if (autorotate[2]) {
		radians[2] = deltaTime.getMilliseconds() * 10 / rotatespeed[2];
		rpm[2] = radians[0] / deltaTime.getSeconds();
		if (rpm[2] < 0) {
			rpm[2] = rpm[2] / -1;
		}
	}
}

void test::testCubeTexture::onRender() {
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	m_View = glm::translate(glm::mat4(1.0f), glm::vec3(cam[0], cam[1], cam[2]));

	m_Texture->Bind();
	{
		model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		model = glm::rotate(model, glm::radians(radians[0]), glm::vec3(0.0, 0.0, 1.0));
		model = glm::rotate(model, glm::radians(radians[1]), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(radians[2]), glm::vec3(0.0, 1.0, 0.0));

		model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]) * scale2);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		//m_Shader->setUniform4f("u_Color", rgba[0], rgba[1], rgba[2], rgba[3]);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}
	{
		glm::mat4 modelx = glm::translate(glm::mat4(1.0f), m_TranslationB);
		glm::mat4 mvp = m_Proj * m_View * modelx;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		//m_Shader->setUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 0.4f);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}

}

void test::testCubeTexture::onImGuiRender() {
	ImGui::ColorEdit4("Clear Color", m_ClearColor);
	//Color
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
	//Object manipulation
	ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, width);
	ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, width);
	//Camera
	ImGui::SliderFloat3("Camera", cam, -1920.0f, 1920.0f);
	if (ImGui::Button("Reset Camera")) {
		cam[0] = 0.0f;
		cam[1] = 0.0f;
		cam[2] = 0.0f;
	}
	//Rotations
	//X Axis
	ImGui::Checkbox("Toggle Automatic X Axis Rotation", &autorotate[0]);
	ImGui::SliderFloat("Rotation Speed X Axis", &rotatespeed[0], -500.0f, 10000.0f);
	if (ImGui::Button("Reset X Axis Rotation Speed")) {
		rotatespeed[0] = 10.0f;
	}
	ImGui::SliderFloat("Triangle Rotation Along X Axis", &radians[0], -360.0f, 360.0f);
	ImGui::Text("X AXIS %.1f RPM", rpm[0]);
	if (ImGui::Button("Reset X Axis")) {
		radians[0] = 0.0f;
	}
	//Y Axis
	ImGui::Checkbox("Toggle Automatic Y Axis Rotation", &autorotate[1]);
	ImGui::SliderFloat("Rotation Speed Y Axis", &rotatespeed[1], -500.0f, 10000.0f);
	if (ImGui::Button("Reset Y Axis Rotation Speed")) {
		rotatespeed[1] = 10.0f;
	}
	ImGui::SliderFloat("Triangle Rotation Along Y Axis", &radians[1], -360.0f, 360.0f);
	ImGui::Text("X AXIS %.1f RPM", rpm[1]);
	if (ImGui::Button("Reset Y Axis")) {
		radians[1] = 0.0f;
	}
	//Z Axis
	ImGui::Checkbox("Toggle Automatic Z Axis Rotation", &autorotate[2]);
	ImGui::SliderFloat("Rotation Speed Z Axis", &rotatespeed[2], -500.0f, 10000.0f);
	if (ImGui::Button("Reset Z Axis Rotation Speed")) {
		rotatespeed[2] = 10.0f;
	}
	ImGui::SliderFloat("Triangle Rotation Along Z Axis", &radians[2], -360.0f, 360.0f);
	ImGui::Text("X AXIS %.1f RPM", rpm[2]);
	if (ImGui::Button("Reset Z Axis")) {
		radians[2] = 0.0f;
	}
	//Scale
	ImGui::SliderFloat3("Triangle Vector Scale", scale, 0.0f, 50.0f);
	ImGui::SliderFloat("Trinagle Ratio Scale", &scale2, -0.0f, 10.0f);
	if (ImGui::Button("Reset Vector Scaling")) {
		scale[0] = 1.0f;
		scale[1] = 1.0f;
		scale[2] = 1.0f;
	}
	if (ImGui::Button("Reset Ratio Scaling")) {
		scale2 = 1.0f;
	}
}
