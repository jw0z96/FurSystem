#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

class Shader
{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief ctor
		//----------------------------------------------------------------------------------------------------------------------
		Shader();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief ctor with paths to vertex & fragment shader
		//----------------------------------------------------------------------------------------------------------------------
		Shader(const char* vertexPath, const char* fragmentPath);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief ctor with paths to compute shader
		//----------------------------------------------------------------------------------------------------------------------
		Shader(const char* computePath);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief dtor
		//----------------------------------------------------------------------------------------------------------------------
		~Shader();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief use this shader
		//----------------------------------------------------------------------------------------------------------------------
		void use();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief delete this shader
		//----------------------------------------------------------------------------------------------------------------------
		void cleanUp();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief use this shader
		//----------------------------------------------------------------------------------------------------------------------
		GLuint getID() const {return pid;}

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief the program ID of the shader
		//----------------------------------------------------------------------------------------------------------------------
		GLuint pid;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief use this shader
		//----------------------------------------------------------------------------------------------------------------------
		void checkCompileErrors(unsigned int shader, std::string type);
};

#endif // SHADER_H
