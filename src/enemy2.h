#include "main.h"

class Enemy2 {
public:
	Enemy2 () {}
	Enemy2 (float x, float y);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void update ();
	void set_rotation (float byHowMuch);
	float is_visible ();
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
    float rotation;
    float speed;
    float direction;
    float count;
    float visible;
private:
	VAO *square1;
	VAO *square2;
	VAO *rod;
};