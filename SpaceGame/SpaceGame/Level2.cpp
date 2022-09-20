/**********************************************************************************
// Level2 (Código Fonte) 
// 
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nú“el 2 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Etther.h"
#include "Home.h"
#include "Level2.h"
#include "Level3.h"
#include "LevelLose.h"
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"
#include "Cannon.h"
#include "Wall.h"
#include <string>
#include <fstream>
#include "Level1.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

Player* Level2::player = nullptr;

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_2_completed.png");

    // cria jogador
    if (Engine::comingFrom == ELEVEL1) {
        if (Engine::currentY > 360) {
            player = new Player(60.0f, Engine::currentY, RED);
        }
        else {
            player = new Player(60.0f, Engine::currentY, BLUE);
            
        }
        
    }
    else {
        player = new Player(Engine::currentX, 30, RED);
    }
    
    player->currLevel = LEVEL2;
    scene->Add(player, MOVING);
    //temporario
    //player->currColor = RED;

    //Cria e posiciona bbox dos canhões
    bottomLeftCannon = new Cannon(-31, -28, 31, 28);
    bottomLeftCannon->MoveTo(350, 692);
    scene->Add(bottomLeftCannon, STATIC);
    //top right cannon
    bottomRightCannon = new Cannon(-31, -21, 31, 21);
    bottomRightCannon->MoveTo(929, 295);
    scene->Add(bottomRightCannon, STATIC);
    //bottom right cannon
    topRightCannon = new Cannon(-31, -28, 31, 28);
    topRightCannon->MoveTo(928, 537);
    scene->Add(topRightCannon, STATIC);
    
    // -----------------------------------------
    // posição das paredes

    Wall* wall;
    wall = new Wall(0, 0, 960, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 374);
    wall->color = BLUE;
    wall->MoveTo(0.0f, 8.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 374);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() + 9.0f, 8.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 960, 10);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() + 22.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 328);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() + 32.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 328);
    wall->color = RED;
    wall->MoveTo(window->CenterX() + 9.0f, window->CenterY() + 32.0f);
    scene->Add(wall, STATIC);

    // cria orb
    Orb* orb = new Orb(RED);
    orb->MoveTo(160, 271);
    scene->Add(orb, STATIC);
    
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void Level2::Update()
{
    if ((clock() - start) % 89 == 0 && hasMissile) {
        Bullet* bl1 = new Bullet(-300, -300);
        bl1->MoveTo(bottomLeftCannon->X() - 20, bottomLeftCannon->Y(), Layer::UPPER);
        scene->Add(bl1, STATIC);

        Bullet* bl2 = new Bullet(-200, -480);
        bl2->MoveTo(bottomLeftCannon->X() + 14, bottomLeftCannon->Y() + 7, Layer::UPPER);
        scene->Add(bl2, STATIC);

        Bullet* tr1 = new Bullet(-200, -100);
        tr1->MoveTo(topRightCannon->X(), topRightCannon->Y() + 12, Layer::UPPER);
        scene->Add(tr1, STATIC);

        Bullet* tr2 = new Bullet(-250, -220);
        tr2->MoveTo(topRightCannon->X(), topRightCannon->Y() - 15, Layer::UPPER);
        scene->Add(tr2, STATIC);

    }

    if ((clock() - start) % 70 == 0 && hasMissile) {

        Bullet* br1 = new Bullet(-200, 0);
        br1->MoveTo(bottomRightCannon->X() + 10, bottomRightCannon->Y() + 7, Layer::UPPER);
        scene->Add(br1, STATIC);

        Bullet* br2 = new Bullet(-200, 0);
        br2->MoveTo(bottomRightCannon->X() - 10, bottomRightCannon->Y() - 7, Layer::UPPER);
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
    else if (window->KeyDown('M'))
    {
        // passa manualmente para o próximo nú“el
        Engine::currentX = 680;
        Engine::currentY = 690;
        Engine::comingFrom = ELEVEL2;
        Engine::Next<Level3>();
    }
    else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
    }

    // Player Perdeu
    if (player->nextLevel == LEVELOSE)
        Engine::Next<LevelLose>();

    // Muda para o nú“el 1
    if (player->nextLevel == LEVEL1) {
        Engine::currentX = player->X();
        Engine::currentY = player->Y();
        Engine::comingFrom = ELEVEL2;
        Engine::Next<Level1>();
    }
        

    // Muda para o nú“el 3
    if (player->nextLevel == LEVEL3) {
        Engine::currentX = player->X();
        Engine::currentY = player->Y();
        Engine::comingFrom = ELEVEL2;
        Engine::Next<Level3>();
    }
        
}


// ------------------------------------------------------------------------------

void Level2::Draw()
{
    // desenha cena
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------