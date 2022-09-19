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
    player = new Player(870.0f, 100.0f, BLUE);
    player->currLevel = LEVEL4;
    scene->Add(player, MOVING);

    //Cria e posiciona bbox dos canhões
    Cannon* cannon;
    //left top cannon
    cannon = new Cannon(-32, -30, 32, 30);
    cannon->MoveTo(36, 255);
    scene->Add(cannon, STATIC);
    //left bottom cannon
    cannon = new Cannon(-26, -29, 26, 29);
    cannon->MoveTo(26, 513);
    scene->Add(cannon, STATIC);

    Wall* wall;
    wall = new Wall(0, 0, 10, 216);
    wall->color = RED;
    wall->MoveTo(162.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 216);
    wall->color = RED;
    wall->MoveTo(782.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 630, 8);
    wall->color = RED;
    wall->MoveTo(162.0f, window->CenterY() - 143.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 13, 360);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() + 470.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 462, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() - 3.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 487, 8);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() - 18.0f, window->CenterY() - 3.0f);
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
    if (player->nextLevel == LEVELWIN)
        Engine::Next<LevelWin>();

    // Muda para o nú“el 1
    if (player->nextLevel == LEVEL1)
        Engine::Next<Level1>();

    // Muda para o nú“el 3
    if (player->nextLevel == LEVEL3)
        Engine::Next<Level3>();
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