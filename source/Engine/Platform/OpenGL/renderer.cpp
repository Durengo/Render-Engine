#include "renderer.h"

#include <iostream>

renderer::renderer()
	: windowID(nullptr), oldTimeSinceStart(0), timeSinceStart(0), deltaTime(0), counter(0) {
	//initDeltaTime();
}

renderer::renderer(GLFWwindow* windowID)
	: windowID(windowID), oldTimeSinceStart(0), timeSinceStart(0), deltaTime(0), counter(0) {

}

void renderer::draw(const vertexArray& va, const indexBuffer& ib, const shader& shader) const {
	shader.Bind();
	va.Bind();
	ib.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
	//unbinding here would reduce performance but is useful for debugging
}

void renderer::clear() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void renderer::windowFPSMS(GLFWwindow* windowID) {
	timeSinceStart = (int)glfwGetTime();
	deltaTime = timeSinceStart - oldTimeSinceStart;
	counter++;
	if (deltaTime >= 1.0 / 30.0) {
		std::string FPS = std::to_string((1.0 / deltaTime) * counter);
		std::string ms = std::to_string((deltaTime / counter) * 1000);
		std::string newTitle = FPS + " FPS / " + ms + "ms";
		glfwSetWindowTitle(windowID, newTitle.c_str());
		oldTimeSinceStart = timeSinceStart;
		counter = 0;
	}
}

void renderer::initDeltaTime() {


	//		timeSinceStart = (int) glfwGetTime();
//		deltaTime = timeSinceStart - oldTimeSinceStart;
}

void renderer::updateDeltaTime(float lastframetime) {
	float time = (float)glfwGetTime();
	deltatime = time - lastframetime;
	lastframetime = time;

	//timestep timestep = time - lastframetime;
//		timeSinceStart = (int) glfwGetTime();
//		deltaTime = timeSinceStart - oldTimeSinceStart;
}

void renderer::waitDeltaTime(int x) {

}

void renderer::restartDeltaTime() {
	lastframetime = 0;
}

//int renderer::getDeltaTime() const {
//		return deltaTime;
//}

timestep renderer::getDeltaTime() const {
	return deltatime;
}

float* renderer::getLastframetime() const {
	return lastframetime;
}

void renderer::setLastframetime(float* lastframetime) {
	renderer::lastframetime = lastframetime;
}

void renderer::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//std::cout << "Something pressed?\n";
	if (key == GLFW_KEY_UP) {
		switch (action) {
		case GLFW_PRESS:
			std::cout << "Pressed Up!\n";
		case GLFW_RELEASE:
			std::cout << "Released Up!\n";
		case GLFW_REPEAT:
			std::cout << "Holding Up!\n";
		default:
			std::cout << std::endl;
			break;
		}
	}
}

void renderer::character_callback(GLFWwindow* window, unsigned int codepoint) {
	const char* key_name = glfwGetKeyName(GLFW_KEY_W, 0);
	std::cout << "W PRESSSSSS\n";
}

void renderer::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	std::cout << "x: " << xpos << " y: " << ypos << std::endl;
}

void renderer::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		bool pressonce = false;
		bool releaseonce = false;
		if (pressonce || releaseonce) {
			return;
		}
		if (action == GLFW_PRESS && !pressonce) {
			std::cout << "Left mouse button pressed!\n";
			pressonce = true;
		}
		if (action == GLFW_RELEASE && !releaseonce) {
			std::cout << "Left mouse button released!\n";
			releaseonce = true;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		bool pressonce = false;
		bool releaseonce = false;
		if (pressonce || releaseonce) {
			return;
		}
		if (action == GLFW_PRESS && !pressonce) {
			std::cout << "Right mouse button pressed!\n";
			pressonce = true;
		}
		if (action == GLFW_RELEASE && !releaseonce) {
			std::cout << "Right mouse button released!\n";
			releaseonce = true;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		bool pressonce = false;
		bool releaseonce = false;
		if (pressonce || releaseonce) {
			return;
		}
		if (action == GLFW_PRESS && !pressonce) {
			std::cout << "Middle mouse button pressed!\n";
			pressonce = true;
		}
		if (action == GLFW_RELEASE && !releaseonce) {
			std::cout << "Middle mouse button released!\n";
			releaseonce = true;
		}
	}
}

void renderer::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	std::cout << "Scroll wheel: " << yoffset << std::endl;
}