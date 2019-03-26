#include "main.h"

class Enemy1 {
public:
	Enemy1 () {}
	Enemy1 (float x, float y, float rotation);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void update ();
	void set_rotation (float byHowMuch);
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
    float rotation;
private:
	VAO *square1;
	VAO *square2;		
};