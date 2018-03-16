#ifndef COMPUTESHADERMANAGER_H
#define COMPUTESHADERMANAGER_H

#include "Curves.h"
#include "Mesh.h"
#include "Shader.h"

#include <GL/glew.h>

#include <chrono>

class ComputeShaderManager
{
	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief private dummy constructor for the singleton
		//----------------------------------------------------------------------------------------------------------------------
		ComputeShaderManager();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief our singleton instance
		//----------------------------------------------------------------------------------------------------------------------
		static ComputeShaderManager* m_instance;

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the singleton instance
		//----------------------------------------------------------------------------------------------------------------------
		static ComputeShaderManager* getInstance() {if (!m_instance){m_instance = new ComputeShaderManager();} return m_instance;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief dtor
		//----------------------------------------------------------------------------------------------------------------------
		~ComputeShaderManager();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief delete all shaders
		//----------------------------------------------------------------------------------------------------------------------
		void cleanUpAll();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief recompile all shaders
		//----------------------------------------------------------------------------------------------------------------------
		void recompileShaders();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief create an SSBO for a mesh
		//----------------------------------------------------------------------------------------------------------------------
		// void createCurvesSSBO(unsigned int &buffer, unsigned int _count);
		void createCurvesSSBO(unsigned int &buffer, Curves _curves);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief create an SSBO for a mesh
		//----------------------------------------------------------------------------------------------------------------------
		void createMeshSSBO(unsigned int &buffer, Mesh &mesh);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief copy Curves SSBO
		//----------------------------------------------------------------------------------------------------------------------
		void copyCurvesSSBO(unsigned int src, unsigned int &dst);

		//----------------------------------------------------------------------------------------------------------------------
		/// @brief randomly distribute curves in a compute shader
		//----------------------------------------------------------------------------------------------------------------------
		void randomDistribution(unsigned int &meshSSBO, unsigned int &curvesSSBO, unsigned int curveCount, unsigned int faceCount, float meshArea, float length, float variation);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief bend curves in a compute shader
		//----------------------------------------------------------------------------------------------------------------------
		void bendCurvesOperator(unsigned int curvesSSBO, glm::vec3 direction, float intensity);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief noise curves in a compute shader
		//----------------------------------------------------------------------------------------------------------------------
		void noiseCurvesOperator(unsigned int curvesSSBO, float intensity);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief clump curves in a compute shader
		//----------------------------------------------------------------------------------------------------------------------
		void clumpCurvesOperator(unsigned int curvesSSBO, unsigned int clumpCurvesSSBO, float envelope, bool preserveLength);


		//----------------------------------------------------------------------------------------------------------------------
		/// @brief start chrono timer
		//----------------------------------------------------------------------------------------------------------------------
		void startTimer();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief end timer and print elapsed
		//----------------------------------------------------------------------------------------------------------------------
		void endTimer();

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief our compute shaders
		//----------------------------------------------------------------------------------------------------------------------
		Shader randomDistributionShader, bendCurvesShader, noiseCurvesShader, clumpCurvesShader;
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief our timer for measuring performance
		//----------------------------------------------------------------------------------------------------------------------
		std::chrono::system_clock::time_point m_timer;
};

#endif // COMPUTESHADERMANAGER_H
