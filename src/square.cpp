#include "main.h"
#include "square.h"
#include <iostream>
#include <stdio.h>

Square :: Square (float x, float y) {
	this->position = glm::vec3 (x, y, 0);
    this->speed = 0.1;
    this->rotation = 0;
    this->direction = 1;
    this->count = 0;

    static const GLfloat object[] = {
         0.1f,  0.1f,  0.0f,
         0.1f, -0.1f,  0.0f,
        -0.1f,  0.1f,  0.0f,
         0.1f, -0.1f,  0.0f,
        -0.1f,  0.1f,  0.0f,
        -0.1f, -0.1f,  0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, object, COLOR_BLACK, GL_FILL);
}

void Square :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Square :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Square :: return_position () {
    return this->position;
}

void Square :: update () {
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