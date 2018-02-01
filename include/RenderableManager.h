#ifndef RENDERABLEMANAGER_H
#define RENDERABLEMANAGER_H

#include <vector>
#include <memory>

#include "Renderable.h"

class RenderableManager
{
	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief private dummy constructor for the singleton
		//----------------------------------------------------------------------------------------------------------------------
		RenderableManager();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief our singleton instance
		//----------------------------------------------------------------------------------------------------------------------
		static RenderableManager* m_instance;

	public:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief get the singleton instance
		//----------------------------------------------------------------------------------------------------------------------
		static RenderableManager* getInstance() {if (!m_instance){m_instance = new RenderableManager();} return m_instance;}
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief dtor
		//----------------------------------------------------------------------------------------------------------------------
		~RenderableManager();
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief register a new renderable
		//----------------------------------------------------------------------------------------------------------------------
		void registerRenderable(std::shared_ptr<Renderable> _renderable);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief register a new renderable
		//----------------------------------------------------------------------------------------------------------------------
		void deregisterRenderable(std::shared_ptr<Renderable> _renderable);
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief draw our registered renderables
		//----------------------------------------------------------------------------------------------------------------------
		void drawRenderables();

	private:
		//----------------------------------------------------------------------------------------------------------------------
		/// @brief Our Renderables
		//----------------------------------------------------------------------------------------------------------------------
		std::vector<std::shared_ptr<Renderable>> m_renderables;
};

#endif // RENDERABLEMANAGER_H
