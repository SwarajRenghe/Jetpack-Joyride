#include "main.h"

class Coin {
public:
	Coin () {}
	Coin (float x, float y, int type);
	color_t color;
	int type;
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
	void update ();
    float rotation;
private:
	VAO *object;
};