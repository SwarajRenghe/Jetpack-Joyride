#include "main.h"

class Magnet {
public:
	Magnet () {}
	Magnet (float x, float y);
	glm::vec3 position;
	bounding_box_t magnetic_area_bounding_box;
	bounding_box_t actual_bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void update ();
	glm::vec3 return_position ();
	bounding_box_t return_magnetic_area_bounding_box ();
	bounding_box_t return_actual_bounding_box ();
    float rotation;
private:
	VAO *red;
	VAO *middle;
	VAO *blue;
};