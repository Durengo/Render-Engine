#pragma once

#include "test.h"

namespace test {

	class testTriangle : public test {
	public:
		testTriangle(int width, int height);

		testTriangle();

		~testTriangle();

		void onUpdate(timestep deltaTime) override;

		void onRender() override;

		void onImGuiRender() override;

	private:
		int width, height;

		unsigned int m_ShaderProgram;

		unsigned int m_VAO;

		unsigned int m_VBO;

	};

}