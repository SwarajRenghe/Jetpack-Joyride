#include "main.h"
#include "floorBlock.h"
#include <iostream>
#include <stdio.h>

FloorBlock::FloorBlock (color_t color) {
	this->position = glm::vec3(0, 0, 0);
    this->rotation = 0;

    static const GLfloat vertex_buffer_data[] = {
         0.00f,  0.00f,  0.0f,
         0.90f,  0.00f,  0.0f,
         0.00f,  0.45f,  0.0f,
         0.00f,  0.45f,  0.0f,
         0.90f,  0.00f,  0.0f,
         0.90f,  0.45f,  0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void FloorBlock :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void FloorBlock :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 FloorBlock :: return_position () {
    return this->position;
}