#include "main.h"
#include "semi_circle.h"
#include <iostream>
#include <stdio.h>

Semi_Circle :: Semi_Circle (float x, float y) {
	this->position = glm::vec3 (x, y, 0);
    this->rotation = 0;
    // this->bounding_box = { this->position.x, this->position.y + 0.25, 1, 0.5 };

    int n = 30;
    float m = 360/n;
    float c = 1.3f;
    float c2 = 1.2f;
    float pi = 3.1415f;

    GLfloat outer[1000];
    GLfloat inner[1000];

    for (int i = 0; i < n/2; ++i) {
        outer [9*i] = 0.000f;
        outer [9*i + 1] = 0.000f;
        outer [9*i + 2] = 0.000f;
        outer [9*i + 3] = c * cos ((m * pi * (i+1)) / 180);
        outer [9*i + 4] = c * sin ((m * pi * (i+1)) / 180);
        outer [9*i + 5] = 0.000f;
        outer [9*i + 6] = c * cos ((m * pi * (i)) / 180);
        outer [9*i + 7] = c * sin ((m * pi * (i)) / 180);
        outer [9*i + 8] = 0.000f;
    }
    for (int i = 0; i < n/2; ++i) {
        inner [9*i] = 0.000f;
        inner [9*i + 1] = 0.000f;
        inner [9*i + 2] = 0.000f;
        inner [9*i + 3] = c2 * cos ((m * pi * (i+1)) / 180);
        inner [9*i + 4] = c2 * sin ((m * pi * (i+1)) / 180);
        inner [9*i + 5] = 0.000f;
        inner [9*i + 6] = c2 * cos ((m * pi * (i)) / 180);
        inner [9*i + 7] = c2 * sin ((m * pi * (i)) / 180);
        inner [9*i + 8] = 0.000f;
    }

    this->outer = create3DObject(GL_TRIANGLES, (n*3)/2, outer, COLOR_ORANGE, GL_FILL);
    this->inner = create3DObject(GL_TRIANGLES, (n*3)/2, inner, COLOR_BACKGROUND, GL_FILL);
}

void Semi_Circle :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->outer);
    draw3DObject(this->inner);
}

void Semi_Circle :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Semi_Circle :: return_position () {
    return this->position;
}

// bounding_box_t Semi_Circle :: return_bounding_box () {
//     return this->bounding_box;
// }

void Semi_Circle :: update () {
    // this->bounding_box = { this->position.x, this->position.y + 0.25, 1, 0.5 };
}