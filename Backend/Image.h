#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/stb_image/stb_image.h"

#include <string>

namespace QMB
{
	class Image
	{
		unsigned char* m_Raw = nullptr;
		int				m_Width = 0;
		int				m_Height = 0;
		int				m_ChannelCount = 0;
	public:

		// Construct from path
		Image(const std::string& path);

		// Default constructor
		Image();

		// Destroys Image
		~Image();

		// Frees the image
		void free();



	};
}
