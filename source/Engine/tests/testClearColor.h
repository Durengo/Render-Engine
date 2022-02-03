#pragma once

#include "test.h"

namespace test {

				class testClearColor : public test {
				public:
								testClearColor();

								~testClearColor();

								void onUpdate(timestep deltaTime) override;

								void onRender() override;

								void onImGuiRender() override;

				private:
								float m_ClearColor[4];
				};

}