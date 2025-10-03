#pragma once

#include <memory>
template<typename T>
using SPTR = std::shared_ptr<T>;

template<typename T>
using UPTR = std::unique_ptr<T>;

namespace Constants {
	namespace Window {
		inline constexpr const char* TITLE = "Tower Defence";
		inline constexpr int WIDTH = 1280;
		inline constexpr int HEIGHT = 720;
	}

	namespace Menu {
		inline constexpr const char* TITLE = Window::TITLE;
		inline constexpr int TITLE_TOP_MARGIN = 50;
		inline constexpr int TITLE_BOTTOM_MARGIN = 50;
		inline constexpr int TITLE_FONT_SIZE = 100;
		inline constexpr int BUTTON_WIDTH = 150;
		inline constexpr int BUTTON_HEIGHT = 100;
		inline constexpr int BUTTON_MARGIN_BOTTOM = 10;
	}
}
