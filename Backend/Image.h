#pragma once
#include "../thirdparty/stb_image/stb_image.h"
#include "../thirdparty/stb_image/stb_image_resize.h"

#include <windows.h>
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
            // Constructs an empty, invalid image. 
		    Image() = default;

		    // Construct from path
		    Image(const std::string& path);

            static [[nodiscard]] Image load_image(const std::string& path);
            static void load_image(Image& img, const std::string& path);


		    Image resized(int new_width, int new_height);


		    // Destroys Image
		    ~Image();

		    // Frees the image
		    void free();
		    void draw(PAINTSTRUCT ps, HDC hdc, HWND hwnd, int x, int y) const;
		    explicit operator BITMAPINFO() const;
        
            // validity
            operator bool() const;


            // move constructor
            Image(Image&& other) noexcept {
                m_Raw = other.m_Raw;
                m_Width = other.m_Width;
                m_Height = other.m_Height;
                m_ChannelCount = other.m_ChannelCount;

                other.m_Raw = nullptr;
                other.m_Width = 0;
                other.m_Height = 0;
                other.m_ChannelCount = 0;
            }

            // move assignment
            Image& operator=(Image&& other) noexcept {
                if (this != &other) {
                    free(); // destroy current image first

                    m_Raw = other.m_Raw;
                    m_Width = other.m_Width;
                    m_Height = other.m_Height;
                    m_ChannelCount = other.m_ChannelCount;

                    other.m_Raw = nullptr;
                    other.m_Width = 0;
                    other.m_Height = 0;
                    other.m_ChannelCount = 0;
                }
                return *this;
            }

	    };
}
