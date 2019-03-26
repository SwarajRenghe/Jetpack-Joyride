#include "main.h"
#include "enemy2.h"
#include <iostream>
#include <stdio.h>

Enemy2 :: Enemy2 (float x, float y) {
	this->position = glm::vec3 (x, y, 0);
    this->rotation = 0;
    this->speed = 0.1;
    this->direction = 1;
    this->bounding_box = { this->position.x, this->position.y, 4, 0.2 };
    this->count = 0;
    this->visible = 0;

    static const GLfloat rod[] = {
         0.1f,  0.1f,  0.0f,
         0.1f, -0.1f,  0.0f,
        -0.1f,  0.1f,  0.0f,
         0.1f, -0.1f,  0.0f,
        -0.1f,  0.1f,  0.0f,
        -0.1f, -0.1f,  0.0f,
        2.0f,  0.1f,  0.0f,
         2.0f, -0.1f,  0.0f,
        -2.0f,  0.1f,  0.0f,
         2.0f, -0.1f,  0.0f,
        -2.0f,  0.1f,  0.0f,
        -2.0f, -0.1f,  0.0f,
    };

    this->rod = create3DObject(GL_TRIANGLES, 12, rod, COLOR_RED, GL_FILL);
}

void Enemy2 :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    this->count += 1;
    if (this->count > 3*60 && this->count < 6*60) {
        draw3DObject(this->rod);
        this->visible = 1;
    }
    if (this->count >= 6*60) {
        this->count = 0;
        this->visible = 0;
    }
    
}

void Enemy2 :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy2 :: set_rotation (float byHowMuch) {
    this->rotation = byHowMuch;
}

float Enemy2 :: is_visible () {
    return this->visible;
}

glm::vec3 Enemy2 :: return_position () {
    return this->position;
}

bounding_box_t Enemy2 :: return_bounding_box () {
    return this->bounding_box;
}

void Enemy2 :: update () {
    this->bounding_box = { this->position.x, this->position.y, 4, 0.2 };
    if (this->direction == 1) {
        this->set_position (this->return_position().x, this->return_position().y + this->speed);
    }
    else {
        this->set_position (this->return_position().x, this->return_position().y - this->speed);
    }

    if (this->return_position().y >= 3 || this->return_position().y <= -1) {
        this->direction *= -1;
    }
}