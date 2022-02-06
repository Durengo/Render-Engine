#pragma once

#include "test.h"

namespace test {

	class testTextureNoAbstraction : public test {
	public:
		testTextureNoAbstraction(int width, int height);

		testTextureNoAbstraction();

		~testTextureNoAbstraction();

		void onUpdate(timestep deltaTime) override;

		void onRender() override;

		void onImGuiRender() override;

	private:
		int width, height;

		unsigned int m_ShaderProgram;

		unsigned int m_VAO;

		unsigned int m_EBO;

		unsigned int m_VBO;

	};

}