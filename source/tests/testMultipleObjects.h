#pragma once

#include "test.h"

#include "../Engine/Platform/OpenGL/vertexBufferLayout.h"
#include "../Engine/Platform/OpenGL/vertexBuffer.h"
#include "../Engine/Platform/OpenGL/indexBuffer.h"
#include "../Engine/Platform/OpenGL/shader.h"

#include <glm/glm.hpp>

#include <memory>

namespace test
{

	class testMultipleObjects : public test
	{
	public:
		testMultipleObjects();

		~testMultipleObjects();

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

		glm::vec3 m_TranslationA;

		glm::vec3 m_TranslationB;
	};

}