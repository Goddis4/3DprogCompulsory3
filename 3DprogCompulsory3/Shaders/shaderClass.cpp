#include "shaderClass.h"

// Reads a text file and outputs a string with everything in the text file
std::string getFileText(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (!in.is_open()) 
	{
		std::cerr << "Error trying to open file: " << filename << std::endl;
		return "";
	}

	try 
	{
		std::ostringstream text;
		text << in.rdbuf();
		in.close();
		return text.str();
	}
	catch (const std::exception& e) 
	{
		std::cerr << "Exception while reading file: " << e.what() << std::endl;
	}
	catch (...) 
	{
		std::cerr << "Unknown exception occurred trying to reading file." << std::endl;
	}
	return "";
	
	if (in)
	{
		std::string text;
		in.seekg(0, std::ios::end);
		text.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&text[0], text.size());
		in.close();
		return(text);
	}
	throw(errno);
	
}

// From two different shaders, this constructor builds the shader program
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
	std::string vertexCode = getFileText(vertexFile);
	std::string fragmentCode = getFileText(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Create Vertex Shader Cube and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Cube
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	// Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	// Create Fragment Shader Cube and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Cube
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	// Create Shader Program Cube and get its reference
	ID = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// Link all the shaders together into the Shader Program
	glLinkProgram(ID);

	// Delete the Vertex and Fragment Shader objects that are now useless
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void Shader::Activate()
{
	glUseProgram(ID);
}

// Deletes the Shader Program
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::setInt(const std::string& name, int value) const
{
   glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
