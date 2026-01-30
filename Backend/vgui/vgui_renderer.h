#pragma once
#include <stdint.h>


namespace native
{
	struct Application;
	struct Window;
}

namespace vgui
{
	namespace gfx
	{

		struct Color
		{
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};


		// Represents a table of function pointers and some platform-specific stuff
		class Context
		{

			// Owning application
			native::Application*	m_Application = nullptr;
			// Pointer to platform specific details of the gfx context. SDL_Renderer, {HDC, PAINTSTRUCT}, GLContext...
			void*					m_Platform = nullptr;

			// Target window
			native::Window*			m_Target = nullptr;

			public: // wrapper functions

		};

		// Initializes a vgui::gfx::Context
		void ctor_impl(native::Application& app, native::Window& target, Context& gfx);

		// Destroys the vgui::gfx;:context
		void dtor_impl(Context& gfx);

		void DrawRect_impl(Context& gfx, int x, int y, int x2, int y2)

	} // namespace gfx
} // namespace vgui