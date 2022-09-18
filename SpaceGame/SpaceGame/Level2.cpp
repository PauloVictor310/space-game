/**********************************************************************************
// Level2 (Código Fonte) 
// 
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 2 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level2.h"
#include "Level3.h"
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"
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

    // cria orb
    Orb* orb = new Orb(RED);
    orb->MoveTo(160, 271);
    scene->Add(orb, STATIC);

    // cria pontos de mudança de direção
    Pivot * pivot;
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