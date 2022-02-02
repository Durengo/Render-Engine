#pragma once

#include "test.h"

#include <memory>

#include "../Engine/Platform/OpenGL/vertexBufferLayout.h"
#include "../Engine/Platform/OpenGL/vertexBuffer.h"
#include "../Engine/Platform/OpenGL/indexBuffer.h"
#include "../Engine/Platform/OpenGL/shader.h"

namespace test {

				class testRectangleAbstraction : public test {
				public:
								testRectangleAbstraction();

								~testRectangleAbstraction();

								void onUpdate(timestep deltaTime) override;

								void onRender() override;

								void onImGuiRender() override;

				private:
								std::unique_ptr<renderer> m_Renderer;

								std::unique_ptr<vertexArray> m_VAO;

								std::unique_ptr<vertexBuffer> m_VBO;

								std::unique_ptr<indexBuffer> m_IBO;

								std::unique_ptr<shader> m_Shader;

				};

}