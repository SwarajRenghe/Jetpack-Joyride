#include "main.h"
#include "bullets.h"
#include <iostream>
#include <stdio.h>

Water_Balloon :: Water_Balloon (float x, float y) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->bounding_box = { this->position.x, this->position.y, 0.1, 0.1 };

    int n = 30;
    float m = 360/n;
    float c = 0.1f;
    float pi = 3.1415f;

    GLfloat g_vertex_buffer_data[1000];

    for (int i = 0; i < n; ++i) {
        g_vertex_buffer_data [9*i] = 0.000f;
        g_vertex_buffer_data [9*i + 1] = 0.000f;
        g_vertex_buffer_data [9*i + 2] = 0.000f;
        g_vertex_buffer_data [9*i + 3] = c * cos ((m * pi * (i+1)) / 180);
        g_vertex_buffer_data [9*i + 4] = c * sin ((m * pi * (i+1)) / 180);
        g_vertex_buffer_data [9*i + 5] = 0.000f;
        g_vertex_buffer_data [9*i + 6] = c * cos ((m * pi * (i)) / 180);
        g_vertex_buffer_data [9*i + 7] = c * sin ((m * pi * (i)) / 180);
        g_vertex_buffer_data [9*i + 8] = 0.000f;
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, COLOR_BLUE, GL_FILL);
}

void Water_Balloon :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Water_Balloon :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Water_Balloon :: return_position () {
    return this->position;
}

bounding_box_t Water_Balloon :: return_bounding_box () {
    return this->bounding_box;
}

void Water_Balloon :: update () {
    this->bounding_box = { this->position.x, this->position.y, 0.3, 0.3 };
    // this->rotation += 10;
    this->position.x += 0.2;
}