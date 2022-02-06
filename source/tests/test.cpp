#include "test.h"

#include <imgui.h>

namespace test {


	testMenu::testMenu(test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer) {

	}

	void testMenu::onImGuiRender() {
		for (auto& test : m_Test) {
			if (ImGui::Button(test.first.c_str())) {
				m_CurrentTest = test.second();
			}
		}
	}
}
