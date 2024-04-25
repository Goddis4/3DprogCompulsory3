#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Location = position;
}

glm::mat4 Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
	// Initializes matrices, otherwise they will be a null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes sure the camera looks from the right position in the right direction
	view = glm::lookAt(Location, Location + Position, Up);

	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// The camera matrix gets exported to the Vertex Shader
	return projection * view;
}

void Camera::Input(GLFWwindow* window)
{
	// Handles key input to move camera
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Location += speed * Position;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		Location += speed * -glm::normalize(glm::cross(Position, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Location += speed * -Position;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		Location += speed * glm::normalize(glm::cross(Position, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Location += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Location += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}


	// Handles mouse Input
	// Hides mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	// Prevents camera from looking away on the initial click
	if (initialClick)
	{
		glfwSetCursorPos(window, (width / 2), (height / 2));
		initialClick = false;
	}

	// Stores the coordinates of the cursor
	double cursorX;
	double cursorY;
	// Fetches the coordinates of the cursor
	glfwGetCursorPos(window, &cursorX, &cursorY);

	// Shifts and normalizes the coordinates of the cursor so they begin in the 
	// centre of the screen and then "transforms" them into degrees 
	float rotateX = sensitivity * (float)(cursorY - (height / 2)) / height;
	float rotateY = sensitivity * (float)(cursorX - (width / 2)) / width;
		
	// Calculates upcoming vertical change in the position
	glm::vec3 newPosition = glm::rotate(Position, glm::radians(-rotateX), glm::normalize(glm::cross(Position, Up)));

	// Decides the next vertical position is allowed or not
	if (abs(glm::angle(newPosition, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Position = newPosition;
	}

	// Rotates the position left and right
	Position = glm::rotate(Position, glm::radians(-rotateY), Up);

	// Places the cursor to the centre of the window so it does not roam around
	glfwSetCursorPos(window, (width / 2), (height / 2));
}