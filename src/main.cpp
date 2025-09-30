#include "editor/editor.h"
#include "renderer.h"
#include "logic.h"
#include <raylib.h>
#include "menu/menu.h"
#include "constants.h"

bool menuShowing = true;
bool hasStartedGame = false;
bool shouldShowEditor = false;

void StartButtonCallback() {
	TraceLog(LOG_INFO, "Start button pressed");
	menuShowing = false;
	hasStartedGame = true;
}

void EditorButtonCallback() {
	TraceLog(LOG_INFO, "Editor button pressed");
	shouldShowEditor = true;
	menuShowing = false;
}

void ExitButtonCallback() {
	TraceLog(LOG_INFO, "Exit button pressed");
	CloseWindow();
}


int main() {
	InitWindow(Constants::Window::WIDTH, Constants::Window::HEIGHT, "Tower Defence");
	SetTargetFPS(60);
	SetExitKey(KEY_NULL);

	std::vector<std::function<void()>> buttonCallbacks = {StartButtonCallback, EditorButtonCallback, ExitButtonCallback};
	Map* map = new Map();
	Logic* logic = new Logic(map);
	Renderer* renderer = new Renderer(map, logic);
	Menu* menu = new Menu(buttonCallbacks);
	Editor* editor = nullptr;

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		
		if(IsKeyPressed(KEY_ESCAPE)) menuShowing = !menuShowing;

		if(menuShowing) {
			menu->Update(hasStartedGame);
		} else if(shouldShowEditor) {
			if(editor == nullptr) {
				editor = new Editor();
			}

			editor->Update();
		}
		else {
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
