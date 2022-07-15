#pragma once

#include "test.h"

#include "../Engine/Platform/OpenGL/vertexBufferLayout.h"
#include "../Engine/Platform/OpenGL/vertexBuffer.h"
#include "../Engine/Platform/OpenGL/indexBuffer.h"
#include "../Engine/Platform/OpenGL/shader.h"

#include <memory>

namespace test {

	class testCameraRotation : public test {
	public:
		testCameraRotation();

		~testCameraRotation();

		void onUpdate(timestep deltaTime) override;

		void onRender() override;

		void onImGuiRender() override;

	private:

		std::unique_ptr<renderer> m_Renderer;

		int width, height;

		std::unique_ptr<vertexArray> m_VAO;

		std::unique_ptr<vertexBuffer> m_VBO;

		std::unique_ptr<indexBuffer> m_IBO;

		std::unique_ptr<shader> m_Shader;

		glm::mat4 m_Proj, m_View;

		glm::mat4 model;

		glm::vec3 m_TranslationA;

		glm::vec3 cameraPos;  

		glm::vec3 cameraTarget;

		glm::vec3 cameraDirection;

		glm::vec3 up;

		glm::vec3 cameraRight;

		glm::vec3 cameraUp;

		float m_ClearColor[4];

		float rgba[4];

		float cam[3];

		bool autorotate[3];

		float rotatespeed[3];

		float rpm[3];

		float radians[3];

		float prevrads[3];

		float radius;

		float scale[3];

		float scale2;

		//bool mvpstate;
	};

}