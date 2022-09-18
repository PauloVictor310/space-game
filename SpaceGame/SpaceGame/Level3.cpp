/**********************************************************************************
// Level3 (C�digo Fonte)
//
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   N�vel 3 do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "Level3.h"
#include "Level4.h"
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"
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

    // cria orb
    Orb* orb = new Orb(BLUE);
    orb->MoveTo(816, 118);
    scene->Add(orb, STATIC);

    // cria pontos de mudan�a de dire��o
    Pivot* pivot;
    bool left, right, up, down;
    float posX, posY;
    ifstream fin;

    // cria piv�s a partir do arquivo
    fin.open("PivotsL2.txt");
    fin >> left;
    while (!fin.eof())
    {
        if (fin.good())
        {
            // l�Elinha de informa��es do piv�E
            fin >> right; fin >> up; fin >> down; fin >> posX; fin >> posY;
            pivot = new Pivot(left, right, up, down);
            pivot->MoveTo(posX, posY);
            scene->Add(pivot, STATIC);
        }
        else
        {
            // ignora coment�rios
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
        // passa manualmente para o pr�ximo n��el
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