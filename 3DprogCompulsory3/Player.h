#pragma once
#include "Shaders/VBO.h"
#include "Shaders/VAO.h"
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <cmath>
#include "Construct.h"

using namespace std;

class Player 
{
public:
	std::array<Vertex, 36> mVertecies;
	std::array<Vertex, 6> mPlaneVertecies;
	glm::vec3 position;
	float r, g, b;
	glm::vec3 velocity;
	glm::vec3 PointPosition;
	float sphereRadius = 0;
	bool up = true;
	bool down = true;
	bool left = true;
	bool right = true;
	bool move = true; 
	float fuel = 100;
	
	VAO VAO5;
	VBO VBO1;
	Construct con;
	std::array<glm::vec3, 4> planePoints;
	
	Player(float scale, const glm::vec3& initialPosition, float red = 1.0f, float green = 1.0f, float blue = 1.0f, float figure = 1.f)
		   : a(scale), position(initialPosition), velocity(glm::vec3(0.0f)), r(red), g(green), b(blue), VBO1()
	{
		// Constructs the different cubes cubes
		// The figure decides what properties it will have
		if (figure == 1)
		{
			mVertecies = con.Cube(glm::vec3(red, green, blue));

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mVertecies.size() * sizeof(Vertex), mVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		
			VAO5.Unbind();
			VBO1.Unbind();
			planePoints[0] = glm::vec3( scale, -scale,  scale) + position;
			planePoints[1] = glm::vec3( scale,  scale,  scale) + position;
			planePoints[2] = glm::vec3( scale,  scale, -scale) + position;
			planePoints[3] = glm::vec3(-scale,  scale, -scale) + position;
		}
		else if (figure == 2) 
		{

			PointPosition = glm::vec3(10.0f, 0.0f, 0.0f);
			mPlaneVertecies = con.Surface(glm::vec3(red, green, blue), PointPosition);

			VAO5.Bind();
			VBO1.Bind();
			glBufferData(GL_ARRAY_BUFFER, mPlaneVertecies.size() * sizeof(Vertex), mPlaneVertecies.data(), GL_STATIC_DRAW);
			VAO5.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
			VAO5.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO5.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			VAO5.Unbind();
			VBO1.Unbind();
			planePoints[0] = glm::vec3(-scale, scale,		 scale) + position;
			planePoints[1] = glm::vec3( scale, scale * 1.5,  scale) + position;
			planePoints[2] = glm::vec3( scale, scale * 1.5, -scale) + position;
			planePoints[3] = glm::vec3(-scale, scale * 2,	-scale) + position;

		}
		sphereRadius = a; 
	}
	float GetA();
	void DeleteVBOANDVAO();
	void UnbindVAO();
	void BindVAO();
	void UpdateVertices(float xSpeed, float ySpeed, float zSpeed, glm::vec3 velocity);
	VBO GetVBO();
	void Input(GLFWwindow* window);

	void Path(std::vector<double> coefficients);
	
	bool CheckCollision( Player& anotherCube);
	

	glm::vec3 barycentricCoordinatesCalculation(glm::vec3& cPoint, glm::vec3 v0,glm::vec3 v1, glm::vec3 v2, bool climbable);

public:
	float a{ 1.0f };
	double xValue = 0;
	double xSpeed = 0.001;
	bool xPositiveDirection = true;

};