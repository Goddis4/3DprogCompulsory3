#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Shaders/shaderClass.h"

class Camera
{
public:
	// Defines and stores the camera's main vectors
	glm::vec3 Location;
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from looking away when first entering window
	bool initialClick = true;

	// Defines and stores the window's width and height
	int width;
	int height;

	// Decide the speed of the camera and it's sensitivity when looking around
	float speed = 0.05f;
	float sensitivity = 80.0f;

	// Constructor for camera to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// The camera matrix gets updated and exported to the Vertex Shader
	glm::mat4 Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);

	// Handles camera Input
	void Input(GLFWwindow* window);
};
#endif
