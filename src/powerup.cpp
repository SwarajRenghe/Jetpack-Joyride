#include "main.h"
#include "powerup.h"
#include <iostream>
#include <stdio.h>

/*
Type 1 - Extra Score
Type 2 - Full Health
Type 3 - Sword
*/

Powerup :: Powerup (float x, float y, int type) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.15;
    this->type = type;
    this->direction = 1;
    this->x_speed = 0.02;
    this->state = 1;
    this->count = 0;
    this->y_accelaration = 0.005;
    this->bounding_box = { this->position.x, this->position.y, 0.5, 0.5 };

    static const GLfloat powerup[] = {
        -0.25f,  0.00f,  0.0f,
        0.25f,  0.00f,  0.0f,
        0.0f,  0.25f,  0.0f,
        -0.25f,  0.00f,  0.0f,
        0.25f,  0.00f,  0.0f,
        0.0f, -0.25f,  0.0f,
    };

    this->powerup1 = create3DObject(GL_TRIANGLES, 6, powerup, COLOR_PURPLE, GL_FILL);
    this->powerup2 = create3DObject(GL_TRIANGLES, 6, powerup, COLOR_GREEN, GL_FILL);
    this->powerup3 = create3DObject(GL_TRIANGLES, 6, powerup, COLOR_ORANGE, GL_FILL);
}

void Powerup :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (this->type == 1) {
	   draw3DObject(this->powerup1);
    }
    if (this->type == 2) {
       draw3DObject(this->powerup2);
    }
    if (this->type == 3) {
       draw3DObject(this->powerup3);
    }
}

void Powerup :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Powerup :: return_position () {
    return this->position;
}

bounding_box_t Powerup :: return_bounding_box () {
    return this->bounding_box;
}

void Powerup :: update () {
    if (this->state == 1) {
        this->set_position (this->position.x, this->position.y -= this->speed);
        this->speed -= this->y_accelaration;
        if (this->speed <= 0) {
            this->state = 2;
        }
    }

    if (this->state == 2) {
        this->set_position (this->position.x, this->position.y += this->speed);
        this->speed += this->y_accelaration;
        if (this->position.y >= 1) {
            this->state = 3;
        }
    }

    if (this->state == 3) {
        this->set_position (this->position.x, this->position.y += this->speed);
        this->speed -= this->y_accelaration;
        if (this->speed <= 0) {
            this->state = 4;
        }
    }

    if (this->state == 4) {
        this->set_position (this->position.x, this->position.y -= this->speed);
        this->speed += this->y_accelaration;
        if (this->speed >= 0.15) {
            this->state = 1;
        }
    }

    this->position.x -= x_speed;
    
    this->rotation += (15);
    if (this->rotation == 360) {
        this->rotation = 0;
    }

    this->bounding_box = { this->position.x, this->position.y, 0.5, 0.5 };
}