// TODO: IMPLEMENT UV MAP FOR INDICES (TEXTURES)
// TODO: 1. PONG CLONE, 2. SNAKE CLONE, 3. TETRIS CLONE, 4. SPACE INVADERS CLONE, 5. PACMAN CLONE, 6. DONKEY KONG CLONE
// TODO: FIX CAMERA YAW LIMITATION
// TODO: CREATE AN EVENT SYSTEM
// TODO: CREATE AN ENTRY POINT
// TODO: MINIMIZE COMPILE TIME

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Platform/OpenGL/renderer.h"
#include "../../tests/_testInclude.h"
#include "timestep.h"

// LEAVE FOR LATER:
//#include "tests/testInclusiveBasics.h"
//#include "tests/testTriangle3D.h"

int main()
{
	GLFWwindow *window;
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1920;
	int height = 1080;
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (glewInit() != GLEW_OK)
		std::cout << "Error! GLEW initialization failure." << std::endl;

	// driver checkup
	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		int numAttrib = 0;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttrib);
		std::cout << "Maximum number of vertex attributes supported by the GPU: " << numAttrib << std::endl;
	}
	if (glfwRawMouseMotionSupported())
	{
		std::cout << "\nRaw Mouse Motion IS supported.\n";
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		std::cout << "Automatically enabling raw mouse. \n\n";
	}
	{

		renderer renderer;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init();
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		/* Loop until the user closes the window */

		test::test *currentTest = nullptr;
		test::testMenu *testMenu = new test::testMenu(currentTest);
		currentTest = testMenu;

		testMenu->registerTest<test::testClearColor>("Clear Color Test");
		testMenu->registerTest<test::testTriangle>("Triangle Test");
		testMenu->registerTest<test::testRectangle>("Rectangle Test");
		testMenu->registerTest<test::testTriangleAbstraction>("Triangle Abstraction Test");
		testMenu->registerTest<test::testRectangleAbstraction>("Rectangle Abstraction Test");
		testMenu->registerTest<test::testTriangleColor>("Triangle Color Test");
		testMenu->registerTest<test::testTriangleColorAnimation>("Triangle Color Animation Test");
		testMenu->registerTest<test::testTexture>("Rectangle Texture Test");
		testMenu->registerTest<test::testProjectionMatrices>("Projection Matrix Test");
		testMenu->registerTest<test::testMultipleObjects>("Multiple Object Test");
		testMenu->registerTest<test::testMultipleRectangleTextures>("Multiple Rectangles With Textures Test");
		testMenu->registerTest<test::testCameraManipulation>("Camera Manipulation");
		testMenu->registerTest<test::testTriangleRainbow>("Rainbow Triangle Test");
		testMenu->registerTest<test::testTriangleTransformation>("Triangle Transformation Test");
		testMenu->registerTest<test::testCube>("Cube Test");
		testMenu->registerTest<test::testTextureCord>("Textured Cube Test");
		testMenu->registerTest<test::testCameraRotation>("Camera Rotation Test");
		testMenu->registerTest<test::testAdvancedCameraManipulation>("Advanced Camera Manipulation Test");

		// TEMPORARILY DISABLED:
		// testMenu->registerTest<test::testCubeTexture>("Textured Multiple Cubes Test");
		// testMenu->registerTest<test::testCamera>("Camera Test");

		// NOT MADE:
		// testMenu->registerTestWithWindow<test::testCamera>("Camera Test", window);
		// testMenu->registerTest<test::testInclusiveBasics>("Basic OpenGL Inclusive Test");
		// testMenu->registerTest<test::testTriangle3D>("Triangle 3D");

		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.clear();
			renderer.windowFPSMS(window);
			renderer.updateDeltaTime();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest)
			{
				currentTest->onUpdate(renderer.getDeltaTime());
				currentTest->onRender();
				currentTest->onEvent(window, renderer.getDeltaTime());
				ImGui::Begin("Tests:");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->onImGuiRender();
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
							ImGui::GetIO().Framerate);
				ImGui::End();
			}

			// ImGuiDemo(show_demo_window, show_another_window, clear_color);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
		delete currentTest;
		if (currentTest != testMenu)
		{
			delete testMenu;
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	// ImGui_ImplGlfw_Shutdown();

	glfwTerminate();
	return 0;
}