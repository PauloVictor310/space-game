/**********************************************************************************
// Level4 (Arquivo de Cabeçalho)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Nível 4 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level4.h"
#include "LevelWin.h"
#include "Player.h"
#include "Orb.h"
#include "Pivot.h"
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

    // cria orb
    Orb* orb = new Orb(RED);
    orb->MoveTo(160, 598);
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