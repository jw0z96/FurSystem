#ifndef MESHRENDERABLE_H
#define MESHRENDERABLE_H

#include <GL/glew.h>

#include "Renderable.h"
#include "Mesh.h"

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
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the type of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		renderableType getType() const override {return MESH;}

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_mesh The Mesh object
		//----------------------------------------------------------------------------------------------------------------------
		Mesh m_mesh;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_VAO The VAO and VBO ids
		//----------------------------------------------------------------------------------------------------------------------
		GLuint m_VAO, m_VBO;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_indices the number of indices to render
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int m_indices;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief generate the VAO for the renderable
		//----------------------------------------------------------------------------------------------------------------------
		void generateVAO();
};

#endif // MESHRENDERABLE_H
