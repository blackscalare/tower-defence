#include "../enemy.h"

class Skeleton : public Enemy{
public:
	Skeleton();
	Skeleton(std::vector<Vector2> tileWaypoints, long id);
	Skeleton(Skeleton &&) = default;
	Skeleton(const Skeleton &) = default;
	Skeleton &operator=(Skeleton &&) = default;
	Skeleton &operator=(const Skeleton &) = default;
	~Skeleton();

private:
	
};
