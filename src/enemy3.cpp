#include "main.h"
#include "enemy3.h"
#include <iostream>
#include <stdio.h>

Enemy3 :: Enemy3 (float x, float y) {
	this->position = glm::vec3 (x, y, 0);
    this->rotation = 0;
    this->speed = 0.2;
    this->direction = 1;
    this->bounding_box = { this->position.x, this->position.y + 0.25, 1, 0.5 };
    this->count = 0;
    this->visible = 1;
    this->direction = 1;
    this->x_accelaration = 0.0025;

    int n = 30;
    float m = 360/n;
    float c = 0.5f;
    float pi = 3.1415f;

    GLfloat g_vertex_buffer_data[1000];

    for (int i = 0; i < n/2; ++i) {
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

    this->object = create3DObject(GL_TRIANGLES, (n*3)/2, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);

}

void Enemy3 :: draw (glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy3 :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy3 :: set_rotation (float byHowMuch) {
    this->rotation = byHowMuch;
}

glm::vec3 Enemy3 :: return_position () {
    return this->position;
}

bounding_box_t Enemy3 :: return_bounding_box () {
    return this->bounding_box;
}

float Enemy3 :: is_visible () {
    return this->visible;
}

void Enemy3 :: update () {
    if (this->direction == 1) {
        this->set_position (this->position.x -= this->speed, this->return_position().y);
        this->speed -= this->x_accelaration;
    }
    else {
        this->set_position (this->position.x += this->speed, this->return_position().y);
        this->speed += this->x_accelaration;
    }
    // if (this->return_position().x <= -2) {
    //     this->direction *= -1;
    // }

    this->position.y -= 0.03;
    
    this->rotation += (15);
    if (this->rotation == 360) {
        this->rotation = 0;
    }
    this->bounding_box = { this->position.x, this->position.y + 0.25, 1, 0.5 };
}