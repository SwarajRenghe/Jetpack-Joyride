#include "main.h"
#include "coin.h"
#include <iostream>
#include <stdio.h>

/*
Type 1 - One Point
Type 2 - Two Points
Type 3 - Three Point
*/

Coin :: Coin (float x, float y, int type) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    if (type == 0 || type == 1 || type == 2) {
        this->type = 1;
    }
    else if (type == 3 || type == 4) {
        this->type = 2;
    }
    else {
        this->type = 3;
    }

    this->bounding_box = { this->position.x, this->position.y, 0.3, 0.3 };

    if (this->type == 1) {
        this->color = COLOR_GOLDEN;
    }
    else if (this->type == 2) {
        this->color = COLOR_BLACK;
    }
    else {
        this->color = COLOR_RED;
    }

    int n = 30;
    float m = 360/n;
    float c = 0.075f;
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

    this->object = create3DObject(GL_TRIANGLES, n*3, g_vertex_buffer_data, this->color, GL_FILL);
}

void Coin :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object);
}

void Coin :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

glm::vec3 Coin :: return_position () {
    return this->position;
}

bounding_box_t Coin :: return_bounding_box () {
    return this->bounding_box;
}

void Coin :: update () {
    this->bounding_box = { this->position.x, this->position.y, 0.3, 0.3 };
    this->rotation += (rand()%10 + 3);
}

// void Coin :: check_for_collision (float x, float y) {
//     this->position = glm::vec3(x, y, 0);
// }
