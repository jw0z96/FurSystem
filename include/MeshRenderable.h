#ifndef MESHRENDERABLE_H
#define MESHRENDERABLE_H

#include "Renderable.h"
#include "Mesh.h"

#include <GL/glew.h>

class MeshRenderable : public Renderable
{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		MeshRenderable();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		MeshRenderable(Mesh const &_mesh);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		~MeshRenderable();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief draw this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void draw() override;

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_mesh The Mesh object
		//----------------------------------------------------------------------------------------------------------------------
		Mesh m_mesh;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_VAO The VAO id
		//----------------------------------------------------------------------------------------------------------------------
		GLuint m_VAO;
		GLuint m_VBO;
		// GLuint m_EBO;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief generate the VAO for the renderable
		//----------------------------------------------------------------------------------------------------------------------
		void generateVAO();
};

#endif // MESHRENDERABLE_H
