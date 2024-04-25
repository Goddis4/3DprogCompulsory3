#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib> 
#include <ctime> 
#include <stb/stb_image.h>
#include <filesystem>

#include "Shaders/shaderClass.h"
#include "Shaders/VAO.h"
#include "Shaders/VBO.h"
#include "Shaders/EBO.h"
#include "Camera.h"
#include "Player.h"
#include "LeastSquareMethod.h"


const unsigned int width = 1000;
const unsigned int height = 700;
using namespace std;

void handleInput(GLFWwindow* window);


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW the version of OpenGL are being used 
	// In this case I am using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW the CORE profile is being used
	// This means I only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLProject", NULL, NULL);
	// Error check if in case the window fails to be created
	if (window == NULL)
	{
		std::cout << "Error trying to create the GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0 and y = 0, to x = 1000 and y = 700
	glViewport(0, 0, width, height);

	// Define and activate the shader program
	Shader shaderProgram("default.vert", "default.frag");
	shaderProgram.Activate();

	std::srand(static_cast<unsigned>(std::time(nullptr)));

	// Define the elements that will be drawn
	Player thePlayer(1.0f, glm::vec3(0, 0, 20), 0.4f, 0.0f, 0.6f, 1);

	Player Ground(20.0f, glm::vec3(5, -27, -10), 0.6f, 0.7f, 0.8f, 2);

	Player NPC(1.0f, glm::vec3(0, 0, -5), 0.7f, 0.2f, 0.0f, 1);

	Player Cube(1.0f, glm::vec3(0, -2, -5), 0.5f, 0.3f, 0.2f, 1);

	Player Cube2(1.0f, glm::vec3(15, 2, -7), 0.5f, 0.4f, 0.2f, 1);


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");
	float scaleValue = 100.0f;


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Define the camera object
	Camera camera(width, height, glm::vec3(0.0f, 5.0f, 45.0f));

	// The speed of cube
	float translationSpeed = 0.05f;

	// Texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set the texture wrapping or filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Textures/brick.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error trying to load texture" << std::endl;
	}
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(true);
	shaderProgram.setInt("tex0", 0);

	// Decide path for npc
	std::vector<double> pathPoints = { -1 , 1, 1, -2, 3, 1 }; // points for pathing
	LeastSquareMethod Path(pathPoints, 3); // the degree of the function, f.exa x^2

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Main while-loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();

		// Input
		handleInput(window);
		thePlayer.Input(window);
		camera.Input(window);

		// NPC path
		NPC.Path(Path.getCoefficients());

		// Set render distance and FOV
		glm::mat4 viewproj = camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, thePlayer.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * model));
		thePlayer.BindVAO();
		thePlayer.GetVBO().Bind();
		glDrawArrays(GL_TRIANGLES, 0, thePlayer.mVertecies.size());
		thePlayer.UnbindVAO();

		// Collision for the player on plane
		Ground.barycentricCoordinatesCalculation(thePlayer.position, Ground.planePoints[0], Ground.planePoints[1], Ground.planePoints[2], true);
		Ground.barycentricCoordinatesCalculation(thePlayer.position, Ground.planePoints[2], Ground.planePoints[3], Ground.planePoints[0], true);
		// Collision for the NPC on plane
		Ground.barycentricCoordinatesCalculation(NPC.position, Ground.planePoints[0], Ground.planePoints[1], Ground.planePoints[2], true);
		Ground.barycentricCoordinatesCalculation(NPC.position, Ground.planePoints[2], Ground.planePoints[3], Ground.planePoints[0], true);

		// Collision for the player on the NPC
		NPC.barycentricCoordinatesCalculation(thePlayer.position, NPC.planePoints[0], NPC.planePoints[1], NPC.planePoints[2], false);
		NPC.barycentricCoordinatesCalculation(thePlayer.position, NPC.planePoints[2], NPC.planePoints[3], NPC.planePoints[0], false);

		// Collision for the player on cube
		Cube.barycentricCoordinatesCalculation(thePlayer.position, Cube.planePoints[0], Cube.planePoints[1], Cube.planePoints[2], false);
		Cube.barycentricCoordinatesCalculation(thePlayer.position, Cube.planePoints[2], Cube.planePoints[3], Cube.planePoints[0], false);

		// Collision for the NPC on cube
		Cube.barycentricCoordinatesCalculation(NPC.position, Cube.planePoints[0], Cube.planePoints[1], Cube.planePoints[2], false);
		Cube.barycentricCoordinatesCalculation(NPC.position, Cube.planePoints[2], Cube.planePoints[3], Cube.planePoints[0], false);

		// Collision for the player on second cube
		Cube2.barycentricCoordinatesCalculation(thePlayer.position, Cube2.planePoints[0], Cube2.planePoints[1], Cube2.planePoints[2], false);
		Cube2.barycentricCoordinatesCalculation(thePlayer.position, Cube2.planePoints[2], Cube2.planePoints[3], Cube2.planePoints[0], false);

		// Collision for second cube on plane
		Ground.barycentricCoordinatesCalculation(Cube2.position, Ground.planePoints[0], Ground.planePoints[1], Ground.planePoints[2], true);
		Ground.barycentricCoordinatesCalculation(Cube2.position, Ground.planePoints[2], Ground.planePoints[3], Ground.planePoints[0], true);

		// Create ground model
		glm::mat4 GroundModel = glm::mat4(1.0f);
		GroundModel = glm::translate(GroundModel, Ground.position);
		GroundModel = glm::scale(GroundModel, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * GroundModel));

		Ground.BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, Ground.mVertecies.size());
		Ground.UnbindVAO();

		// Create NPC model
		glm::mat4 NPCmodel = glm::mat4(1.0f);
		NPCmodel = glm::translate(NPCmodel, NPC.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * NPCmodel));

		NPC.BindVAO();
		NPC.GetVBO().Bind();
		glDrawArrays(GL_TRIANGLES, 0, NPC.mVertecies.size());
		NPC.UnbindVAO();
		camera.Location.x = thePlayer.position.x;

		// Create model for cube
		glm::mat4 CubeModel = glm::mat4(1.0f);
		CubeModel = glm::translate(CubeModel, Cube.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * CubeModel));
		Cube.BindVAO();
		Cube.GetVBO().Bind();
		glDrawArrays(GL_TRIANGLES, 0, Cube.mVertecies.size());
		Cube.UnbindVAO();

		// Create model for second cube
		glm::mat4 CubeModel2 = glm::mat4(1.0f);
		CubeModel2 = glm::translate(CubeModel2, Cube2.position);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewproj * CubeModel2));
		Cube2.BindVAO();
		Cube2.GetVBO().Bind();
		glDrawArrays(GL_TRIANGLES, 0, Cube2.mVertecies.size());
		Cube2.UnbindVAO();


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}





	// Delete every object I have created
	thePlayer.VAO5.Delete();
	shaderProgram.Delete();

	// Delete the window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}

void handleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}