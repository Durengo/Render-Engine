#pragma once

#include <vector>
#include <string>
#include <functional>
#include <iostream>

#include "../Core/timestep.h"
#include "../Platform/OpenGL/renderer.h"

namespace test {

				class test {
				public:
								test() {}

								virtual ~test() {}

								virtual void onUpdate(timestep deltaTime) {}

								//virtual void onUpdate(timestep deltaTime, GLFWwindow &window) {}

								virtual void onRender() {}

								//virtual void onRender(GLFWwindow &window) {}

								virtual void onImGuiRender() {}

				private:

				};

				class testMenu : public test {
				public:
								testMenu(test *&currentTestPointer);

								void onImGuiRender() override;

								template<typename T>
								void registerTest(const std::string &name) {
										std::cout << "Registering test: " << name << std::endl;

										m_Test.push_back(std::make_pair(name, []() { return new T(); }));
								}

								template<typename T>
								void registerTestWithWidthAndHeight(const std::string &name, int width, int height) {
										std::cout << "Registering test: " << name << std::endl;

										m_Test.push_back(std::make_pair(name, [width, height]() { return new T(); }));
								}

								template<typename T>
								void registerTestWithWindow(const std::string &name, GLFWwindow *window) {
										std::cout << "Registering test: " << name << std::endl;

										m_Test.push_back(std::make_pair(name, [window]() { return new T(window); }));
								}


				private:
								test *&m_CurrentTest;

								std::vector<std::pair<std::string, std::function<test *()>>> m_Test;
				};

};