#include "main.h"

class Enemy3 {
public:
	Enemy3 () {}
	Enemy3 (float x, float y);
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
    float x_accelaration;
private:
	VAO *object;
};