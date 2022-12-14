/**********************************************************************************
// Level1 (C?digo Fonte) 
// 
// Cria??o:     18 Jan 2013
// Atualiza??o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri??o:   N??el 1 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Etther.h"
#include "Home.h"
#include "Level1.h"
#include "Level2.h"
#include "Player.h"
#include "Pivot.h"
#include "Cannon.h"
#include "Wall.h"
#include "Bullet.h"
#include <string>
#include <fstream>
#include "Level4.h"
#include "LevelLose.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

Scene* Level1::scene = nullptr;
Player* Level1::player = nullptr;

void Level1::Init()
{
    // cria cena do jogo
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_1_completed.png");

    // cria jogador
    if (Engine::comingFrom == ELEVEL2) {
        if (Engine::currentY > 360) {
            player = new Player(900, Engine::currentY, RED);
        }
        else {
            player = new Player(900, Engine::currentY, BLUE);
        }
        
    }
    else if (Engine::comingFrom == ELEVEL4) {
        player = new Player(Engine::currentX, 30, RED);
    }
    else {
        player = new Player(480, 450, BLUE);
    }
    
    player->currLevel = LEVEL1;
    scene->Add(player, MOVING);

    //Cria e posiciona bbox dos canh?es
    //left cannon
    leftCannon = new Cannon(-35, -34, 35, 34);
    leftCannon->MoveTo(34, 34);
    scene->Add(leftCannon, STATIC);
    //right cannon
    rightCannon = new Cannon(-36, -31, 36, 31);
    rightCannon->MoveTo(914, 436);
    scene->Add(rightCannon, STATIC);

    // -----------------------------------------
    // posi??o das paredes

    Wall* wall;
    wall = new Wall(0, 0, 960, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 355);
    wall->color = RED;
    wall->MoveTo(window->CenterX() - 23.0f, 8.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 13, 374);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() + 470.0f, 8.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 960, 10);
    wall->color = BLUE;
    wall->MoveTo(0.0f, window->CenterY() + 22.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 13, 328);
    wall->color = RED;
    wall->MoveTo(window->CenterX() + 470.0f, window->CenterY() + 32.0f);
    scene->Add(wall, STATIC);

    

}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void Level1::Update()
{
    
    if ((clock() - start) % 53 == 0 && hasMissile) {
        Bullet* bl1 = new Bullet(200, 300);
        bl1->MoveTo(leftCannon->X(), leftCannon->Y(), Layer::UPPER);
        scene->Add(bl1, STATIC);

        Bullet* bl2 = new Bullet(200, 200);
        bl2->MoveTo(leftCannon->X() + 40, leftCannon->Y() + 7, Layer::UPPER);
        scene->Add(bl2, STATIC);

        Bullet* br1 = new Bullet(-200, -300);
        br1->MoveTo(rightCannon->X(), rightCannon->Y(), Layer::UPPER);
        scene->Add(br1, STATIC);

        Bullet* br2 = new Bullet(-250, -100);
        br2->MoveTo(rightCannon->X() - 40, rightCannon->Y() - 7, Layer::UPPER);
        scene->Add(br2, STATIC);
    }
    // habilita/desabilita bounding box
    if (ctrlKeyB && window->KeyDown('B'))
    {
        viewBBox = !viewBBox;
        ctrlKeyB = false;
    }
    else if (window->KeyUp('B'))
    {
        ctrlKeyB = true;
    }

    if (ctrlKeyE && window->KeyDown('E'))
    {
        hasMissile = !hasMissile;
        ctrlKeyE = false;
    }
    else if (window->KeyUp('E'))
    {
        ctrlKeyE = true;
    }
    
    if (window->KeyDown(VK_ESCAPE))
    {
        // volta para a tela de abertura
        Engine::Next<Home>();
    }
    else if (window->KeyDown('N'))
    {
        // passa manualmente para o pr?ximo n??el
        Engine::currentX = 60;
        Engine::currentY = 200;
        Engine::comingFrom = ELEVEL1;
        Engine::Next<Level2>();
    }
    else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
    }

    // Muda para o n??el 2
    if (player->nextLevel == LEVEL2) {
        Engine::currentX = player->X();
        Engine::currentY = player->Y();
        Engine::comingFrom = ELEVEL1;
        Engine::Next<Level2>();
    }
        

    // Muda para o n??el 2
    if (player->nextLevel == LEVELOSE)
        Engine::Next<LevelLose>();

    // Muda para o n??el 4
    if (player->nextLevel == LEVEL4) {
        Engine::currentX = player->X();
        Engine::currentY = player->Y();
        Engine::comingFrom = ELEVEL1;
        Engine::Next<Level4>();
    }
        
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    // desenha cena
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------