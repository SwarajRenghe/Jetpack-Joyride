#include "main.h"

class Water_Balloon {
public:
	Water_Balloon () {}
	Water_Balloon (float x, float y);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
	void update ();
    float rotation;
    float downward_velocity;
private:
	VAO *object;
};