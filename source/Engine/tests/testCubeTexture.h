#pragma once

#include "test.h"

#include <memory>

#include "../Platform/OpenGL/vertexBufferLayout.h"
#include "../Platform/OpenGL/vertexBuffer.h"
#include "../Platform/OpenGL/indexBuffer.h"
#include "../Platform/OpenGL/shader.h"
#include "../Platform/OpenGL/texture.h"

namespace test {

				class testCubeTexture : public test {
				public:
								testCubeTexture();

								~testCubeTexture();

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

								glm::mat4 m_Proj, m_View;

								glm::mat4 model;

								glm::vec3 m_TranslationA;

								glm::vec3 m_TranslationB;

								float m_ClearColor[4];

								float rgba[4];

								float cam[3];

								bool autorotate[3];

								float rotatespeed[3];

								float rpm[3];

								float radians[3];

								float scale[3];

								float scale2;
				};

}