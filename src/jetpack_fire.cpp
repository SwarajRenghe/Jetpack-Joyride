#include "main.h"
#include "jetpack_fire.h"
#include <iostream>
#include <stdio.h>

Jetpack_Fire :: Jetpack_Fire (float x, float y) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->bounding_box = { this->position.x, this->position.y, 1, 1 };

    this->gravity = 0.005;
    this->downwardVelocity = 0;

    static const GLfloat outer_orange[] = {
        -0.07f,  0.0f,  0.0f,
         0.07f,  0.0f,  0.0f,
        -0.09f,   0.1f,  0.0f,
        -0.07f,  0.0f,  0.0f,
         0.07f,  0.0f,  0.0f,
        +0.09f,   0.1f,  0.0f,
        -0.07f,  0.0f,  0.0f,
         0.07f,  0.0f,  0.0f,
         0.000f, 0.2f, 0.0f,
    };

    static const GLfloat inner_red[] = {
        -0.05f,  0.0f,  0.0f,
         0.05f,  0.0f,  0.0f,
        -0.06f,  0.07f,  0.0f,
        -0.05f,  0.0f,  0.0f,
         0.05f,  0.0f,  0.0f,
        +0.06f,  0.07f,  0.0f,
        -0.05f,  0.0f,  0.0f,
         0.05f,  0.0f,  0.0f,
         0.000f,  0.1f, 0.0f,
    };

    this->outer_orange = create3DObject(GL_TRIANGLES, 9, outer_orange, COLOR_YELLOW, GL_FILL);
    this->inner_red = create3DObject(GL_TRIANGLES, 9, inner_red, COLOR_RED, GL_FILL);
}

void Jetpack_Fire :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->outer_orange);
    draw3DObject(this->inner_red);
}

void Jetpack_Fire :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Jetpack_Fire :: update () {
    this->bounding_box = { this->position.x, this->position.y, 0.375, 0.875 };

    this->set_position (this->position.x, this->position.y-this->downwardVelocity);
    this->downwardVelocity += this->gravity;

    this->rotation += 15;
}

glm::vec3 Jetpack_Fire :: return_position () {
    return this->position;
}

bounding_box_t Jetpack_Fire :: return_bounding_box () {
    return this->bounding_box;
}