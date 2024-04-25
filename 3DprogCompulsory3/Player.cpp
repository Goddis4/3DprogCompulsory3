#include "Player.h"
#include <iostream>

float Player::GetA()
{
    return a;
}

void Player::DeleteVBOANDVAO()
{
	VAO5.Delete();
}

void Player::UnbindVAO()
{
	VAO5.Unbind();
}

void Player::BindVAO()
{
	VAO5.Bind();
}

void Player::UpdateVertices(float xSpeed, float ySpeed, float zSpeed, glm::vec3 velocity)
{
	position.x += xSpeed;
	position.y += ySpeed;
	position.z += zSpeed;
}

VBO Player::GetVBO()
{
	return VBO1;
}

// Handles key input to move player
void Player::Input(GLFWwindow* window)
{
	float speed = 0.1f;
	float translationSpeed = speed;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && up) 
	{
		UpdateVertices(0, 0, -speed, glm::vec3(0, 0, 1));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && down) 
	{
		UpdateVertices(0, 0, speed, glm::vec3(0, 0, 1));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && left) 
	{
		UpdateVertices(-speed, 0, 0, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && right) 
	{
		UpdateVertices(speed, 0, 0, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && fuel > 0 && fuel > 20) 
	{
		UpdateVertices(0, speed * 50, 0, glm::vec3(0, 1, 0));
		fuel -= 1.0f/20.0f;
	}
	
}

bool Player::CheckCollision( Player& anotherCube)
{
	float distanceCentres = glm::length(position - anotherCube.position);
		
	if (distanceCentres <= (sphereRadius + anotherCube.sphereRadius)) 
	{
		float minimuntranslation = sphereRadius +anotherCube.sphereRadius - distanceCentres;
		auto dirvec = glm::normalize(position - anotherCube.position);
		position += dirvec * minimuntranslation;

		anotherCube.move = false;
		return true; 
	}
	else 
	{
		anotherCube.move = true;
	}

	// Detected no collision
	return false;
}

std::vector<double> calculateDerivative(const std::vector<double>& coefficients) 
{
	std::vector<double> derivativeCoefficients;

	// Calculate derivative coefficients
	for (size_t i = 1; i < coefficients.size(); ++i) 
	{
		derivativeCoefficients.push_back(i * coefficients[i]);
	}

	return derivativeCoefficients;
}

double polynomialEvaluation(const std::vector<double>& coefficients, double x) {
	double result = 0.0;
	double power = 1.0;
	for (size_t i = 0; i < coefficients.size(); ++i) 
	{
		result += coefficients[i] * power;
		power *= x;
	}
	return result;
}

double calculateDerivativeAtPoint(const std::vector<double>& coefficients, double x) 
{
	std::vector<double> derivativeCoefficients = calculateDerivative(coefficients);

	return polynomialEvaluation(derivativeCoefficients, x);
}


void Player::Path(std::vector<double> coefficients)
{
	double derivative = calculateDerivativeAtPoint(coefficients, xValue) / 4096;
	for (Vertex& vertex : mVertecies) 
	{
		position.x += xSpeed / 2;
		
		if (xPositiveDirection) position.z += derivative;
		else position.z -= derivative;
	}
	xValue += xSpeed;
	if (xValue >= 1) 
	{
		xSpeed *= -1;
		xPositiveDirection = false;
	}
	else if (xValue <= -0.25) 
	{
		xSpeed *= -1;
		xPositiveDirection = true;
	}
}

glm::vec3 Player::barycentricCoordinatesCalculation(glm::vec3& cPoint, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, bool climbable)
{
	glm::vec3 point = cPoint;

	if (!climbable)
	{
		planePoints[0] = glm::vec3(-1, 1,  1) + position;
		planePoints[1] = glm::vec3( 1, 1,  1) + position;
		planePoints[2] = glm::vec3( 1, 1, -1) + position;
		planePoints[3] = glm::vec3(-1, 1, -1) + position;
		v0.y = 0;
		v1.y = 0;
		v2.y = 0;
		point.y = 0;
	}

	glm::vec3 v0v1(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
	glm::vec3 v0v2(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);
	glm::vec3 v0p(point.x - v0.x, point.y - v0.y, point.z - v0.z);

	// Calculate dot products
	float dot00 = glm::dot(v0v1, v0v1);
	float dot01 = glm::dot(v0v1, v0v2);
	float dot02 = glm::dot(v0v1, v0p );
	float dot11 = glm::dot(v0v2, v0v2);
	float dot12 = glm::dot(v0v2, v0p );

	// Calculate barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
	float w = 1 - u - v;
	if (u > 0 && v > 0 && w > 0) 
	{
		if (climbable)
		{
			float heightV6 = v0.y * w + v1.y * u + v2.y * v;
			cPoint.y = heightV6 + 1; // -19 is planePosition.y -2. Offset to have player on top 
		}
		else
		{
			cPoint.y += 2;
		}
	}

	return glm::vec3(u, v, w);
}
