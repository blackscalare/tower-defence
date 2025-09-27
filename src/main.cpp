#include "renderer.h"
#include "logic.h"
#include <raylib.h>

int main() {
	InitWindow(1280, 720, "Tower Defence");
	SetTargetFPS(60);

	Map* map = new Map();
	Logic* logic = new Logic(map);
	Renderer* renderer = new Renderer(map, logic);

	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		logic->Update(GetFrameTime());
		renderer->Update();
		if(IsKeyPressed(KEY_R)) {
			map->Reload();
		}
		EndDrawing();
	}
}
