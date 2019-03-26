#include "main.h"

#ifndef FLOOR_BLOCK_H
#define FLOOR_BLOCK_H

class FloorBlock {
public:
	FloorBlock () {}
	FloorBlock (color_t color);
	glm::vec3 position;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	glm::vec3 return_position ();
    float rotation;
private:
	VAO *object;
};

#endif