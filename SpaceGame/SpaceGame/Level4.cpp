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
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

void Level4::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_4_completed.png");

    // cria jogador
    Player* player = new Player();
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
    wall = new Wall(0, 0, 462, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() - 143.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(462, 100, 800, 110);
    wall->color = BLUE;
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