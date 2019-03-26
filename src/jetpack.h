#include "main.h"

class Jetpack {
public:
	Jetpack () {}
	Jetpack (float x, float y, color_t color);
	glm::vec3 position;
	bounding_box_t bounding_box;
	bounding_box_t shield_bounding_box;
	void draw(glm::mat4 VP);
	void set_position(float x, float y);
	void move_left (float byHowMuch);
	void move_right (float byHowMuch);
	void jump_up (float byHowMuch);
	void jump_down (float byHowMuch);
	void update ();
	void shield ();
	void set_rotation (float byHowMuch);
	glm::vec3 return_position ();
	bounding_box_t return_bounding_box ();
	bounding_box_t return_shield_bounding_box ();
    float rotation;
    float gravity;
    float shieldTimer;
    float downwardVelocity;
    bool isInRing;
    bool isShield;
    int RingNumber;
private:
	VAO *body;
	VAO *neck;
	VAO *legs;
	VAO *face;
	VAO *hair;
	VAO *jetpack;
	VAO *shield1;
	VAO *shield2;
};