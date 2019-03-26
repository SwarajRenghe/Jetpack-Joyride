#include "main.h"

class Ice_Bullets {
public:
	Ice_Bullets () {}
	Ice_Bullets (float x, float y);
	glm::vec3 position;
	bounding_box_t bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void set_rotation (float byHowMuch);
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
	void update ();
    float rotation;
    float speed;
    float direction;
    float state;
    float count;
    float y_accelaration;
    float x_speed;
private:
	VAO *bullet;
};