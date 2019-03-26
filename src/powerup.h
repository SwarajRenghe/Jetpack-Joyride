#include "main.h"

class Powerup {
public:
	Powerup () {}
	Powerup (float x, float y, int type);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void set_rotation (float byHowMuch);
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
	void update ();
    float rotation;
    int type;
    float speed;
    float direction;
    float count;
    float y_accelaration;
    float x_speed;
    float state;
private:
	VAO *powerup1;
	VAO *powerup2;
	VAO *powerup3;
};