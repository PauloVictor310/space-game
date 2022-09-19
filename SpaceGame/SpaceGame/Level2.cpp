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
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"
#include "Cannon.h"
#include "Wall.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_2_completed.png");

    // cria jogador
    Player * player = new Player();
    scene->Add(player, MOVING);

    //Cria e posiciona bbox dos canhões
    Cannon* cannon;
    //bottom cannon
    cannon = new Cannon(-31, -28, 31, 28);
    cannon->MoveTo(350, 692);
    scene->Add(cannon, STATIC);
    //top right cannon
    cannon = new Cannon(-31, -21, 31, 21);
    cannon->MoveTo(929, 295);
    scene->Add(cannon, STATIC);
    //bottom right cannon
    cannon = new Cannon(-31, -28, 31, 28);
    cannon->MoveTo(928, 537);
    scene->Add(cannon, STATIC);
    
    // -----------------------------------------
    // posição das paredes

    Wall* wall;
    wall = new Wall(0, 0, 960, 8);
    wall->MoveTo(0.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 374);
    wall->MoveTo(0.0f, 8.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 374);
    wall->MoveTo(window->CenterX() + 9.0f, 8.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 960, 10);
    wall->MoveTo(0.0f, window->CenterY() + 22.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 328);
    wall->MoveTo(0.0f, window->CenterY() + 32.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 328);
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
    else if (window->KeyDown('M'))
    {
        // passa manualmente para o próximo nú“el
        Engine::Next<Level3>();
    }
    else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
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