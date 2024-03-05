#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
#include <random>

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    size = 125;

    points[0] = 1;
    points[1] = 2;
    points[2] = 2;
    points[3] = 3;

    gun_moveX = 0;
    gun_moveY = 0;

    count_lives = 3;
    nr_points = 5;

    is_pressed = false;
    index_gun = 0;

    for (int i = 0; i < 10; i++) {
        hex_appearance[i] = false;
        disparition[i] = false;
        good[i] = false;
        a[i] = -1;
        b[i] = -1;
        translateX[i] = 0;
        scaleX[i] = 1;
        scaleY[i] = 1;
        shoots[i] = 0;
        actual_pos[i].x = -1;
        actual_pos[i].y = -1;
    }

    hex_appearance[0] = true;

    for (int i = 0; i < 9; i++) {
        scale_gun[i].x = 1;
        scale_gun[i].y = 1;
        green_matrix[i] = -10;

        for (int j = 0; j < 3; j++) {
            angularStep[i][j] = 0;
            strs[i][j] = -1;
        }

        for (int j = 0; j < 4; j++) {
            gun_lines[i][j] = 0;
            time[i][j] = 9;
        }
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
            enemy_lines[i][j] = 0;

    for (int i = 0; i < 3; i++) {
        still_on_screen[i] = false;
        stars[i].x = -1;
        stars[i].y = -1;
    }

    green_squares_positions = {
        glm::vec3(120, 350, 0),  glm::vec3(270, 350, 0), glm::vec3(420, 350, 0),
        glm::vec3(120, 200, 0),glm::vec3(270, 200, 0), glm::vec3(420, 200, 0),
        glm::vec3(120, 50, 0), glm::vec3(270, 50, 0), glm::vec3(420, 50, 0)
              
    };

    borders_positions = {
        glm::vec3(30, 580, 0),
        glm::vec3(220, 580, 0),
        glm::vec3(410, 580, 0),
        glm::vec3(600, 580, 0)
    };

    guns_positions = {
        glm::vec3(80, 580 + size/2, 0),
        glm::vec3(270, 580 + size / 2, 0),
        glm::vec3(460, 580 + size / 2, 0),
        glm::vec3(650, 580 + size / 2, 0)
    };

    enemy_positions = {
        glm::vec2(1300, 412.5),
        glm::vec2(1300, 262.5),
        glm::vec2(1300, 112.5)
    };


    // Patratele verzi
    Mesh* green_square = object2D::CreateSquare("green_square", corner, size, glm::vec3(0, 1, 0), true);
    AddMeshToList(green_square);

    //Patratele rosii (vietile)
    Mesh* red_square = object2D::CreateSquare("red_square", corner, 90, glm::vec3(1, 0, 0), true);
    AddMeshToList(red_square);

    // Chenare negre pentru tunuri
    Mesh* p1 = object2D::CreateSquare("p1", corner, size, glm::vec3(0, 0, 0));
    AddMeshToList(p1);

    // Linia de finish
    Mesh* r1 = object2D::CreateRectangle("r1", corner, 50, 425, glm::vec3(1, 0, 0), true);
    AddMeshToList(r1);

    // Tunurile
    Mesh* d1 = object2D::CreateDiamond("d1", corner, 50, 25, glm::vec3(1, 0.5, 0), true);
    guns.push_back(d1);

    Mesh* d2 = object2D::CreateDiamond("d2", corner, 50, 25, glm::vec3(0, 0, 1), true);
    guns.push_back(d2);

    Mesh* d3 = object2D::CreateDiamond("d3", corner, 50, 25, glm::vec3(1, 1, 0), true);
    guns.push_back(d3);

    Mesh* d4 = object2D::CreateDiamond("d4", corner, 50, 25, glm::vec3(0.5, 0.5, 1), true);
    guns.push_back(d4);

    // Hexagoanele inamice
    Mesh* h1 = object2D::CreateHexagon("h1", corner, 50, glm::vec3(1, 0.5, 0), true);
    enemies.push_back(h1);

    Mesh* h2 = object2D::CreateHexagon("h2", corner, 50, glm::vec3(0, 0, 1), true);
    enemies.push_back(h2);

    Mesh* h3 = object2D::CreateHexagon("h3", corner, 50, glm::vec3(1, 1, 0), true);
    enemies.push_back(h3);

    Mesh* h4 = object2D::CreateHexagon("h4", corner, 50, glm::vec3(0.5, 0.5, 1), true);
    enemies.push_back(h4);

    Mesh* h_int = object2D::CreateHexagon("h_int", corner, 20, glm::vec3(0, 0.8, 1), true);
    AddMeshToList(h_int);

    // Costul
    Mesh* little_star = object2D::CreateStar("little_star", corner, 12, glm::vec3(0.51, 0.48, 0.53), true);
    AddMeshToList(little_star);

    // Punctele adunate
    Mesh* points = object2D::CreateStar("points", corner, 30, glm::vec3(1, 0.48, 1), true);
    AddMeshToList(points);

    // Gloante pe culori
    Mesh* b1 = object2D::CreateStar("little_star", corner, 20, glm::vec3(1, 0.5, 0), true);
    bullets.push_back(b1);

    Mesh* b2 = object2D::CreateStar("little_star", corner, 20, glm::vec3(0, 0, 1), true);
    bullets.push_back(b2);

    Mesh* b3 = object2D::CreateStar("little_star", corner, 20, glm::vec3(1, 1, 0), true);
    bullets.push_back(b3);

    Mesh* b4 = object2D::CreateStar("little_star", corner, 20, glm::vec3(0.5, 0.5, 1), true);
    bullets.push_back(b4);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.35, 0.24, 0.17, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Initialize_enemies() {
    for (int i = 0; i < 10; i++) {
        hex_appearance[i] = false;
        disparition[i] = false;
        good[i] = false;
        a[i] = -1;
        b[i] = -1;
        translateX[i] = 0;
        scaleX[i] = 1;
        scaleY[i] = 1;
        actual_pos[i].x = -1;
        actual_pos[i].y = -1;
    }

    hex_appearance[0] = true;
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 3; j++) {
            angularStep[i][j] = 0;
            strs[i][j] = -1;
        }
    }

}

void Tema1::Disparition(Mesh* object, float x_pos, float y_pos, float x_scale, float y_scale) {
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(x_pos, y_pos);

    modelMatrix *= transform2D::Scale(x_scale, y_scale);
    RenderMesh2D(object, shaders["VertexColor"], modelMatrix);
}

void Tema1::Verif(int poz) {
    if (green_matrix[poz] != -10) {
        green_matrix[poz] = -2 * green_matrix[poz] - 1; 
        shoots[poz] = 0;

        for (int j = 0; j < 3; j++) {
            strs[poz][j] = -1;
            angularStep[poz][j] = 0;
        }

        for (int j = 0; j < 4; j++) {
            time[poz][j] = 9;
        }
    }
}

void Tema1::Update(float deltaTimeSeconds)
{
    for (int i = 0; i < nr_points; i++) {
        RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(810 + 40 * i, 580, 0));
    }

    for (int i = 0; i < count_lives; i++) {
        RenderMesh(meshes["red_square"], shaders["VertexColor"], glm::vec3(800 + i * 120, 600, 0));
    }

    // Hexagoanele inamice
    for (int i = 0; i < 10; i++) {
        if (hex_appearance[i] == true && disparition[i] == false) {
            a[i] = (int)(rand() % 4);
            b[i] = (int)(rand() % 3);
            hex_appearance[i] = false;
        }

        if (a[i] != -1 && disparition[i] == false) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(enemy_positions[b[i]].x, enemy_positions[b[i]].y);
            translateX[i] -= deltaTimeSeconds * 50;

            modelMatrix *= transform2D::Translate(translateX[i], 0);
            RenderMesh2D(meshes["h_int"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(enemies[a[i]], shaders["VertexColor"], modelMatrix);

            actual_pos[i].x = modelMatrix[2][0];
            actual_pos[i].y = modelMatrix[2][1];

            if (translateX[i] <= -150 && translateX[i] > -150 - 50 * deltaTimeSeconds) {
                enemy_lines[b[i]][a[i]]++;
            }

            if (translateX[i] < -150 && good[i] == false && rand() % 5 == 3 && rand() % 30 == 4) {
                hex_appearance[(i+1)%10] = true;
                good[i] = true;
                good[(i+1)%10] = false;
            }

            if (translateX[i] < -1250) {
                count_lives--;
                disparition[i] = true;
                enemy_lines[b[i]][a[i]]--;
            }
        }

        if (translateX[i] < -722 && translateX[i] > -722 - deltaTimeSeconds * 50) {
            int poz = b[i] * 3 + 2;
            Verif(poz);
        }
        if (translateX[i] < -877 && translateX[i] > -877 - deltaTimeSeconds * 50) {
            int poz = b[i] * 3 + 1;
            Verif(poz);
        }
        if (translateX[i] < -1027 && translateX[i] > -1027 - deltaTimeSeconds * 50) {
            int poz = b[i] * 3;
            Verif(poz);
        }

        if (disparition[i] == true && translateX[i] >= 150) {
            hex_appearance[(i + 1) % 10] = true;
            good[i] = true;
            good[(i + 1) % 10] = false;
        }
         if (disparition[i] == true) {
            scaleX[i] -= deltaTimeSeconds;
            scaleY[i] -= deltaTimeSeconds;

            if (scaleX[i] < 0 || scaleY[i] < 0) {
                scaleX[i] = 0;
                scaleY[i] = 0;
            }

            Disparition(meshes["h_int"], actual_pos[i].x, actual_pos[i].y, scaleX[i], scaleY[i]);
            Disparition(enemies[a[i]], actual_pos[i].x, actual_pos[i].y, scaleX[i], scaleY[i]);
            
            if (scaleX[i] == 0) {
                disparition[i] = false;
                translateX[i] = 0;
                scaleX[i] = 1;
                scaleY[i] = 1;
                a[i] = -1;
                actual_pos[i].x = -1;
                actual_pos[i].y = -1;
            }
         }
         for (int i = 0; i < 10; i++) {
             if (a[i] != -1 || disparition[i] == true)
                 break;
             else if (i == 9 && hex_appearance[9] == false && a[9] == -1 && disparition[9] == false) {
                 Initialize_enemies();
             }
         }
    }

    // Stelute = puncte
    if (rand() % 30 == 4) {
        if (still_on_screen[0] == false && still_on_screen[1] == false && still_on_screen[2] == false) {
            for (int i = 0; i < 3; i++) {
                still_on_screen[i] = true;
                stars[i].x = rand() % 700;
                stars[i].y = rand() % 700;
            }
        }
    }

    for (int i = 0; i < 3;i++)
        if (still_on_screen[i] == true)
            RenderMesh(meshes["points"], shaders["VertexColor"], glm::vec3(stars[i].x, stars[i].y, 0));
   
    if (is_pressed == true)
        RenderMesh(guns[index_gun], shaders["VertexColor"], glm::vec3(gun_moveX, gun_moveY, 0));

    for (int i = 0; i < 9; i++) {
        if (green_matrix[i] > -10 && green_matrix[i] < 0) {
            int index = -(green_matrix[i] + 1) / 2;
            gun_lines[i][index] = 0;

            scale_gun[i].x -= 10*deltaTimeSeconds;
            scale_gun[i].y -= 10*deltaTimeSeconds;
            if (scale_gun[i].x < 0 || scale_gun[i].y < 0) {
                scale_gun[i].x = 0;
                scale_gun[i].y = 0;
            }

            Disparition(guns[index], green_squares_positions[i].x + 50, green_squares_positions[i].y + size / 2, scale_gun[i].x, scale_gun[i].y);
           
            if (scale_gun[i].x == 0 || scale_gun[i].y == 0) {
                green_matrix[i] = -10;
                scale_gun[i].y = 1;
                scale_gun[i].x = 1;
                scale_gun[i].x = 1;
            }
        }
        if (green_matrix[i] >= 0) {
            RenderMesh(guns[green_matrix[i]], shaders["VertexColor"], glm::vec3(green_squares_positions[i].x + 50, green_squares_positions[i].y + size / 2, 0));
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 4; j++) {
            int k = -1;
            if (i < 3) 
                k = 0;
            else if (i < 6 && i >=3) 
                k = 1;
            else if (i < 9 && i >=6) 
                k = 2;

            if (gun_lines[i][j] > 0 && enemy_lines[k][j] > 0 ) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(green_squares_positions[i].x + 100, green_squares_positions[i].y + size / 2);

                time[i][0] -= deltaTimeSeconds;
                time[i][1] -= deltaTimeSeconds;
                time[i][2] -= deltaTimeSeconds;

                if (time[i][0] < 6) {
                    strs[i][0] = 0;
                    time[i][0] = 15;
                }

                if (time[i][1] < 3) {
                    strs[i][1] = 0;
                    time[i][1] = 12;
                }

                if (time[i][2] < 0) {
                    strs[i][2] = 0;
                    time[i][2] = 9;
                    time[i][1] = 9;
                    time[i][0] = 9;
                }

                for (int p = 0; p < 3; p++) {
                    if(strs[i][p] != -1)
                        strs[i][p] += 350 * deltaTimeSeconds;
                }
                
                for (int p = 0; p < 3; p++) {
                    if (strs[i][p] != -1) {
                        modelMatrix *= transform2D::Translate(strs[i][p], 0);
                        angularStep[i][p] += deltaTimeSeconds * 0.5;
                        modelMatrix *= transform2D::Rotate(50 * angularStep[i][p]);
                        RenderMesh2D(bullets[j], shaders["VertexColor"], modelMatrix);

                        bullet_pos[i][p].x = modelMatrix[2][0];
                        bullet_pos[i][p].y = modelMatrix[2][1];
                    }
                }

                for (int l = 0; l < 10; l++) {
                    if (a[l] == j) {
                        for (int p = 0; p < 3; p++) {
                            int c1 = bullet_pos[i][p].y - 5;
                            int c2 = actual_pos[l].x;

                            if (strs[i][p] != -1 && distance(glm::vec2(bullet_pos[i][p].x, c1), glm::vec2(actual_pos[l].x, actual_pos[l].y)) < (50 - 35)) {
                                strs[i][p] = -1;
                                angularStep[i][p] = 0;
                                shoots[l]++;

                                if (shoots[l] == 3) {
                                    disparition[l] = true;
                                    enemy_lines[k][j]--;
                                    shoots[l] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (count_lives == 0)
        window->Close();
}


void Tema1::FrameEnd()
{
    // Chenare negre pentru tunuri
    for (int i = 0; i < 4; i++)
        RenderMesh(meshes["p1"], shaders["VertexColor"], borders_positions[i]);
   

    // Linia de finish
    RenderMesh(meshes["r1"], shaders["VertexColor"], glm::vec3(20, 50, 0));

    // Tunurile
    for (int i = 0; i < 4; i++)
        RenderMesh(guns[i], shaders["VertexColor"], guns_positions[i]);

    // Patratele verzi (pe coloane)
    for (int i = 0; i < 9; i++) 
        RenderMesh(meshes["green_square"], shaders["VertexColor"], green_squares_positions[i]);


    // Cost tun1
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(50, 560, 0));

    // Cost tun 2
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(240, 560, 0));
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(280, 560, 0));

    // Cost tun3
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(430, 560, 0));
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(470, 560, 0));

    // Cost tun4
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(620, 560, 0));
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(660, 560, 0));
    RenderMesh(meshes["little_star"], shaders["VertexColor"], glm::vec3(700, 560, 0));
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (is_pressed == true) {
        gun_moveX += deltaX;
        gun_moveY -= deltaY;
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    mouseY = window->GetResolution().y - mouseY;
    for (int i = 0; i < 3; i++) {
        if (button == 1 && mouseX > stars[i].x - 45 && mouseX < stars[i].x + 45 && 
            mouseY > stars[i].y - 30 && mouseY < stars[i].y + 45 && still_on_screen[i] == true) {
            still_on_screen[i] = false;
            nr_points++;
        }
    }

    if (button == 1){ 
        for (int i = 0; i < 4; i++) {
            if (mouseX > borders_positions[i].x && mouseX < borders_positions[i].x + size && 
                mouseY > borders_positions[i].y && mouseY < borders_positions[i].y + size) {
                index_gun = i;
                is_pressed = true;
                gun_moveX = mouseX;
                gun_moveY = mouseY;
                break;
            }
        } 
    }

    if (button == 2) {
        for (int i = 0; i < 9; i++) {
            if (mouseX > green_squares_positions[i].x && mouseX < green_squares_positions[i].x + size && 
                mouseY > green_squares_positions[i].y && mouseY < green_squares_positions[i].y + size) {
                if (green_matrix[i] != -10)
                    green_matrix[i] = -2 * green_matrix[i] - 1; 
                
                for (int j = 0; j < 3; j++) {
                    strs[i][j] = -1;
                    angularStep[i][j] = 0;
                }

                for (int j = 0; j < 4; j++) {
                    time[i][j] = 9;
                }

                shoots[i] = 0;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    mouseY = window->GetResolution().y - mouseY;
    if (button == 1 && is_pressed == true) {
        is_pressed = false;
        for (int i = 0; i < 9; i++) {
            if (mouseX > green_squares_positions[i].x && mouseX < green_squares_positions[i].x + size && 
                mouseY > green_squares_positions[i].y && mouseY < green_squares_positions[i].y + size && green_matrix[i] == -10) {
                if (nr_points >= points[index_gun]) {
                    green_matrix[i] = index_gun;
                    nr_points = nr_points - points[index_gun];
                    gun_lines[i][index_gun] = 1;
                }
            }
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
