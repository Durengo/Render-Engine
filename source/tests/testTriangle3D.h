#pragma once

#include "test.h"

namespace test {

	class testTriangle3D : public test {
	public:
		testTriangle3D(int width, int height);

		testTriangle3D();

		~testTriangle3D();

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