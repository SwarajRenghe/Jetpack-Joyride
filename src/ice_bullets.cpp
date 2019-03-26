#include "main.h"
#include "ice_bullets.h"
#include <iostream>
#include <stdio.h>

Ice_Bullets :: Ice_Bullets (float x, float y) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.15;
    this->direction = 1;
    this->x_speed = 0.02;
    this->state = 1;
    this->count = 0;
    this->y_accelaration = 0.005;
    this->bounding_box = { this->position.x, this->position.y, 0.5, 0.5 };

    static const GLfloat bullet[] = {
        -0.25f,  0.00f,  0.0f,
        0.25f,  0.00f,  0.0f,
        0.0f,  0.25f,  0.0f,
        -0.25f,  0.00f,  0.0f,
        0.25f,  0.00f,  0.0f,
        0.0f, -0.25f,  0.0f,
    };

    this->bullet = create3DObject(GL_TRIANGLES, 6, bullet, COLOR_LIME_GREEN, GL_FILL);
}

void Ice_Bullets :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->bullet);
}

void Ice_Bullets :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Ice_Bullets :: return_position () {
    return this->position;
}

bounding_box_t Ice_Bullets :: return_bounding_box () {
    return this->bounding_box;
}

void Ice_Bullets :: update () {
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

    this->bounding_box = { this->position.x, this->position.y, 1, 1 };
}