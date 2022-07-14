#include "testAdvancedCameraManipulation.h"

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

// void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

test::testAdvancedCameraManipulation::testAdvancedCameraManipulation()
	: m_Renderer(std::make_unique<renderer>()), width(1920), height(1080),
	  // m_Proj(glm::ortho(0.0f, (float) width, 0.0f, (float) height, -10000.0f, 10000.0f)),
	  // m_Proj(glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 1920.0f)),
	  m_View(glm::mat4(1.0f)),
	  // m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
	  m_TranslationA(0, 0, -50),
	  maincam(),
	  firstMouse(true), yaw(-90.0f), pitch(0.0f), lastX((float)width / 2.0), lastY((float)height / 2.0), fov(45.0f),
	  cameraPos(glm::vec3(0.0f, 0.0f, 0.0f)), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	  m_Proj(glm::perspective(glm::radians(maincam.fov), (float)width / (float)height, 0.1f, (float)(height * width))),
	  m_ClearColor{0.0f, 0.0f, 0.0f, 0.0f}, cursor(true),
	  rgba{1.0f, 1.0f, 1.0f, 1.0f}, cam{0.0f, 0.0f, 0.0f}, autorotate{false, false, false}, rotatespeed{10.0f, 10.0f, 10.0f},
	  rpm{0.0f, 0.0f, 0.0f}, radians{0.0f, 0.0f, 0.0f}, prevrads{0.0f, 0.0f, 0.0f}, radius(0.0f), scale{1.0f, 1.0f, 1.0f}, scale2(0.032f)
{

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	float positions[] = {
		-50.0f, 50.0f, 0.0f, 1.0f,
		-50.0f, -50.0f, 0.0f, 1.0f,
		50.0f, 50.0f, 0.0f, 1.0f,
		50.0f, -50.0f, 0.0f, 1.0f,
		-50.0f, 50.0f, -100.0f, 1.0f,
		-50.0f, -50.0f, -100.0f, 1.0f,
		50.0f, 50.0f, -100.0f, 1.0f,
		50.0f, -50.0f, -100.0f, 1.0f};
	unsigned int indices[] = {
		0, 2, 3, 0, 3, 1,
		2, 6, 7, 2, 7, 3,
		6, 4, 5, 6, 5, 7,
		4, 0, 1, 4, 1, 5,
		0, 4, 6, 0, 6, 2,
		1, 5, 7, 1, 7, 3};

	m_VAO = std::make_unique<vertexArray>();

	m_VBO = std::make_unique<vertexBuffer>(positions, 8 * 4 * sizeof(float));

	vertexBufferLayout layout;
	layout.PushFloat(4);

	m_VAO->addBuffer(*m_VBO, layout);

	m_IBO = std::make_unique<indexBuffer>(indices, 36);

	m_Shader = std::make_unique<shader>("res/shaders/advancedCamera.shader");
	m_Shader->Bind();
	m_Shader->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	// cameraUp = glm::cross(cameraDirection, cameraRight);
	//  cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//  cameraDirection = glm::normalize(cameraPos - cameraTarget);
	//  up = glm::vec3(0.0f, 1.0f, 0.0f);
	//  cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	//  radius = 10.0f;
}

test::testAdvancedCameraManipulation::~testAdvancedCameraManipulation()
{
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
}

void test::testAdvancedCameraManipulation::onUpdate(timestep deltaTime)
{
	if (autorotate[0])
	{
		prevrads[0] = deltaTime.getSeconds() * ((rpm[0]) * (2 * glm::pi<float>()));
		radians[0] += prevrads[0];
	}
	if (autorotate[1])
	{
		prevrads[1] = deltaTime.getSeconds() * ((rpm[1]) * (2 * glm::pi<float>()));
		radians[1] += prevrads[1];
	}
	if (autorotate[2])
	{
		prevrads[2] = deltaTime.getSeconds() * ((rpm[2]) * (2 * glm::pi<float>()));
		radians[2] += prevrads[2];
	}
}

void test::testAdvancedCameraManipulation::onRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	{
		// cam[0] = static_cast<float>(sin(glfwGetTime()) * radius);
		// cam[2] = static_cast<float>(cos(glfwGetTime()) * radius);
		// m_View = glm::lookAt(glm::vec3(cam[0], 0.0f, cam[2]), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		// m_View = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		m_View = maincam.GetViewMatrix();
		model = glm::translate(glm::mat4(1.0f), m_TranslationA);
		model = glm::rotate(model, glm::radians(radians[0]), glm::vec3(0.0, 0.0, 1.0));
		model = glm::rotate(model, glm::radians(radians[1]), glm::vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, glm::radians(radians[2]), glm::vec3(0.0, 1.0, 0.0));

		model = glm::scale(model, glm::vec3(scale[0], scale[1], scale[2]) * scale2);
		glm::mat4 mvp = m_Proj * m_View * model;
		m_Shader->Bind();
		m_Shader->setUniformMat4f("u_MVP", mvp);
		m_Shader->setUniform4f("u_Color", rgba[0], rgba[1], rgba[2], rgba[3]);
		m_Renderer->draw(*m_VAO, *m_IBO, *m_Shader);
	}
}

void test::testAdvancedCameraManipulation::onImGuiRender()
{
	ImGui::ColorEdit4("Clear Color", m_ClearColor);
	// Color
	ImGui::ColorEdit4("Cube Color", rgba);
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
	// Object manipulation
	ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f - width, width);
	if (ImGui::Button("Reset Translations"))
	{
		m_TranslationA[0] = 0;
		m_TranslationA[1] = 0;
		m_TranslationA[2] = 0;
	}
	// Camera
	ImGui::SliderFloat3("Camera", cam, -width, width);
	if (ImGui::Button("Reset Camera"))
	{
		cam[0] = 0.0f;
		cam[1] = 0.0f;
		cam[2] = 0.0f;
	}
	// Rotations
	// X Axis
	ImGui::Checkbox("Toggle Automatic X Axis Rotation", &autorotate[0]);
	ImGui::SliderFloat("Rotation Speed X Axis", &rpm[0], 0.0f, 100.0f);
	ImGui::SliderFloat("Triangle Rotation Along X Axis", &radians[0], -360.0f, 360.0f);
	ImGui::Text("X AXIS %.1f RPM", rpm[0]);
	if (ImGui::Button("Reset X-AXIS RPM Value"))
	{
		rpm[0] = 0.0f;
	}
	if (ImGui::Button("Reset X-AXIS Triangle Rotation"))
	{
		radians[0] = 0.0f;
	}
	// Y Axis
	ImGui::Checkbox("Toggle Automatic Y Axis Rotation", &autorotate[1]);
	ImGui::SliderFloat("Rotation Speed Y Axis", &rpm[1], 0.0f, 100.0f);
	ImGui::SliderFloat("Triangle Rotation Along Y Axis", &radians[1], -360.0f, 360.0f);
	ImGui::Text("Y AXIS %.1f RPM", rpm[1]);
	if (ImGui::Button("Reset Y-AXIS RPM Value"))
	{
		rpm[1] = 0.0f;
	}
	if (ImGui::Button("Reset Y-AXIS Triangle Rotation"))
	{
		radians[1] = 0.0f;
	}
	// Z Axis
	ImGui::Checkbox("Toggle Automatic Z Axis Rotation", &autorotate[2]);
	ImGui::SliderFloat("Rotation Speed Z Axis", &rpm[2], 0.0f, 100.0f);
	ImGui::SliderFloat("Triangle Rotation Along Z Axis", &radians[2], -360.0f, 360.0f);
	ImGui::Text("Z AXIS %.1f RPM", rpm[2]);
	if (ImGui::Button("Reset Z-AXIS RPM Value"))
	{
		rpm[2] = 0.0f;
	}
	if (ImGui::Button("Reset Z-AXIS Triangle Rotation"))
	{
		radians[2] = 0.0f;
	}
	// Scale
	ImGui::SliderFloat3("Cube Vector Scale", scale, 0.0f, 50.0f);
	ImGui::SliderFloat("Cube Ratio Scale", &scale2, -0.0f, 10.0f);
	if (ImGui::Button("Reset Vector Scaling"))
	{
		scale[0] = 1.0f;
		scale[1] = 1.0f;
		scale[2] = 1.0f;
	}
	if (ImGui::Button("Reset Ratio Scaling"))
	{
		scale2 = 0.032f;
	}
}

void test::testAdvancedCameraManipulation::onEvent(GLFWwindow *window, timestep deltaTime)
{
	// glfwSetCursorPosCallback(window, cursor_position_callback);
	// glfwSetCursorPosCallback(window, maincam.cursor_position_callback);

	// double xpos, ypos;
	// glfwGetCursorPos(window, &xpos, &ypos);
	// std::cout << "MOUSE MOVED\n X POS: " << xpos << " , Y POS: " << ypos << "\n";

	maincam.MovementSpeed = 20.0f;
	// maincam.ProcessMouseMovement((float)maincam.XPOS, (float)maincam.YPOS);
	if (!cursor)
	{
		glfwGetCursorPos(window, &maincam.XPOS, &maincam.YPOS);
		// glfwSetScrollCallback(window, maincam.scroll_callback);
		maincam.mouse_callback();
		// maincam.ProcessMouseScroll();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			maincam.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime.getSeconds());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			maincam.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime.getSeconds());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			maincam.ProcessKeyboard(Camera_Movement::LEFT, deltaTime.getSeconds());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			maincam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime.getSeconds());
		// if (glfwGetKey(window, GLFW_MOUSE_) == GLFW_PRESS)
		// 	maincam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime.getSeconds());
		// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		// 	maincam.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime.getSeconds());
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		if (cursor)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			cursor = false;
			// ImGui::
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cursor = true;
			maincam.constrainPitch = true;
			// ImGui
		}
	}

	// const float cameraSpeed = 20.0f * deltaTime.getSeconds(); // adjust accordingly
	// if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//     glfwSetWindowShouldClose(window, true);
	// if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//     cameraPos += cameraSpeed * cameraFront;
	// if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//     cameraPos -= cameraSpeed * cameraFront;
	// if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//     cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	// if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//     cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// void test::testAdvancedCameraManipulation::mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
// 		float xpos = static_cast<float>(xposIn);
// 		float ypos = static_cast<float>(yposIn);

// 		if (firstMouse) // initially set to true
// 		{
//     		lastX = xpos;
//     		lastY = ypos;
//     		firstMouse = false;
// 		}

// 		float xoffset = xpos - lastX;
// 		float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
// 		lastX = xpos;
// 		lastY = ypos;

// 		const float sensitivity = 0.1f;
// 		xoffset *= sensitivity;
// 		yoffset *= sensitivity;

// 		yaw   += xoffset;
// 		pitch += yoffset;

// 		if(pitch > 89.0f)
//   		pitch =  89.0f;
// 		if(pitch < -89.0f)
//   		pitch = -89.0f;

// 		//Front direction
// 		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
// 		direction.y = sin(glm::radians(pitch));
// 		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
// 		cameraFront = glm::normalize(direction);
// 	}

// void test::testAdvancedCameraManipulation::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//     fov -= (float)yoffset;
//     if (fov < 1.0f)
//         fov = 1.0f;
//     if (fov > 45.0f)
//         fov = 45.0f;
// }