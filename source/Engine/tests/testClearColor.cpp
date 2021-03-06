#include "testClearColor.h"

#include "imgui.h"

#include "../Core/GLErrorHandler.h"

namespace test {

				testClearColor::testClearColor()
								: m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f} {

				}

				testClearColor::~testClearColor() {

				}

				void testClearColor::onUpdate(timestep deltaTime) {
						test::onUpdate(deltaTime);
				}

				void testClearColor::onRender() {
						GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
						GLCall(glClear(GL_COLOR_BUFFER_BIT));

				}

				void testClearColor::onImGuiRender() {
						ImGui::ColorEdit4("Clear Color", m_ClearColor);
				}
}