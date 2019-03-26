#include "main.h"
#include "timer.h"
#include "floorBlock.h"
#include "jetpack.h"
#include "coin.h"
#include "enemy1.h"
#include "enemy2.h"
#include "enemy3.h"
#include "square.h"
#include "bullets.h"
#include "jetpack_fire.h"
#include "magnet.h"
#include "powerup.h"
#include "semi_circle.h"
#include "dragon.h"
#include "ice_bullets.h"
#include "seven_segment_display.h"
#include <stdio.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

const int numberOfCoins = 100;
const int numberOfBricks = 400;
const int numberOfEnemies1 = 20;
const int numberOfEnemies2 = 5;
const int numberOfEnemies3 = 5;
const int numberOfDisplays = 6;
const int numberOfMagnets = 6;
const int numberOfPowerups = 20;
const int numberOfSemiCricles = 1;

int dragon_bullet_count = 0;

int score = 0;
int health = 100;

Jetpack jetpack;

Dragon dragon;

std::vector<Seven_Segment_Display> displays;

// Seven_Segment_Display level;

std::vector<FloorBlock> bottom_brick1;
std::vector<FloorBlock> top_brick1;
std::vector<FloorBlock> bottom_brick2;
std::vector<FloorBlock> top_brick2;

std::vector<Coin> coin;

std::vector<Magnet> magnets;

std::vector<Powerup> powerups;

std::vector<Water_Balloon> water_balloons;
std::vector<Ice_Bullets> ice_bullets;

std::vector<Jetpack_Fire> jetpack_fires;

std::vector<Enemy1> enemies_1;
std::vector<Enemy2> enemies_2;
std::vector<Enemy3> enemies_3;

std::vector<Square> squares;

std::vector<Semi_Circle> semi_circles;

float screen_zoom = 1, screen_center_x = 1, screen_center_y = 1;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

// Eye - Location of camera.
glm::vec3 eye ( 0, 0, 1 );

// Target - Where is the camera looking at.
glm::vec3 target (0, 0, 0);

void draw() {

    dragon_bullet_count++;

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for (int i = 0; i < semi_circles.size(); ++i) {
        semi_circles[i].draw (VP);
    }

    jetpack.draw (VP);

    if (dragon.health > 0)
        dragon.draw (VP);

    for (int i = 0; i < numberOfBricks; ++i) {
        if (bottom_brick1[i].return_position().x >= (eye.x - 5.0) && bottom_brick1[i].return_position().x <= (eye.x + 5.0)) {
            bottom_brick1[i].draw (VP);
        }
        if (top_brick1[i].return_position().x >= (eye.x - 5.0) && top_brick1[i].return_position().x <= (eye.x + 5.0)){
            top_brick1[i].draw (VP);
        }
        if (bottom_brick2[i].return_position().x >= (eye.x - 5.0) && bottom_brick2[i].return_position().x <= (eye.x + 5.0)) {
            bottom_brick2[i].draw (VP);
        }
        if (top_brick2[i].return_position().x >= (eye.x - 5.0) && top_brick2[i].return_position().x <= (eye.x + 5.0)) {
            top_brick2[i].draw (VP);
        }
    }
    for (int i = 0; i < coin.size(); ++i) {
        if (coin[i].return_position().x >= (eye.x - 5.0) && coin[i].return_position().x <= (eye.x + 5.0)) {
            coin[i].draw(VP);
        }
    }
    for (int i = 0; i < enemies_1.size(); ++i) {
        enemies_1[i].draw (VP);
    }
    for (int i = 0; i < enemies_2.size(); ++i) {
        enemies_2[i].draw (VP);
    }
    for (int i = 0; i < enemies_3.size(); ++i) {
        enemies_3[i].draw (VP);
    }
    for (int i = 0; i < jetpack_fires.size(); ++i) {
        jetpack_fires[i].draw (VP);
    }
    for (int i = 0; i < squares.size(); ++i) {
        squares[i].draw (VP);
    }
    for (int i = 0; i < water_balloons.size(); ++i) {
        water_balloons[i].draw (VP);
    }
    for (int i = 0; i < magnets.size(); ++i) {
        magnets[i].draw (VP);
    }
    for (int i = 0; i < powerups.size(); ++i) {
        powerups[i].draw (VP);
    }
    for (int i = 0; i < ice_bullets.size(); ++i) {
        ice_bullets[i].draw (VP);
    }

    if (score >= 0) {
        displays[0].set_number((score % 1000) / 100);
        displays[0].draw (VP);
        displays[1].set_number((score % 100) / 10);
        displays[1].draw (VP);
        displays[2].set_number((score % 10));
        displays[2].draw (VP);
    }

    if (health >= 0) {
        displays[3].set_number((health % 1000) / 100);
        displays[3].draw (VP);
        displays[4].set_number((health % 100) / 10);
        displays[4].draw (VP);
        displays[5].set_number((health % 10));
        displays[5].draw (VP);
    }

}


void tick_input(GLFWwindow *window) {

    int left  = glfwGetKey (window, GLFW_KEY_LEFT);
    int a  = glfwGetKey (window, GLFW_KEY_A);
    int right = glfwGetKey (window, GLFW_KEY_RIGHT);
    int d = glfwGetKey (window, GLFW_KEY_D);
    int up = glfwGetKey (window, GLFW_KEY_UP);
    int w = glfwGetKey (window, GLFW_KEY_W);
    int s = glfwGetKey (window, GLFW_KEY_S);
    int down = glfwGetKey (window, GLFW_KEY_DOWN);
    int space = glfwGetKey (window, GLFW_KEY_SPACE);

    glfwSetScrollCallback(window, scroll_callback);

    if ((left || a) && jetpack.isInRing == false) {
        if (jetpack.return_position().x > (eye.x-2.5)) {
            jetpack.move_left (0.1);
        }
        jetpack.set_rotation(180);
    }

    if ((right || d) && jetpack.isInRing == false) {
        jetpack.move_right (0.1);
        jetpack.set_rotation(0);
    }
    if ((up || w) && jetpack.isInRing == false) {
        jetpack.jump_up (-0.1);
        Jetpack_Fire temp_jetpack_fire = Jetpack_Fire (jetpack.return_bounding_box().x-0.5, jetpack.return_bounding_box().y-0.4);
        jetpack_fires.push_back (temp_jetpack_fire);
    }

    if (space) {
        water_balloons.push_back (Water_Balloon(jetpack.return_position().x+0.35, jetpack.return_position().y+0.6));
    }

    if (jetpack.return_position().x >= (eye.x+1)) {
        target.x += 0.1;
        eye.x += 0.1;
        for (int i = 0; i < numberOfDisplays; ++i) {
            displays[i].update();
        }
        // level.update();
    }

    if (down || s && jetpack.return_position().y <= 2 && jetpack.isInRing == false) {
        if (jetpack.return_position().y > 0.5) {
            jetpack.set_position(jetpack.return_position().x, jetpack.return_position().y - 0.5);
        }
    }
}

void tick_elements() {

    // printf("dragon health - %f\n", dragon.health);

    jetpack.update();

    if (dragon.return_position().x <= eye.x + 5) {
        dragon.set_position (eye.x + 3, dragon.return_position().y);
    }

    if (dragon.return_position().x >= (eye.x - 5.0) && dragon.return_position().x <= (eye.x + 5.0)) {
        dragon.update ();
    }

    // Fire from the jetpack
    for (int i = 0; i < jetpack_fires.size(); ++i) {
        jetpack_fires[i].update ();
    }

    // Jetpack and the Semi Circle
    for (int i = 0; i < numberOfSemiCricles; ++i) {
        if (jetpack.return_position().x >= semi_circles[i].return_position().x-1.3 && jetpack.return_position().x <= semi_circles[i].return_position().x+1.3) {
            if (jetpack.return_position().y >= semi_circles[i].return_position().y+0.2 && jetpack.return_position().y <= semi_circles[i].return_position().y+1.3) {
                jetpack.isInRing = true;
                jetpack.RingNumber = i;
                break;
            }
        }
    }

    // Jetpack inside the semi circle
    if (jetpack.isInRing) {
        jetpack.set_position (jetpack.return_position().x + 0.06, semi_circles[jetpack.RingNumber].position.y + sqrt(pow (1.3, 2) - pow (jetpack.position.x - semi_circles[jetpack.RingNumber].position.x, 2)));
        eye.x += 0.06;
        target.x += 0.06;
        for (int i = 0; i < numberOfDisplays; ++i) {
            displays[i].position.x += 0.06;
        }
        // level.position.x += 0.06;
        if (jetpack.return_position().x >= semi_circles[jetpack.RingNumber].return_position().x+1.3) {
            jetpack.isInRing = false;
            jetpack.RingNumber = -1;
        }
    }

    // Making Ice Bullets for Dragon
    if (!jetpack.isInRing && dragon.health > 0) {
        if (dragon_bullet_count % (3*30) == 0) {
            // printf("making ice bullet\n");
            ice_bullets.push_back (Ice_Bullets(dragon.return_position().x-0.5, dragon.return_position().y));
            dragon_bullet_count = 0;
        }
    }

    // Check for collision with Ice Bullets
    for (int i = 0; i < ice_bullets.size(); ++i) {
        if (!jetpack.isInRing && ice_bullets[i].return_position().x >= (eye.x - 5.0) && ice_bullets[i].return_position().x <= (eye.x + 5.0)) {
            ice_bullets[i].update ();
            if (jetpack.isShield == true) {
                if (detect_collision(jetpack.return_shield_bounding_box(), ice_bullets[i].return_bounding_box())) {
                    ice_bullets.erase(ice_bullets.begin() + i);
                }
            }
            if (detect_collision(ice_bullets[i].return_bounding_box(), jetpack.return_bounding_box())) {
                ice_bullets.erase(ice_bullets.begin() + i);
                health -= 3;
            }
            for (int j = 0; j < water_balloons.size(); ++j) {
                if (detect_collision(ice_bullets[i].return_bounding_box(), water_balloons[j].return_bounding_box())) {
                    ice_bullets.erase(ice_bullets.begin() + i);
                    water_balloons.erase(water_balloons.begin() + j);
                    score += 2;
                }
            }
        }
    }

    // Check for collisions with Dragon
    if (jetpack.isShield == true) {
        if (detect_collision(jetpack.return_shield_bounding_box(), dragon.return_bounding_box())) {

        }
    }
    else if (detect_collision(dragon.return_bounding_box(), jetpack.return_bounding_box())) {
        score -= 2;
        health -= 5;
    }
    for (int j = 0; j < water_balloons.size(); ++j) {
        if (detect_collision(dragon.return_bounding_box(), water_balloons[j].return_bounding_box())) {
            water_balloons.erase(water_balloons.begin() + j);
            score += 2;
            if (dragon.health > 3)
                dragon.health -= 5;
        }
    }

    // Check for collision with Coin
    for (int i = 0; i < coin.size(); ++i) {
        if (coin[i].return_position().x >= (eye.x - 5.0) && coin[i].return_position().x <= (eye.x + 5.0)) {
            coin[i].update();
            if (detect_collision(coin[i].return_bounding_box(), jetpack.return_bounding_box())) {
                if (coin[i].type == 1) {
                    score++;
                }
                else if (coin[i].type == 2) {
                    score += 3;
                }
                else {
                    score += 5;
                }
                coin.erase(coin.begin() + i);
            }
        }
    }

    // Check for collision with Enemy1
    for (int i = 0; i < enemies_1.size(); ++i) {
        if (!jetpack.isInRing && enemies_1[i].return_position().x >= (eye.x - 5.0) && enemies_1[i].return_position().x <= (eye.x + 5.0)) {
            enemies_1[i].update ();
            if (jetpack.isShield == true) {
                if (detect_collision(jetpack.return_shield_bounding_box(), enemies_1[i].return_bounding_box())) {
                    enemies_1.erase(enemies_1.begin() + i);
                }
            }
            else if (detect_collision(enemies_1[i].return_bounding_box(), jetpack.return_bounding_box())) {
                enemies_1.erase(enemies_1.begin() + i);
                // printf("collision\n");
                score -= 2;
                health -= 5;
            }
            for (int j = 0; j < water_balloons.size(); ++j) {
                if (detect_collision(enemies_1[i].return_bounding_box(), water_balloons[j].return_bounding_box())) {
                    enemies_1.erase(enemies_1.begin() + i);
                    water_balloons.erase(water_balloons.begin() + j);
                    score += 2;
                }
            }
        }
    }

    // Magnet 
    for (int i = 0; i < magnets.size(); ++i) {
        if (!jetpack.isInRing && magnets[i].return_position().x >= (eye.x - 5.0) && magnets[i].return_position().x <= (eye.x + 5.0)) {
            magnets[i].update ();
            if (jetpack.isShield == true) {
                if (detect_collision(jetpack.return_shield_bounding_box(), magnets[i].return_magnetic_area_bounding_box())) {
                    
                }
            }
            else if (detect_collision(magnets[i].return_magnetic_area_bounding_box(), jetpack.return_bounding_box())) {
                jetpack.jump_up (-0.2);                
                if (!glfwGetKey (window, GLFW_KEY_S)) {
                    if (detect_collision(magnets[i].return_actual_bounding_box(), jetpack.return_bounding_box())) {
                        jetpack.set_position (jetpack.return_position().x, magnets[i].return_position().y-1);
                    }
                }
                else {
                    jetpack.jump_down(-0.1);
                }
            }
        }
    }

    // Collision with moving fire lines
    for (int i = 0; i < enemies_2.size(); ++i) {
        enemies_2[i].update ();
        if (!jetpack.isInRing && enemies_2[i].return_position().x >= (eye.x - 5.0) && enemies_2[i].return_position().x <= (eye.x + 5.0)) {
            // enemies_2[i].update ();
            if (jetpack.isShield == true) {
                if (detect_collision(jetpack.return_shield_bounding_box(), enemies_2[i].return_bounding_box())) {
                    enemies_2.erase(enemies_2.begin() + i);
                }
            }
            else if (enemies_2[i].is_visible() && detect_collision(enemies_2[i].return_bounding_box(), jetpack.return_bounding_box())) {
                enemies_2.erase(enemies_2.begin() + i);
                health -= 10;
            }
            for (int j = 0; j < water_balloons.size(); ++j) {
                if (detect_collision(enemies_2[i].return_bounding_box(), water_balloons[j].return_bounding_box())) {
                    enemies_2.erase(enemies_2.begin() + i);
                    water_balloons.erase(water_balloons.begin() + j);
                    score += 5;
                }
            }
        }
    }

    // Collision with Boomerang
    for (int i = 0; i < enemies_3.size(); ++i) {
        if (!jetpack.isInRing) {
            if (enemies_3[i].return_position().y < 1 || enemies_3[i].return_position().x < eye.x) {
                enemies_3[i].update ();
            }
            else if (enemies_3[i].return_position().x >= (eye.x - 5.0) && enemies_3[i].return_position().x <= (eye.x + 5.0)) {
                enemies_3[i].update ();
            }
            if (enemies_3[i].return_position().x >= (eye.x - 5.0) && enemies_3[i].return_position().x <= (eye.x + 5.0)) {
                if (jetpack.isShield == true) {
                    if (detect_collision(jetpack.return_shield_bounding_box(), enemies_3[i].return_bounding_box())) {
                        enemies_3.erase(enemies_3.begin() + i);
                    }
                }
                else if (enemies_3[i].is_visible() && detect_collision(enemies_3[i].return_bounding_box(), jetpack.return_bounding_box())) {
                    enemies_3.erase(enemies_3.begin() + i);
                    score -= 3;
                    health -= 15;
                }
            }
            for (int j = 0; j < water_balloons.size(); ++j) {
                if (detect_collision(enemies_3[i].return_bounding_box(), water_balloons[j].return_bounding_box())) {
                    enemies_3.erase(enemies_3.begin() + i);
                    water_balloons.erase(water_balloons.begin() + j);
                    score += 10;
                }
            }
        }
    }

    // Ice Balls
    for (int i = 0; i < ice_bullets.size(); ++i) {
        ice_bullets[i].update ();
        if (ice_bullets[i].return_position().x >= (eye.x - 5.0) && ice_bullets[i].return_position().x <= (eye.x + 5.0)) {

        }
        else {
            ice_bullets.erase(ice_bullets.begin() + i);
        }
    }

    // Squares
    for (int i = 0; i < squares.size(); ++i) {
        squares[i].update ();
        if (squares[i].return_position().x >= (eye.x - 5.0)) {

        }
        else {
            squares.erase(squares.begin() + i);
        }
    }

    // Powerups
    for (int i = 0; i < powerups.size(); ++i) {
        if (powerups[i].return_position().x >= (eye.x - 5.0) && powerups[i].return_position().x <= (eye.x + 5.0)) {
            powerups[i].update ();
            if (detect_collision(powerups[i].return_bounding_box(), jetpack.return_bounding_box())) {
                if (powerups[i].type == 1) {
                    score += 20;
                }
                else if (powerups[i].type == 2) {
                    health = 100;
                }
                else if (powerups[i].type == 3) {
                    jetpack.isShield = true;
                    jetpack.shield();
                }
                powerups.erase(powerups.begin() + i);
            }
        }
    }

    // Water Balloons / Bullets
    for (int i = 0; i < water_balloons.size(); ++i) {
        water_balloons[i].update ();
        if (water_balloons[i].return_position().x >= (eye.x - 5.0) && water_balloons[i].return_position().x <= (eye.x + 5.0)) {

        }
        else {
            water_balloons.erase(water_balloons.begin() + i);
        }

    }

    camera_rotation_angle += 5;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    jetpack     = Jetpack (-2, 0, COLOR_GREEN);

    dragon      = Dragon (30, 2);

    float gap = 0;

    // level = Seven_Segment_Display (0, 4.3, 1);

    for (int i = 0; i < 3; ++i) {
        // printf("gap->%d\n", gap);
        displays.push_back (Seven_Segment_Display (3+gap, 4.3, 0));
        gap += 0.4;
    }
    gap = -2.5;
    for (int i = 3; i < 6; ++i) {
        // printf("gap->%d\n", gap);
        displays.push_back (Seven_Segment_Display (gap, 4.3, 1));
        gap += 0.4;
    }

    gap = 0.2;
    
    for (int i = 0; i < numberOfBricks; ++i) {
        FloorBlock temp_floor_block[4];

        temp_floor_block[0] = FloorBlock (COLOR_RED);
        temp_floor_block[1] = FloorBlock (COLOR_RED);
        temp_floor_block[2] = FloorBlock (COLOR_RED);
        temp_floor_block[3] = FloorBlock (COLOR_RED);
        
        bottom_brick1.push_back (temp_floor_block[0]);
        top_brick1.push_back (temp_floor_block[1]);
        bottom_brick2.push_back (temp_floor_block[2]);
        top_brick2.push_back (temp_floor_block[3]);

        bottom_brick1[i].set_position (i + gap - 4, -2.53);
        top_brick1[i].set_position (i + gap - 4, +4.0);
        bottom_brick2[i].set_position (i + gap - 4.5, -3.03);
        top_brick2[i].set_position (i + gap - 4.5, +4.5);

        gap+=0.1;
    }
    for (int i = 0; i < numberOfCoins; ++i) {
        float y = ((rand()%10)+0.1 / (rand()%10));
        if (rand()%2 == 1) {
            y *= -1;
        }
        if (y < -2.5) {
            y = -2;
        }
        if (y > 3.5) {
            y = 3.5;
        }
        Coin tempCoin = Coin (rand()%100, y, rand()%6);
        coin.push_back(tempCoin);
    }
    int distance = 0;
    for (int i = 0; i < numberOfEnemies1; ++i) {
        Enemy1 temp_enemy_1 = Enemy1 (rand()%10 + distance, (rand()%10) % 3, rand()%30 );
        distance += 15;
        enemies_1.push_back (temp_enemy_1);
    }
    distance = 5;
    for (int i = 0; i < numberOfEnemies2; ++i) {
        int x = rand()%10 + distance;
        Enemy2 temp_enemy_2 = Enemy2 (x, 1);
        enemies_2.push_back (temp_enemy_2);
        squares.push_back (Square (x+2, 1));
        squares.push_back (Square (x-2, 1));
        distance += 15;
    }
    gap = 0;
    for (int i = 0; i < numberOfEnemies3; ++i) {
        Enemy3 temp_enemy_3 = Enemy3 (5+gap, 3.5);
        enemies_3.push_back (temp_enemy_3);
        gap += 10;
    }
    gap = 3;
    for (int i = 0; i < numberOfMagnets; ++i) {
        magnets.push_back (Magnet (rand()%10 + gap, 3));
        gap+=15;
    }
    gap = 0;
    for (int i = 0; i < numberOfPowerups; ++i) {
        powerups.push_back (Powerup (rand()%10+gap, 1, (rand()%3)+1));
        gap += 7;
    }

    for (int i = 0; i < numberOfSemiCricles; ++i) {
        semi_circles.push_back (Semi_Circle (2, 2));
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1200;
    int height = 1200;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers


        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            reset_screen();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    printf("your final score is -> %d\n", score);

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
