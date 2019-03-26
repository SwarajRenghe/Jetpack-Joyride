#include "main.h"

class Semi_Circle {
public:
	Semi_Circle () {}
	Semi_Circle (float x, float y);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw (glm::mat4 VP);
	void set_position (float x, float y);
	void update ();
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
    float rotation;
private:
	VAO *outer;
	VAO *inner;
};