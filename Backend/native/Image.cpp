#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <thirdparty/stb_image/stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <thirdparty/stb_image/stb_image_resize.h>

namespace qmb
{
	
	Image Image::load_image(const std::string& path)
	{
		Image img = {};
		load_image(img, path);
		return img;

	}
	void Image::load_image(Image& img, const std::string& path)
	{

		if (img) img.free();
		img.m_Raw = stbi_load(path.c_str(), &(img.m_Width), &(img.m_Height), &(img.m_ChannelCount), 4);


		// a bit more easy to read imo
		int area = img.m_Width * img.m_Height;


		unsigned char* p = img.m_Raw;
		unsigned char* end = p + area * 4;

		while (p < end) {
			std::swap(p[0], p[2]);
			p += 4;
		}

	}


	void Image::free()
	{
		if (!m_Raw) return;
		stbi_image_free(m_Raw);
		m_Raw = nullptr;
		m_Width = 0;
		m_Height = 0;
	}

	Image::~Image()
	{
		free();
	}

	Image::operator BITMAPINFO() const {
		BITMAPINFO bmi = {};
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = m_Width;
		bmi.bmiHeader.biHeight = -m_Height; // top-down
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;      // RGBA
		bmi.bmiHeader.biCompression = BI_RGB;
		return bmi;
	}

	Image::operator bool() const {
		return m_Raw;
	}

	void Image::draw(HDC hdc, int x, int y, int w, int h) const {
		if (!m_Raw) return;

		BITMAPINFO bmi = static_cast<BITMAPINFO>(*this);
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchDIBits(
			hdc,
			x, y, w, h,
			0, 0, m_Width, m_Height,
			m_Raw,
			&bmi,
			DIB_RGB_COLORS,
			SRCCOPY
		);
	}

}