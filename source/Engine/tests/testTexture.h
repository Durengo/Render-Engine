#pragma once

#include "test.h"

#include <memory>

#include "../Platform/OpenGL/vertexBufferLayout.h"
#include "../Platform/OpenGL/vertexBuffer.h"
#include "../Platform/OpenGL/indexBuffer.h"
#include "../Platform/OpenGL/shader.h"
#include "../Platform/OpenGL/texture.h"

namespace test {

				class testTexture : public test {
				public:
								testTexture();

								~testTexture();

								void onUpdate(timestep deltaTime) override;

								void onRender() override;

								void onImGuiRender() override;

				private:
								std::unique_ptr<renderer> m_Renderer;

								std::unique_ptr<vertexArray> m_VAO;

								std::unique_ptr<vertexBuffer> m_VBO;

								std::unique_ptr<indexBuffer> m_IBO;

								std::unique_ptr<shader> m_Shader;

								std::unique_ptr<texture> m_Texture;

				};
}