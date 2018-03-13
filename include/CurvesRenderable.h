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
		RenderableType getType() const override {return m_curveRenderType;}
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
		/// @brief set the compute type of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setCurveType(CurveType _type);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the render type of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		inline void setRibbons() {m_curveRenderType = CURVES_RIBBONS;}
		inline void setLines() {m_curveRenderType = CURVES_LINES;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the mesh
		//----------------------------------------------------------------------------------------------------------------------
		void setCurves(Curves const &_curves);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the colour of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setColour(glm::vec3 const &_col);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the width for the curve ribbons
		//----------------------------------------------------------------------------------------------------------------------
		void setWidth(float _width) {m_ribbonWidth = _width;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the colour of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		glm::vec3 getColour() const {return m_colour;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the number of indices in this renderable
		//----------------------------------------------------------------------------------------------------------------------
		unsigned int getIndices() const {return m_indices;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the width for the curve ribbons
		//----------------------------------------------------------------------------------------------------------------------
		float getWidth() const {return m_ribbonWidth;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the Roughness of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setRoughness(float const &_roughness);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the Roughness of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		float getRoughness() const {return m_roughness;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief set the Metallic of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		void setMetallic(float const &_metallic);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the Metallic of this renderable
		//----------------------------------------------------------------------------------------------------------------------
		float getMetallic() const {return m_metallic;}

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_curveType The compute type of the curves
		//----------------------------------------------------------------------------------------------------------------------
		CurveType m_curveType;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_curveRenderType The renderable type of the curves
		//----------------------------------------------------------------------------------------------------------------------
		RenderableType m_curveRenderType;
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
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_ribbonWidth the width of our renderable ribbons
		//----------------------------------------------------------------------------------------------------------------------
		float m_ribbonWidth;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief m_roughness, m_metallic roughness and metallic
		//----------------------------------------------------------------------------------------------------------------------
		float m_roughness, m_metallic;
};

#endif // CURVESRENDERABLE_H
