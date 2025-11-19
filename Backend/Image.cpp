#include "Image.h"


namespace QMB
{
	Image::Image(const std::string& path)
	{
		m_Raw = stbi_load(path.c_str(), &m_Width, &m_Height, &m_ChannelCount, 0);
	}
	Image::Image()
	{

	}

	void Image::free()
	{
		stbi_image_free(m_Raw);
		m_Raw = nullptr;
	}

	Image::~Image()
	{
		free();
	}
}