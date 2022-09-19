/**********************************************************************************
// Level3 (Código Fonte)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nú“el 3 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Etther.h"
#include "Home.h"
#include "Level3.h"
#include "Level4.h"
#include "LevelLose.h"
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Wall.h"
#include <string>
#include <fstream>
#include <ctime>
#include "Level2.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

Player* Level3::player = nullptr;

void Level3::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_3_completed.png");

    // cria jogador
    player = new Player(680.0f, 690.0f, RED);
    player->currLevel = LEVEL3;
    scene->Add(player, MOVING);
    //temporario
    //player->currColor = RED;

    //Cria e posiciona bbox dos canhões
    //corner left cannon
    topLeftCannon = new Cannon(-32, -27, 32, 27);
    topLeftCannon->MoveTo(43, 26);
    scene->Add(topLeftCannon, STATIC);
    //bottom left cannon
    bottomLeftCannon = new Cannon(-35, -23, 35, 23);
    bottomLeftCannon->MoveTo(44, 464);
    scene->Add(bottomLeftCannon, STATIC);
    //right down cannon
    bottomRightCannon = new Cannon(-34.5, -27.5, 34.5, 27.5);
    bottomRightCannon->MoveTo(926, 399);
    scene->Add(bottomRightCannon, STATIC);

    // -----------------------------------------
    // posição das paredes

    Wall* wall;
    wall = new Wall(0, 0, 8, 365);
    wall->color = BLUE;
    wall->MoveTo(0.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 365);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() + 9.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 479, 10);
    wall->color = BLUE;
    wall->MoveTo(9.0f, window->CenterY());
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 460, 10);
    wall->color = RED;
    wall->MoveTo(window->CenterX() + 19.0f, window->CenterY());
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 347);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() + 5.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 347);
    wall->color = BLUE;
    wall->MoveTo(window->CenterX() + 9.0f, window->CenterY() + 5.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 960, 8);
    wall->color = RED;
    wall->MoveTo(0.0f, window->CenterY() + 352.0f);
    scene->Add(wall, STATIC);

    // cria orb
    Orb* orb = new Orb(BLUE);
    orb->MoveTo(816, 118);
    scene->Add(orb, STATIC);

}

// ------------------------------------------------------------------------------

void Level3::Finalize()
{
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void Level3::Update()
{

    if ((clock() - start) % 233 == 0) {
        Bullet* bl1 = new Bullet(300, 20);
        bl1->MoveTo(bottomLeftCannon->X() + 20, bottomLeftCannon->Y() - 17, Layer::UPPER);
        scene->Add(bl1, STATIC);

        Bullet* bl2 = new Bullet(300, 66);
        bl2->MoveTo(bottomLeftCannon->X() + 20, bottomLeftCannon->Y() + 17, Layer::UPPER);
        scene->Add(bl2, STATIC);

        Bullet* tr1 = new Bullet(-200, 100);
        tr1->MoveTo(bottomRightCannon->X(), bottomRightCannon->Y() + 12, Layer::UPPER);
        scene->Add(tr1, STATIC);

        Bullet* tr2 = new Bullet(-250, 220);
        tr2->MoveTo(bottomRightCannon->X(), bottomRightCannon->Y() - 15, Layer::UPPER);
        scene->Add(tr2, STATIC);

    }

    if ((clock() - start) % 205 == 0) {

        Bullet* br1 = new Bullet(300, 300);
        br1->MoveTo(topLeftCannon->X() + 20, topLeftCannon->Y() + 7, Layer::UPPER);
        scene->Add(br1, STATIC);

        Bullet* br2 = new Bullet(300, 300);
        br2->MoveTo(topLeftCannon->X() - 20, topLeftCannon->Y() - 7, Layer::UPPER);
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

    if (window->KeyDown(VK_ESCAPE))
    {
        // volta para a tela de abertura
        Engine::Next<Home>();
    }
    else if (window->KeyDown('K'))
    {
        // passa manualmente para o próximo nú“el
        Engine::Next<Level4>();
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

    // Muda para o nú“el 2
    if (player->nextLevel == LEVEL2)
        Engine::Next<Level2>();

    // Muda para o nú“el 4
    if (player->nextLevel == LEVEL4)
        Engine::Next<Level4>();
}

// ------------------------------------------------------------------------------

void Level3::Draw()
{
    // desenha cena
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    scene->Draw();

    // desenha bounding box dos objetos
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------