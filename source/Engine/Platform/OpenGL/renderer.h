#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Core/GLErrorHandler.h"
#include "../../Core/timestep.h"
#include "vertexArray.h"
#include "indexBuffer.h"
#include "shader.h"

class renderer {
public:
				renderer();

				renderer(GLFWwindow *windowID);

				void draw(const vertexArray &va, const indexBuffer &ib, const shader &shader) const;

				void clear() const;

				void windowFPSMS(GLFWwindow *windowID);

				void initDeltaTime();

				void updateDeltaTime(float lastframetime);

				void waitDeltaTime(int x);

				void restartDeltaTime();

				float *getLastframetime() const;

				void setLastframetime(float *lastframetime);

				//int getDeltaTime() const;
				timestep getDeltaTime() const;

				//FUNCTIONS MESS WITH INPUT
				static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

				static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

				static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

				static void keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods);

				static void character_callback(GLFWwindow *window, unsigned int codepoint);

private:
				GLFWwindow *windowID;

				double oldTimeSinceStart;

				double timeSinceStart;

				double deltaTime;

				unsigned int counter;

				timestep deltatime;

				float *lastframetime;

};