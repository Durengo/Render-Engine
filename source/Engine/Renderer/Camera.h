#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// TODO: LIMIT YAW FOR PRECISION.
// EG:
// Yaw = std::fmod((Yaw + xoffset), (GLfloat)360.0f);
// Yaw = glm::mod( Yaw + xoffset, 360.0f );

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

// static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
// {
// 	std::cout << "MOUSE MOVED\n X POS: " << xpos << " , Y POS: " << ypos << "\n";
//     XPOS = xpos;
//     YPOS = ypos;
// }

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float fov;
    double XPOS;
    double YPOS;
    double XOFFSET;
    double YOFFSET;
    float lastX;
    float lastY;
    GLboolean constrainPitch = true;

    // static double XPOS, YPOS;
    //  constructor with vectors

    // Camera(GLFWwindow *WIN)
    // {
    //     window = WIN;
    //     Front = glm::vec3(0.0f, 0.0f, -1.0f);
    //     MovementSpeed = 2.5f;
    //     MouseSensitivity = 0.1f;
    //     fov = 45.0f;
    //     Position = glm::vec3(0.0f, 0.0f, 0.0f);
    //     Up = glm::vec3(0.0f, 1.0f, 0.0f);
    //     Yaw = -90.0f;
    //     Pitch = 0.0f;
    //     WorldUp = Up;
    //     updateCameraVectors();
    //     XPOS = 0;
    //     YPOS = 0;
    // }

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), fov(FOV)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        XPOS = 0;
        YPOS = 0;
        double XOFFSET = 0;
        double YOFFSET = 0;
        lastX = 960.0f;
        lastY = 540.0f;
        updateCameraVectors();
    }
    // constructor with scalar values
    // Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), fov(FOV)
    // {
    //     Position = glm::vec3(posX, posY, posZ);
    //     WorldUp = glm::vec3(upX, upY, upZ);
    //     Yaw = yaw;
    //     Pitch = pitch;
    //     XPOS = 0;
    //     YPOS = 0;
    //     lastX = 960.0f;
    //     lastY = 540.0f;
    //     updateCameraVectors();
    // }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // CAMERA TYPES:
    static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
    {
        // std::cout << "MOUSE MOVED\n X POS: " << XPOS << " , Y POS: " << YPOS << "\n";
        // ProcessMouseMovement(xpos, ypos);
        //  XPOS = xpos;
        //  YPOS = ypos;
    }
    // FPS LIKE:
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
    void mouse_callback()
    {

        std::cout << "MOUSE MOVED\n X POS: " << XPOS << " , Y POS: " << YPOS << "\n";

        if (constrainPitch)
        {
            lastX = XPOS;
            lastY = YPOS;
            constrainPitch = false;
        }

        // float xpos = static_cast<float>(XPOS);
        // float ypos = static_cast<float>(YPOS);

        float xoffset = XPOS - lastX;
        float yoffset = lastY - YPOS; // reversed since y-coordinates go from bottom to top
        lastX = XPOS;
        lastY = YPOS;

        std::cout << "LAST X\n X POS: " << lastX << " , Y POS: " << lastY << "\n";

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        updateCameraVectors();
    }
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    // void ProcessMouseMovement(GLboolean constrainPitch = true)
    {
        // float xoffset = (float)XPOS;
        // float yoffset = (float)YPOS;

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
    {
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f;
    }

    // CLICK AND LOOK TYPE:
    // Handles mouse inputs
    // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    // {
    // 	// Hides mouse cursor
    // 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // 	// Prevents camera from jumping on the first click
    // 	if (firstClick)
    // 	{
    // 		glfwSetCursorPos(window, (width / 2), (height / 2));
    // 		firstClick = false;
    // 	}

    // 	// Stores the coordinates of the cursor
    // 	double mouseX;
    // 	double mouseY;
    // 	// Fetches the coordinates of the cursor
    // 	glfwGetCursorPos(window, &mouseX, &mouseY);

    // 	// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
    // 	// and then "transforms" them into degrees
    // 	float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
    // 	float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

    // 	// Calculates upcoming vertical change in the Orientation
    // 	glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

    // 	// Decides whether or not the next vertical Orientation is legal or not
    // 	if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
    // 	{
    // 		Orientation = newOrientation;
    // 	}

    // 	// Rotates the Orientation left and right
    // 	Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

    // 	// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
    // 	glfwSetCursorPos(window, (width / 2), (height / 2));
    // }
    // else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    // {
    // 	// Unhides cursor since camera is not looking around anymore
    // 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // 	// Makes sure the next time the camera looks around it doesn't jump
    // 	firstClick = true;
    // }

    // ANOTHER CAM EXAMPLE:

    //     class camera {
    // 	glm::vec3 m_pos;
    // 	glm::quat m_orient;
    // public:
    // 	camera(void) = default;
    // 	camera(const camera &) = default;

    // 	camera(const glm::vec3 &pos) : m_pos(pos) {}
    // 	camera(const glm::vec3 &pos, const glm::quat &orient) : m_pos(pos), m_orient(orient) {}

    // 	camera &operator =(const camera &) = default;

    // 	const glm::vec3 &position(void) const { return m_pos; }
    // 	const glm::quat &orientation(void) const { return m_orient; }

    // 	glm::mat4 view(void) const { return glm::translate(glm::mat4_cast(m_orient), m_pos); }

    // 	void translate(const glm::vec3 &v) { m_pos += v * m_orient; }
    // 	void translate(float x, float y, float z) { m_pos += glm::vec3(x, y, z) * m_orient; }

    // 	void rotate(float angle, const glm::vec3 &axis) { m_orient *= glm::angleAxis(angle, axis * m_orient); }
    // 	void rotate(float angle, float x, float y, float z) { m_orient *= glm::angleAxis(angle, glm::vec3(x, y, z) * m_orient); }

    // 	void yaw(float angle) { rotate(angle, 0.0f, 1.0f, 0.0f); }
    // 	void pitch(float angle) { rotate(angle, 1.0f, 0.0f, 0.0f); }
    // 	void roll(float angle) { rotate(angle, 0.0f, 0.0f, 1.0f); }

private:
    GLFWwindow *window;
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};