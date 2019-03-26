#include "main.h"

class Jetpack_Fire {
public:
	Jetpack_Fire () {}
	Jetpack_Fire (float x, float y);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void update ();
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
    float rotation;
    float gravity;
    float downwardVelocity;
private:
	VAO *outer_orange;
	VAO *inner_red;
};