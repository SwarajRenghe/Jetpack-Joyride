#include "main.h"
#include "magnet.h"
#include <iostream>
#include <stdio.h>

Magnet :: Magnet (float x, float y) {
	this->position = glm::vec3 (x, y, 0);
    this->rotation = 0;
    this->magnetic_area_bounding_box = { this->position.x, this->position.y-0.4, 1, 0.4 };
    this->actual_bounding_box = { this->position.x, this->position.y, 1, 0.4 };

    static const GLfloat red[] = {
        -0.5f,  0.2f,  0.0f,
        -0.3f,  0.2f,  0.0f,
        -0.3f, -0.2f,  0.0f,
        -0.3f, -0.2f,  0.0f,
        -0.5f,  0.2f,  0.0f,
        -0.5f, -0.2f,  0.0f,
    };
    static const GLfloat middle[] = {
        -0.3f,  0.2f,  0.0f,
         0.3f,  0.2f,  0.0f,
         0.3f, -0.2f,  0.0f,
         0.3f, -0.2f,  0.0f,
        -0.3f,  0.2f,  0.0f,
        -0.3f, -0.2f,  0.0f,
    };
    static const GLfloat blue[] = {
         0.5f,  0.2f,  0.0f,
         0.3f,  0.2f,  0.0f,
         0.3f, -0.2f,  0.0f,
         0.3f, -0.2f,  0.0f,
         0.5f,  0.2f,  0.0f,
         0.5f, -0.2f,  0.0f,
    };

    this->red = create3DObject(GL_TRIANGLES, 12, red, COLOR_RED, GL_FILL);
    this->middle = create3DObject(GL_TRIANGLES, 12, middle, COLOR_BLACK, GL_FILL);
    this->blue = create3DObject(GL_TRIANGLES, 12, blue, COLOR_BLUE, GL_FILL);
}

void Magnet :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->red);
    draw3DObject(this->middle);
    draw3DObject(this->blue);
}

void Magnet :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Magnet :: return_position () {
    return this->position;
}

bounding_box_t Magnet :: return_magnetic_area_bounding_box () {
    return this->magnetic_area_bounding_box;
}

bounding_box_t Magnet :: return_actual_bounding_box () {
    return this->actual_bounding_box;
}

void Magnet :: update () {
    this->magnetic_area_bounding_box = { this->position.x, this->position.y-0.8, 1, 0.4 };
    this->actual_bounding_box = { this->position.x, this->position.y, 1, 0.4  };
}
