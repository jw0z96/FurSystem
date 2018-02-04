#ifndef CURVES_H
#define CURVES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

struct Curve
{
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief the curve vertices
	//----------------------------------------------------------------------------------------------------------------------
	glm::vec3 vertices[5]; // hard coded 5 vertices
};

struct Curves
{
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief constructor
	//----------------------------------------------------------------------------------------------------------------------
	Curves(){}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief constructor
	//----------------------------------------------------------------------------------------------------------------------
	Curves(std::vector<Curve>& _curves)
	{
		m_curves = _curves;
	}
	//----------------------------------------------------------------------------------------------------------------------
	/// @brief m_curves the curves
	//----------------------------------------------------------------------------------------------------------------------
	std::vector<Curve> m_curves;
};

#endif // CURVES_H
