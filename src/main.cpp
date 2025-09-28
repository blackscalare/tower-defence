#include "renderer.h"
#include "logic.h"
#include <raylib.h>
#include "menu/menu.h"
#include "constants.h"

bool menuShowing = true;

void StartButtonCallback() {
	TraceLog(LOG_INFO, "Start button pressed");
	menuShowing = false;
}

void EditorButtonCallback() {
	TraceLog(LOG_INFO, "Editor button pressed");
}

void ExitButtonCallback() {
	TraceLog(LOG_INFO, "Exit button pressed");
	CloseWindow();
}

int main() {
	InitWindow(Constants::Window::WIDTH, Constants::Window::HEIGHT, "Tower Defence");
	SetTargetFPS(60);

	std::vector<std::function<void()>> buttonCallbacks = {StartButtonCallback, EditorButtonCallback, ExitButtonCallback};
	Map* map = new Map();
	Logic* logic = new Logic(map);
	Renderer* renderer = new Renderer(map, logic);
	Menu* menu = new Menu(buttonCallbacks);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		
		if(menuShowing) {
			menu->Update();
		} else {
			logic->Update(GetFrameTime());
			renderer->Update();
			if(IsKeyPressed(KEY_R)) {
				map->Reload();
			}
		}
			
		EndDrawing();
	}

	delete map;
	delete logic;
	delete renderer;
	delete menu;
}
