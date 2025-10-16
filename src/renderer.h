#pragma once

#include "map/map.h"
#include "logic.h"
#include <map>

class Renderer {
public:
	Renderer() {};
	Renderer(Map* map, Logic* logic);
	Renderer(Renderer &&) = default;
	Renderer(const Renderer &) = default;
	Renderer &operator=(Renderer &&) = default;
	Renderer &operator=(const Renderer &) = default;
	~Renderer() {};

	void Update();
private:
	Map* map;
	Logic* logic;

	enum TextureName {
		ARROW,
		SKELETON,
		TURRET,
		SNIPER,
		BOMBER
	};

	const char* TextureNameToString(TextureName t) {
		switch (t) {
			case ARROW: return "ARROW";
			case SKELETON: return "SKELETON";
			case TURRET: return "TURRET";
			case SNIPER: return "SNIPER";
		}
	}


	void DrawTiles();
	void DrawGameObjects();
	void DrawGui();
	void DrawTowerBoxes();
	void DrawHoverEffect();
	void DrawDebug();
	void DrawProjectileWithRotation(Texture* texture, const Vector2& pos, const Vector2& goal);
	void DrawTowerPlacementEffect();
	void DrawTowerAreaEffect(Vector2 pos, TextureName textureName, float range);

	std::map<TextureName, Texture> textures;
};
