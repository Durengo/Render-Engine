#include <iostream>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Platform/OpenGL/renderer.h"
#include "../../tests/_testInclude.h"

//LEAVE FOR LATTER:
//#include "tests/testInclusiveBasics.h"
//#include "tests/testTriangle3D.h"

#include "timestep.h"

void ImGuiDemo(bool &show_demo_window, bool &show_another_window, ImVec4 &clear_color);

int main() {
		GLFWwindow *window;
		if (!glfwInit())
				return -1;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		int width = 1920;
		int height = 1080;
		window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
		if (!window) {
				glfwTerminate();
				return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		if (glewInit() != GLEW_OK)
				std::cout << "Error! GLEW initialization failure." << std::endl;



		//driver checkup
		std::cout << glGetString(GL_VERSION) << std::endl;
		{
				int numAttrib = 0;
				glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttrib);
				std::cout << "Maximum number of vertex attributes supported by the GPU: " << numAttrib << std::endl;
		}
		if (glfwRawMouseMotionSupported()) {
				std::cout << "\nRaw Mouse Motion IS supported.\n";
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
				std::cout << "Automatically enabling raw mouse. \n\n";
		}
		//std::cout << sizeof(float);
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
				testMenu->registerTest<test::testTriangleColor>("Triangle Color Test");
				testMenu->registerTest<test::testTriangleColorAnimation>("Triangle Color Animation Test");
				testMenu->registerTest<test::testRectangleAbstraction>("Rectangle Abstraction Test");
				testMenu->registerTest<test::testTexture>("Rectangle Texture Test");
				testMenu->registerTest<test::testProjectionMetrices>("Projection Matrix Test");
				testMenu->registerTest<test::testMultipleObjects>("Multiple Object Test");
				testMenu->registerTest<test::testMultipleRectangleTextures>("Multiple Rectangles With Textures Test");
				testMenu->registerTest<test::testCameraManipulation>("Camera Manipulation");
				testMenu->registerTest<test::testTriangleTransformation>("Triangle Transformation Test");
				testMenu->registerTest<test::testCube>("Cube Test");
				testMenu->registerTest<test::testCubeTexture>("Textured Multiple Cubes Test");
				testMenu->registerTest<test::testCamera>("Camera Test");
				//testMenu->registerTestWithWindow<test::testCamera>("Camera Test", window);

//				testMenu->registerTest<test::testInclusiveBasics>("Basic OpenGL Inclusive Test");
//				testMenu->registerTest<test::testTriangle3D>("Triangle 3D");

				float lastframetime = 0.0f;
				renderer.setLastframetime(&lastframetime);

				while (!glfwWindowShouldClose(window)) {
						GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
						renderer.clear();
						renderer.windowFPSMS(window);
						renderer.updateDeltaTime(lastframetime);

//						//keyboard input handle
//						glfwSetKeyCallback(window, renderer::keyCallBack);
//						//set unicode (?)
//						//glfwSetCharCallback(window, character_callback);
//						//mouse handle
//						//position
//						glfwSetCursorPosCallback(window, renderer.cursor_position_callback);
//						//buttons
//						glfwSetMouseButtonCallback(window, renderer::mouse_button_callback);
//						//scroll
//						glfwSetScrollCallback(window, renderer::scroll_callback);

						ImGui_ImplOpenGL3_NewFrame();
						ImGui_ImplGlfw_NewFrame();
						ImGui::NewFrame();

						if (currentTest) {
								currentTest->onUpdate(renderer.getDeltaTime());
								currentTest->onRender();
								ImGui::Begin("Tests:");
								if (currentTest != testMenu && ImGui::Button("<-")) {
										delete currentTest;
										currentTest = testMenu;
								}
								currentTest->onImGuiRender();
								ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
																				ImGui::GetIO().Framerate);
								ImGui::End();
						}

						//ImGuiDemo(show_demo_window, show_another_window, clear_color);

						ImGui::Render();
						ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

						glfwSwapBuffers(window);

						glfwPollEvents();
				}
				delete currentTest;
				if (currentTest != testMenu) { delete testMenu; }
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
		//ImGui_ImplGlfw_Shutdown();

		glfwTerminate();
		return 0;
}

void ImGuiDemo(bool &show_demo_window, bool &show_another_window, ImVec4 &clear_color) {
		if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);
		{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin(
								"Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float *) &clear_color); // Edit 3 floats representing a color

				if (ImGui::Button(
								"Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
						counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
																ImGui::GetIO().Framerate);
				ImGui::End();
		}
		if (show_another_window) {
				ImGui::Begin("Another Window",
																	&show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				ImGui::Text("Hello from another window!");
				if (ImGui::Button("Close Me"))
						show_another_window = false;
				ImGui::End();
		}
}