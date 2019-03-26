#include "main.h"
#include "jetpack.h"
#include <iostream>
#include <stdio.h>

Jetpack::Jetpack (float x, float y, color_t color) {
	this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->bounding_box = { this->position.x, this->position.y, 0.75, 1.6 };
    this->shield_bounding_box = { this->position.x, this->position.y, 1.3, 1.3};
    this->shieldTimer = 0;
    this->isShield = false;

    this->isInRing = false;
    this->RingNumber = -1;
    this->gravity = 0.01;
    this->downwardVelocity = 0;

    static const GLfloat body[] = {
         0.25f,  0.25f,  0.0f,
         0.25f, -0.25f,  0.0f,
        -0.25f,  0.25f,  0.0f,
         0.25f, -0.25f,  0.0f,
        -0.25f,  0.25f,  0.0f,
        -0.25f, -0.25f,  0.0f,
    };
    static const GLfloat neck[] = {
        -0.05f, 0.375f,  0.0f,
         -0.05f, 0.25f,  0.0f,
         0.05f,  0.25f,  0.0f,
         0.05f,  0.25f,  0.0f,
        -0.05f, 0.375f,  0.0f,
         0.05f, 0.375f,  0.0f,
    };
    static const GLfloat legs[] = {
        -0.1f,  -0.25f,  0.0f,
         0.1f,  -0.25f,  0.0f,
         0.1f, -0.5f,  0.0f,
         0.1f, -0.5f,  0.0f,
        -0.1f,  -0.25f,  0.0f,
        -0.1f, -0.5f, 0.0f,
    };
    static const GLfloat face[] = {
         0.15f,  0.375f,  0.0f,
         -0.15f, 0.375f,  0.0f,
         0.15f, 0.75f,  0.0f,
         0.15f, 0.75f,  0.0f,
         -0.15f, 0.375f,  0.0f,
         -0.15f, 0.75f,  0.0f,
    };
    static const GLfloat hair[] = {
         -0.15f, 0.75f,  0.0f,
         0.15f, 0.75f,  0.0f,
         0.15f, 0.9f, 0.0f,           
    };
    static const GLfloat jetpack[] = {
        -0.25f,  0.15f,  0.0f,
        -0.25f,  -0.15f,  0.0f,
        -0.3f,   0.15f, 0.0f,
        -0.3f,   0.15f, 0.0f,
        -0.25f,  -0.15f,  0.0f,
        -0.3f,  -0.15f,  0.0f,
        -0.3f,  -0.3f,  0.0f,
        -0.3f,   0.3f, 0.0f,
        -0.5f,   0.3f, 0.0f,
        -0.5f,   0.3f, 0.0f,
        -0.3f,  -0.3f,  0.0f,
        -0.5f, -0.3f, 0.0f,
    };

    int n = 30;
    float m = 360/n;
    float c = 1.3f;
    float c2 = 1.2f;
    float pi = 3.1415f;

    GLfloat outer[1000];
    GLfloat inner[1000];

    for (int i = 0; i < n; ++i) {
        outer [9*i] = 0.000f;
        outer [9*i + 1] = 0.000f;
        outer [9*i + 2] = 0.000f;
        outer [9*i + 3] = c * cos ((m * pi * (i+1)) / 180);
        outer [9*i + 4] = c * sin ((m * pi * (i+1)) / 180);
        outer [9*i + 5] = 0.000f;
        outer [9*i + 6] = c * cos ((m * pi * (i)) / 180);
        outer [9*i + 7] = c * sin ((m * pi * (i)) / 180);
        outer [9*i + 8] = 0.000f;
    }
    for (int i = 0; i < n; ++i) {
        inner [9*i] = 0.000f;
        inner [9*i + 1] = 0.000f;
        inner [9*i + 2] = 0.000f;
        inner [9*i + 3] = c2 * cos ((m * pi * (i+1)) / 180);
        inner [9*i + 4] = c2 * sin ((m * pi * (i+1)) / 180);
        inner [9*i + 5] = 0.000f;
        inner [9*i + 6] = c2 * cos ((m * pi * (i)) / 180);
        inner [9*i + 7] = c2 * sin ((m * pi * (i)) / 180);
        inner [9*i + 8] = 0.000f;
    }

    this->body = create3DObject(GL_TRIANGLES, 6, body, color, GL_FILL);
    this->neck = create3DObject(GL_TRIANGLES, 6, neck, color, GL_FILL);
    this->legs = create3DObject(GL_TRIANGLES, 6, legs, color, GL_FILL);
    this->face = create3DObject(GL_TRIANGLES, 6, face, color, GL_FILL);
    this->hair = create3DObject(GL_TRIANGLES, 6, hair, COLOR_YELLOW, GL_FILL);
    this->jetpack = create3DObject(GL_TRIANGLES, 12, jetpack, COLOR_BLACK, GL_FILL);

    this->shield1 = create3DObject(GL_TRIANGLES, n*3, outer, COLOR_BLACK, GL_FILL);
    this->shield2 = create3DObject(GL_TRIANGLES, n*3, inner, COLOR_BACKGROUND, GL_FILL);
}

void Jetpack :: draw (glm::mat4 VP) {
    printf("%f %f\n", this->isShield, this->shieldTimer);
    if (this->shieldTimer < 0) {
        this->isShield = false;
        this->shieldTimer = 0;
    }
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

    if (this->isShield) {
        draw3DObject(this->shield1);
        draw3DObject(this->shield2);
        this->shieldTimer--;
    }

	draw3DObject(this->body);
    draw3DObject(this->neck);
    draw3DObject(this->legs);
    draw3DObject(this->face);
    draw3DObject(this->hair);
    draw3DObject(this->jetpack);

}

void Jetpack :: set_position (float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Jetpack :: update () {
    this->bounding_box = { this->position.x, this->position.y, 0.8, 1.8 };
    if (this->isShield) {
        this->shield_bounding_box = { this->position.x, this->position.y, 1.3, 1.3};
    }

    if (this->return_position().y - this->downwardVelocity > 3.2) {
        this->set_position (this->position.x, 3.2);
        this->gravity = 0.01;
        this->downwardVelocity = 0;
    }

    if (this->bounding_box.y - this->downwardVelocity > -1.5) {
        this->downwardVelocity += this->gravity;
        this->set_position (this->position.x, this->position.y - this->downwardVelocity);
    }
    else if (this->bounding_box.y - this->downwardVelocity <= -1.5) {
        this->set_position (this->position.x, -1.5);
        this->gravity = 0.01;
        this->downwardVelocity = 0;
    }
}

void Jetpack :: move_left (float byHowMuch) {
    this->position.x -= byHowMuch;
}

void Jetpack :: set_rotation (float byHowMuch) {
    this->rotation = byHowMuch;
}


void Jetpack :: shield () {
    // this->shield_bounding_box = { this->position.x, this->position.y, 1.3, 1.3};
    if (this->isShield == true) {
        if (this->shieldTimer >= 0) {
            this->shieldTimer += 300;
        }
        else {
            this->isShield = false;
            this->shieldTimer = 0;
        }
    }
}

void Jetpack :: move_right (float byHowMuch) {
    this->position.x += byHowMuch;
}

void Jetpack :: jump_up (float byHowMuch) {
    this->downwardVelocity = byHowMuch;
}

void Jetpack :: jump_down (float byHowMuch) {
    this->downwardVelocity += byHowMuch;
    this->position.y += downwardVelocity;
}

glm::vec3 Jetpack :: return_position () {
    return this->position;
}

bounding_box_t Jetpack :: return_bounding_box () {
    return this->bounding_box;
}

bounding_box_t Jetpack :: return_shield_bounding_box () {
    return this->shield_bounding_box;
}