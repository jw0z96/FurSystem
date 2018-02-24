#ifndef CURVESRENDERABLE_H
#define CURVESRENDERABLE_H

#include <GL/glew.h>

#include "Renderable.h"
#include "Curves.h"

class CurvesRenderable : public Renderable
{
	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief constructor
		//----------------------------------------------------------------------------------------------------------------------
		CurvesRenderable();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief destructor
		//----------------------------------------------------------------------------------------------------------------------
		~CurvesRenderable();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief draw this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void draw() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the type of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		renderableType getType() const override {return CURVES;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief generate the SSBO for the renderable
		//----------------------------------------------------------------------------------------------------------------------
		void generate() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief delete the VAO for the renderable
		//----------------------------------------------------------------------------------------------------------------------
		void cleanUp() override;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the source SSBO of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setSourceSSBO(GLuint _SSBO);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the colour of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setCurveType(CurveType _type);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the mesh
		//----------------------------------------------------------------------------------------------------------------------
		void setCurves(Curves const &_curves);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the colour of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setColour(glm::vec3 const &_col);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the colour of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 getColour() const {return m_colour;}

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_curveType The compute type of the curves
		//----------------------------------------------------------------------------------------------------------------------
		CurveType m_curveType;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_mesh The Mesh object
		//----------------------------------------------------------------------------------------------------------------------
		Curves m_curves;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_srcSSBO The source SSBO for the curves
		//----------------------------------------------------------------------------------------------------------------------
		GLuint m_srcSSBO;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_SSBO The SSBO for the curves
		//----------------------------------------------------------------------------------------------------------------------
		GLuint m_SSBO;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_emptyVAO empty vao for procedural geometry
		//----------------------------------------------------------------------------------------------------------------------
		GLuint m_emptyVAO;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_indices the number of indices to render
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int m_indices;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_colour the colour of our renderable
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 m_colour;
};

#endif // CURVESRENDERABLE_H
