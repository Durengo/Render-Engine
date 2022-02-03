#pragma once

#include "test.h"

#include <memory>

#include "../Platform/OpenGL/vertexBufferLayout.h"
#include "../Platform/OpenGL/vertexBuffer.h"
#include "../Platform/OpenGL/indexBuffer.h"
#include "../Platform/OpenGL/shader.h"

namespace test {

				class testTriangleColorAnimation : public test {
				public:
								testTriangleColorAnimation();

								~testTriangleColorAnimation();

								void onUpdate(timestep deltaTime) override;

								void onRender() override;

								void onImGuiRender() override;

				private:

								std::unique_ptr<renderer> m_Renderer;

								std::unique_ptr<vertexArray> m_VAO;

								std::unique_ptr<vertexBuffer> m_VBO;

								std::unique_ptr<indexBuffer> m_IBO;

								std::unique_ptr<shader> m_Shader;

								float r, g, b;

								bool br, bg, bb;

								float incrR, incrG, incrB;

								float settime = 0.0f;
								bool istimeset = false;

				};

}