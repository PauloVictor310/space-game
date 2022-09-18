/**********************************************************************************
// Level3 (Código Fonte)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 3 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Etther.h"
#include "Home.h"
#include "Level3.h"
#include "Level4.h"
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

void Level3::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/phase_3_completed.png");

    // cria jogador
    Player* player = new Player();
    scene->Add(player, MOVING);

    //Cria e posiciona bbox dos canhões
    Cannon* cannon;
    //corner left cannon
    cannon = new Cannon(-32, -27, 32, 27);
    cannon->MoveTo(43, 26);
    scene->Add(cannon, STATIC);
    //bottom left cannon
    cannon = new Cannon(-35, -23, 35, 23);
    cannon->MoveTo(44, 464);
    scene->Add(cannon, STATIC);
    //right down cannon
    cannon = new Cannon(-34.5, -27.5, 34.5, 27.5);
    cannon->MoveTo(926, 399);
    scene->Add(cannon, STATIC);

    // -----------------------------------------
    // posição das paredes

    Wall* wall;
    wall = new Wall(0, 0, 8, 365);
    wall->MoveTo(0.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 365);
    wall->MoveTo(window->CenterX() + 9.0f, 0.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 479, 10);
    wall->MoveTo(9.0f, window->CenterY());
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 460, 10);
    wall->MoveTo(window->CenterX() + 19.0f, window->CenterY());
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 8, 347);
    wall->MoveTo(0.0f, window->CenterY() + 5.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 10, 347);
    wall->MoveTo(window->CenterX() + 9.0f, window->CenterY() + 5.0f);
    scene->Add(wall, STATIC);

    wall = new Wall(0, 0, 960, 8);
    wall->MoveTo(0.0f, window->CenterY() + 352.0f);
    scene->Add(wall, STATIC);

    // cria orb
    Orb* orb = new Orb(BLUE);
    orb->MoveTo(816, 118);
    scene->Add(orb, STATIC);

    // cria pontos de mudança de direção
    Pivot* pivot;
    bool left, right, up, down;
    float posX, posY;
    ifstream fin;

    // cria pivôs a partir do arquivo
    fin.open("PivotsL2.txt");
    fin >> left;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // lElinha de informações do pivE
            fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY;
            pivot = new Pivot(left, right, up, down);
            pivot->MoveTo(posX, posY);
            scene->Add(pivot, STATIC);
        }
        else
        {
            // ignora comentários
            fin.clear();
            char temp[80];
            fin.getline(temp, 80);
        }
        fin >> left;
    }
    fin.close();
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