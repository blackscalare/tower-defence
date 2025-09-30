#pragma once
#include <functional>
#include <raylib.h>
#include <vector>

class Menu {
public:
	Menu();
	Menu(std::vector<std::function<void()>> buttonCallbacks);
	Menu(Menu &&) = default;
	Menu(const Menu &) = default;
	Menu &operator=(Menu &&) = default;
	Menu &operator=(const Menu &) = default;
	~Menu();
	
	enum ButtonType {
		START_GAME,
		EDITOR,
		EXIT
	};

	struct MenuButton {
		ButtonType buttonType;
		int x;
		int y;
		int width;
		int height;
		Color color;
		const char* text;
		std::function<void()> callback;

		MenuButton(ButtonType buttonType, int x, int y, int width, int height, Color color, const char* text, std::function<void()> callback) 
			: buttonType(buttonType), x(x), y(y), width(width), height(height), color(color), text(text), callback(callback) {}
	};

	void Update(bool hasStartedGame);
	bool IsOpen() { return isOpen; }
	void Open() { isOpen = true; }
	void Close() { isOpen = false; }
private:
	void Init(std::vector<std::function<void()>> buttonCallbacks);
	void DrawTitle();
	void DrawButtons(bool hasStartedGame);
	int GetButtonY(int buttonIndex);
	int GetButtonTextX(const MenuButton* b);
	int GetButtonTextY(const MenuButton* b);
	void HandleButtonPress();
	
	bool isOpen;
	std::vector<MenuButton*> buttons;
	Color seeTorughRed = ColorAlpha(RED, 0.2);

};
