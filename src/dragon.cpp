#include "main.h"
#include "dragon.h"
#include "ice_bullets.h"
#include <iostream>
#include <stdio.h>

Dragon :: Dragon (float x, float y) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->direction = 1;
    this->health = 100;

    this->bounding_box = { this->position.x, this->position.y, 1, 1 };

    static const GLfloat object[] = {
        0.0f, 0.8f, 0.0f,
        0.4f, 0.0f, 0.0f,
        0.8f, 0.4f, 0.0f,
        0.0f, 0.8f , 0.0f,
        0.8f, 0.4f, 0.0f,
        0.72f,0.64f, 0.0f,
        0.0f, 1.0f, 0.0f,
        -0.2f, 0.7f, 0.0f,
        0.0f, 0.6f, 0.0f,
        0.74f, 0.52f, 0.0f,
        0.8f, 0.4f, 0.0f,
        1.44f,0.62f, 0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 12, object, COLOR_LIME_GREEN, GL_FILL);
}

void Dragon :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Dragon :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Dragon :: return_position () {
    return this->position;
}

bounding_box_t Dragon :: return_bounding_box () {
    return this->bounding_box;
}

void Dragon :: update () {
    this->bounding_box = { this->position.x, this->position.y, 1, 1 };

    if (this->direction == 1) {
        this->position.y -= 0.04;
    }
    else {
        this->position.y += 0.04;
    }

    if (this->position.y <= -2 || this->position.y >= +2) {
        this->direction *= -1;
    }
}