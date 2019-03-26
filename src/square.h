#include "main.h"

class Square {
public:
	Square () {}
	Square (float x, float y);
	glm::vec3 position;
	void draw(glm::mat4 VP);
	void update ();
	glm::vec3 return_position ();
	void set_position(float x, float y);
    float speed;
    float direction;
    float count;
    float rotation;
private:
	VAO *object;
};