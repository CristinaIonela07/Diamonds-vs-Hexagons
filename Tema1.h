#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;

        void Disparition(Mesh* object, float x_pos, float y_pos, float x_scale, float y_scale);
        void Initialize_enemies();
        void Verif(int poz);
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;


    protected:
        float size;

        glm::mat3 modelMatrix;
        
        float angularStep[9][3];

        bool still_on_screen[3];
        glm::vec2 stars[3]; 

        int nr_points; 
        int points[4];

        bool hex_appearance[10];
        glm::vec2 actual_pos[10]; 
        bool good[10];     
        std::vector<glm::vec2> enemy_positions;
        std::vector<Mesh*> enemies;   
        int a[10], b[10];            \
        bool disparition[10];                  
        float translateX[10];                  
        float scaleX[10], scaleY[10];          

        int count_lives;          

        bool is_pressed;     
        int index_gun;            
        float gun_moveX, gun_moveY;  
        glm::vec2 bullet_pos[9][3];

        std::vector<Mesh*> guns;  
        std::vector<glm::vec3> green_squares_positions;   
        std::vector<glm::vec3> borders_positions;          
        std::vector<glm::vec3> guns_positions;             
        glm::vec2 scale_gun[9];                            
        int green_matrix[9];                          
        
        int enemy_lines[3][4];
        int gun_lines[9][4];

        glm::vector<Mesh*> bullets;

        float time[9][4];
        int shoots[10];

        float strs[9][3];
    };
}   // namespace m1
