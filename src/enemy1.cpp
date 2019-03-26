#include "main.h"
#include "enemy1.h"
#include <iostream>
#include <stdio.h>

Enemy1 :: Enemy1 (float x, float y, float rotation) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = rotation;
    this->bounding_box = { this->position.x, this->position.y, 0.9, 0.2 };

    static const GLfloat square1[] = {
         0.1f,  0.1f,  0.0f,
         0.1f, -0.1f,  0.0f,
        -0.1f,  0.1f,  0.0f,
         0.1f, -0.1f,  0.0f,
        -0.1f,  0.1f,  0.0f,
        -0.1f, -0.1f,  0.0f,
    };
    static const GLfloat square2[] = {
         0.8f,  0.1f,  0.0f,
         0.8f, -0.1f,  0.0f,
        -0.8f,  0.1f,  0.0f,
         0.8f, -0.1f,  0.0f,
        -0.8f,  0.1f,  0.0f,
        -0.8f, -0.1f,  0.0f,
    };

    this->square1 = create3DObject(GL_TRIANGLES, 6, square1, COLOR_ORANGE, GL_FILL);
    this->square2 = create3DObject(GL_TRIANGLES, 6, square2, COLOR_ORANGE, GL_FILL);
}

void Enemy1 :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->square1);
    draw3DObject(this->square2);
}

void Enemy1 :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy1 :: set_rotation (float byHowMuch) {
    this->rotation = byHowMuch;
}

glm::vec3 Enemy1 :: return_position () {
    return this->position;
}

bounding_box_t Enemy1 :: return_bounding_box () {
    return this->bounding_box;
}

void Enemy1 :: update () {
    
}