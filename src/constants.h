#pragma once

#include <memory>
#include <raylib.h>
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

	namespace Gui {
	    inline constexpr int TURRET_BOX_WIDTH = 100;
	    inline constexpr int TURRET_BOX_HEIGHT = 100;
	    inline constexpr int TURRET_BOX_1_X = Window::WIDTH / 2 - TURRET_BOX_WIDTH / 2;
	    inline constexpr int TURRET_BOX_2_X = Window::WIDTH / 2 - TURRET_BOX_WIDTH / 2 + 125;
	    inline constexpr int TURRET_BOX_Y = Window::HEIGHT - 100;
	}

	namespace Colors {
	    inline constexpr Color HOVER_EFFECT = CLITERAL(Color){ 255, 255, 255, 50 };
	}

	namespace Towers {
	    inline constexpr int TURRET_PRICE = 30;
	    inline constexpr int TURRET_RANGE = 100.0f;

	    inline constexpr int SNIPER_PRICE = 45;
	    inline constexpr int SNIPER_RANGE = 200.0f;
	}
}

inline bool operator<(Vector2 lhs, Vector2 rhs) {
	return lhs < rhs;
}
