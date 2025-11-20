#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/stb_image/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../thirdparty/stb_image/stb_image_resize.h"

namespace QMB
{
	Image::Image(const std::string& path)
	{
		m_Raw = stbi_load(path.c_str(), &m_Width, &m_Height, &m_ChannelCount, 4);
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
	Image Image::resized(int new_width, int new_height)
	{
		// if this image is null, create a null image and return it
		if (!m_Raw) return {};

		// try to allocate a buffer
		unsigned char* new_img = (unsigned char*)malloc(new_width * new_height * 4);

		// if it fails, return empty image
		if (!new_img) return {};

		// create an empty image
		Image img = {};

		// set some internal state. 
		img.m_Raw = new_img;
		img.m_ChannelCount = 4;
		img.m_Width = new_width;
		img.m_Height = new_height;

		// copy the buffer, resized. Error happens here, per breakpoint
		int success = stbir_resize_uint8(
			m_Raw, m_Width, m_Height, 0,       // source
			img.m_Raw, img.m_Width, img.m_Height, 0, // destination
			4                              // channels (RGBA)
		);

		// if resizing somehow fails,return an empty image
		if (!success) {
			::free(new_img);
			return {};
		}

		// return the image

		return img;




		/*


		Image img = {};


		if (!img.m_Raw) return img; // don't bother with resizing it.

		img.m_Raw = (unsigned char*)malloc(new_width * new_height * 4);


		img.m_ChannelCount = 4;
		img.m_Width = new_width;
		img.m_Height = new_height;
		stbir_resize_uint8(
			m_Raw, m_Width, m_Height, 0,       // source
			img.m_Raw, new_width, new_height, 0, // destination
			4                              // channels (RGBA)
		);

		return img;
		*/
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

	void Image::draw(PAINTSTRUCT ps, HDC hdc, HWND hwnd, int x, int y) const {
		if (!m_Raw) return;

		//;

		BITMAPINFO bmi = static_cast<BITMAPINFO>(*this);

		StretchDIBits(
			hdc,
			x, y, m_Width, m_Height,
			0, 0, m_Width, m_Height,
			m_Raw,
			&bmi,
			DIB_RGB_COLORS,
			SRCCOPY
		);

		//ReleaseDC(hwnd, hdc); // or EndPaint in WM_PAINT
	}

}