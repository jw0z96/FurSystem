#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------

Shader::Shader()
{
	std::cout<<"Shader()\n";
}

//----------------------------------------------------------------------------------------------------------------------

Shader::Shader(const char* computePath)
{
	std::cout<<"Shader(const char* computePath)\n";
	// 1. retrieve the vertex/fragment source code from filePath
	std::string computeCode;
	std::ifstream cShaderFile;
	// ensure ifstream objects can throw exceptions:
	cShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		cShaderFile.open(computePath);
		std::stringstream cShaderStream;
		// read file's buffer contents into streams
		cShaderStream << cShaderFile.rdbuf();
		// close file handlers
		cShaderFile.close();
		// convert stream into string
		computeCode = cShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* cShaderCode = computeCode.c_str();
	// 2. compile shaders
	unsigned int compute;
	// vertex shader
	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &cShaderCode, NULL);
	glCompileShader(compute);
	checkCompileErrors(compute, "COMPUTE");
	// shader Program
	pid = glCreateProgram();
	glAttachShader(pid, compute);
	glLinkProgram(pid);
	checkCompileErrors(pid, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(compute);
}

//----------------------------------------------------------------------------------------------------------------------

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &geoPath)
{
	std::cout<<"Shader(const std::string &vertexPath, std::string &fragmentPath, const std::string &geoPath)\n";
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream<<vShaderFile.rdbuf();
		fShaderStream<<fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	// shader Program
	pid = glCreateProgram();
	// 2. compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	const char* vShaderCode = vertexCode.c_str();
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	glAttachShader(pid, vertex);
	// fragment Shader
	const char* fShaderCode = fragmentCode.c_str();
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	glAttachShader(pid, fragment);

	if(geoPath != "")
	{
		std::string geoCode;
		std::ifstream gShaderFile;
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			gShaderFile.open(geoPath);
			std::stringstream gShaderStream;
			// read file's buffer contents into streams
			gShaderStream<<gShaderFile.rdbuf();
			// close file handlers
			gShaderFile.close();
			// convert stream into string
			geoCode = gShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		// compile shader
		unsigned int geo;
		const char* gShaderCode = geoCode.c_str();
		geo = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geo, 1, &gShaderCode, NULL);
		glCompileShader(geo);
		checkCompileErrors(geo, "GEOMETRY");
		glAttachShader(pid, geo);
		glLinkProgram(pid);
		glDeleteShader(geo);
	}
	else
	{
		glLinkProgram(pid);
	}

	checkCompileErrors(pid, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

//----------------------------------------------------------------------------------------------------------------------

Shader::~Shader()
{
	std::cout<<"~Shader()\n";
}

//----------------------------------------------------------------------------------------------------------------------

void Shader::use()
{
	glUseProgram(pid);
}

//----------------------------------------------------------------------------------------------------------------------

void Shader::cleanUp()
{
	glDeleteProgram(pid);
}

//----------------------------------------------------------------------------------------------------------------------

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
