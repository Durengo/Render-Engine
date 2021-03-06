#pragma once

#include "test.h"

#include <memory>

#include "glm/glm.hpp"

#include "../Platform/OpenGL/vertexBufferLayout.h"
#include "../Platform/OpenGL/vertexBuffer.h"
#include "../Platform/OpenGL/indexBuffer.h"
#include "../Platform/OpenGL/shader.h"

namespace test {

				class testProjectionMetrices : public test {
				public:
								testProjectionMetrices();

								~testProjectionMetrices();

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

				};

}