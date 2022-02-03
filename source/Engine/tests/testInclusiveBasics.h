#pragma once

#include "test.h"

#include <memory>

#include "glm/glm.hpp"

#include "../Platform/OpenGL/vertexBufferLayout.h"
#include "../Platform/OpenGL/vertexBuffer.h"
#include "../Platform/OpenGL/indexBuffer.h"
#include "../Platform/OpenGL/shader.h"
#include "../Platform/OpenGL/texture.h"

namespace test {

				class testInclusiveBasics : public test {
				public:
								testInclusiveBasics();

								~testInclusiveBasics();

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

								std::unique_ptr<texture> m_Texture;

								std::unique_ptr<vertexArray> m_VAO1;

								std::unique_ptr<vertexBuffer> m_VBO1;

								std::unique_ptr<indexBuffer> m_IBO1;

								std::unique_ptr<shader> m_Shader1;

								glm::mat4 m_Proj, m_View;

								float camx, camy;

								float m_ClearColor[4];

								float rgba[4];

								glm::vec3 m_TranslationA;

								glm::vec3 m_TranslationB;

								glm::vec3 m_TranslationC;

				};
}
