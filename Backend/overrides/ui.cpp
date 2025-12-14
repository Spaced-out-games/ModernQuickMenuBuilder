#include "ui.h"
#ifdef  _DEBUG
#include <format>
#endif
namespace ui
{
	LRESULT drag_drop_bg_img(HWND hwnd, Image& target, WPARAM wParam, LPARAM lParam)
	{
		HDROP hDrop = (HDROP)wParam;
		UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, nullptr, 0);

		for (UINT i = 0; i < fileCount; ++i)
		{
			char filePath[MAX_PATH];
			DragQueryFileA(hDrop, i, filePath, MAX_PATH);

			// Optionally check the extension
			std::string path(filePath);
			if (path.ends_with(".bmp") || path.ends_with(".png") || path.ends_with(".jpg"))
			{
				#ifdef _DEBUG
				std::cout << std::format("Dropped file {}", path);
				#endif // _DEBUG

				Image::load_image(target, path);

				InvalidateRect(hwnd, nullptr, TRUE);
			}
		}

		DragFinish(hDrop);
		return 0;
	}
}