#include "menu.h"
#include "../constants.h"
#include <cassert>
#include <raylib.h>

Menu::Menu() {}

Menu::Menu(std::vector<std::function<void()>> buttonCallbacks) {
	isOpen = true;
	Init(buttonCallbacks);
}

Menu::~Menu() {
	for(MenuButton* b : buttons) {
		delete b;
	}
}

void Menu::Init(std::vector<std::function<void()>> buttonCallbacks) {
	assert(buttonCallbacks.size() == 3);

	MenuButton* startButton = new MenuButton(
		START_GAME,
		Constants::Window::WIDTH / 2,
		GetButtonY(0),
		Constants::Menu::BUTTON_WIDTH,
		Constants::Menu::BUTTON_HEIGHT,
		WHITE,
		"Start",
		buttonCallbacks[0]
	);

	MenuButton* editorButton = new MenuButton(
		EDITOR,
		Constants::Window::WIDTH / 2,
		GetButtonY(1),
		Constants::Menu::BUTTON_WIDTH,
		Constants::Menu::BUTTON_HEIGHT,
		WHITE,
		"Editor",
		buttonCallbacks[1]
	);

	MenuButton* exitButton = new MenuButton(
		EXIT,
		Constants::Window::WIDTH / 2,
		GetButtonY(2),
		Constants::Menu::BUTTON_WIDTH,
		Constants::Menu::BUTTON_HEIGHT,
		WHITE,
		"Exit",
		buttonCallbacks[2]
	);

	buttons.push_back(startButton);
	buttons.push_back(editorButton);
	buttons.push_back(exitButton);
}

void Menu::Update(bool hasStartedGame) {
	DrawTitle();
	DrawButtons(hasStartedGame);
	HandleButtonPress();
}

void Menu::DrawTitle() {
	DrawText(Constants::Menu::TITLE, (Constants::Window::WIDTH / 2) - (MeasureText(Constants::Menu::TITLE, Constants::Menu::TITLE_FONT_SIZE)) / 2,
		  Constants::Menu::TITLE_TOP_MARGIN, 
		  Constants::Menu::TITLE_FONT_SIZE, 
		  WHITE);
}

void Menu::DrawButtons(bool hasStartedGame) {
	for(const MenuButton* b : buttons) {
		if(b->buttonType == START_GAME && hasStartedGame) continue;
		Vector2 mousePos = GetMousePosition();
		if(CheckCollisionRecs(
			{static_cast<float>(b->x), static_cast<float>(b->y), Constants::Menu::BUTTON_WIDTH, Constants::Menu::BUTTON_HEIGHT},
			{mousePos.x, mousePos.y, 1, 1}
		)) {
			DrawRectangleLines(b->x, b->y, b->width, b->height, RED);
			DrawRectangle(b->x + 1, b->y + 1, b->width - 1 , b->height - 1, seeTorughRed);
		} else {
			DrawRectangleLines(b->x, b->y, b->width, b->height, b->color);
		}
		DrawText(b->text, GetButtonTextX(b), GetButtonTextY(b), 20, WHITE);
	}
}

void Menu::HandleButtonPress() {
	if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		for(const MenuButton* b : buttons) {
			Vector2 mousePos = GetMousePosition();
			if(CheckCollisionRecs(
				{static_cast<float>(b->x), static_cast<float>(b->y), Constants::Menu::BUTTON_WIDTH, Constants::Menu::BUTTON_HEIGHT},
				{mousePos.x, mousePos.y, 1, 1}
			)) {
				b->callback();
			}
		}
	}
}

int Menu::GetButtonY(int buttonIndex) {
	return Constants::Menu::TITLE_TOP_MARGIN + Constants::Menu::TITLE_FONT_SIZE + Constants::Menu::TITLE_BOTTOM_MARGIN  + ((Constants::Menu::BUTTON_HEIGHT + Constants::Menu::BUTTON_MARGIN_BOTTOM) * buttonIndex);
}

int Menu::GetButtonTextX(const MenuButton* b) {
	return b->x + b->width / 2 - MeasureText(b->text, 2);
}

int Menu::GetButtonTextY(const MenuButton* b) {
	return b->y + b->height / 2 - 20 / 2;
}
