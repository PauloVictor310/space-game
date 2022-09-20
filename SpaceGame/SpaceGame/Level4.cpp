/**********************************************************************************
// Level4 (Arquivo de Cabeçalho)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nú“el 4 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Etther.h"
#include "Home.h"
#include "Level4.h"
#include "LevelWin.h"
#include "Player.h"
#include "Orb.h"
#include "Pivot.h"
#include "Cannon.h"
#include "Wall.h"
#include <string>
#include <fstream>
#include "Level3.h"
#include "LevelLose.h"
#include "LevelWin.h"
#include "Level1.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

Player* Level4::player = nullptr;

void Level4::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_4_completed.png");

    // cria jogador
    if (Engine::comingFrom == ELEVEL3) {
        if (Engine::currentY < 360) {
            player = new Player(870.0f, Engine::currentY, BLUE);
        }
        else {
            player = new Player(870.0f, Engine::currentY, RED);
        }
        
    }
    else {
        player = new Player(Engine::currentX, 690, RED);
    }
    
    player->currLevel = LEVEL4;
    scene->Add(player, MOVING);
    //left top cannon
    topCannon = new Cannon(-32, -30, 32, 30);
    topCannon->MoveTo(36, 255);
    scene->Add(topCannon, STATIC);
    //left bottom cannon
    bottomCannon = new Cannon(-26, -29, 26, 29);
    bottomCannon->MoveTo(26, 513);
    scene->Add(bottomCannon, STATIC);

    Wall* wall;
    wall = new Wall(0, 0, 10, 216);
    wall->color = RED;
    wall->MoveTo(162.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 216);
    wall->color = RED;
    wall->MoveTo(782.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 610, 6);
    wall->color = RED;
    wall->MoveTo(172.0f, window->CenterY() - 141.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 13, 360);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() + 470.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 450, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() - 3.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 478, 8);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() - 8.0f, window->CenterY() - 3.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 347);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() - 23.0f, window->CenterY() + 6.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 13, 360);
    wall->color = RED;
    wall->MoveTo(window->CenterX() + 470.0f, window->CenterY());
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 948, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() + 352.0f);
    scene->Add(wall, STATIC);

    // cria orb
    Orb* orb = new Orb(RED);
    orb->MoveTo(160, 598);
    scene->Add(orb, STATIC);

    // cria orb de vitoria
    Orb* orbWin = new Orb(YELLOW);
    orbWin->MoveTo(315, 52);
    scene->Add(orbWin, STATIC);

}

// ------------------------------------------------------------------------------

void Level4::Finalize()
{
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void Level4::Update()
{

    if ((clock() - start) % 62 == 0 && hasMissile) {
        Bullet* bl1 = new Bullet(200, 300);
        bl1->MoveTo(topCannon->X(), topCannon->Y(), Layer::UPPER);
        scene->Add(bl1, STATIC);

        Bullet* bl2 = new Bullet(200, 200);
        bl2->MoveTo(topCannon->X() + 40, topCannon->Y() + 7, Layer::UPPER);
        scene->Add(bl2, STATIC);

        Bullet* br1 = new Bullet(200, 300);
        br1->MoveTo(bottomCannon->X(), bottomCannon->Y() - 14, Layer::UPPER);
        scene->Add(br1, STATIC);

        Bullet* br2 = new Bullet(250, 400);
        br2->MoveTo(bottomCannon->X() - 10, bottomCannon->Y() + 7, Layer::UPPER);
        scene->Add(br2, STATIC);
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

    if (window->KeyDown(VK_ESCAPE))
    {
        // volta para a tela de abertura
        Engine::Next<Home>();
    }
    else if (window->KeyDown('V'))
    {
        // passa manualmente para o próximo nú“el
        Engine::Next<LevelWin>();
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

    // Player Perdeu
    if (player->nextLevel == LEVELWIN) {
        Engine::comingFrom = ELEVEL4;
        Engine::Next<LevelWin>();
    }
        

    // Muda para o nú“el 1
    if (player->nextLevel == LEVEL1) {
        Engine::currentX = player->X();
        Engine::currentY = player->Y();
        Engine::comingFrom = ELEVEL4;
        Engine::Next<Level1>();
    }
        

    // Muda para o nú“el 3
    if (player->nextLevel == LEVEL3) {
        Engine::currentX = player->X();
        Engine::currentY = player->Y();
        Engine::comingFrom = ELEVEL4;
        Engine::Next<Level3>();
    }
}

// ------------------------------------------------------------------------------

void Level4::Draw()
{
    // desenha cena
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------