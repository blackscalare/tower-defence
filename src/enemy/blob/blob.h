#include "../enemy.h"
class Blob : public Enemy {
public:
	Blob();
	Blob(std::vector<Vector2> tileWaypoints, long id);
	Blob(Blob &&) = default;
	Blob(const Blob &) = default;
	Blob &operator=(Blob &&) = default;
	Blob &operator=(const Blob &) = default;
	~Blob();

private:
	
};
