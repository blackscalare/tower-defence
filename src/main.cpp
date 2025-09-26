#include "renderer.h"
#include <raylib.h>

int main() {
	InitWindow(1280, 720, "Tower Defence");
	SetTargetFPS(60);

	Map* map = new Map();
	Renderer* renderer = new Renderer(map);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		renderer->Update();
		if(IsKeyPressed(KEY_R)) {
			map->Reload();
		}
		EndDrawing();
	}
}
