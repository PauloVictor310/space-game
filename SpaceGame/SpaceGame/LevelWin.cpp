/**********************************************************************************
// LevelWin (Arquivo de Cabeçalho)
//
// Criação:     18 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Tela de vitória do jogo Etther
//
**********************************************************************************/

#include "Engine.h"
#include "Home.h"
#include "LevelWin.h"
#include "LevelLose.h"
#include "Player.h"
#include "Pivot.h"
#include <string>
#include <fstream>
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------

void LevelWin::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // cria background
    backg = new Sprite("Resources/win_screen.png");

    // cria jogador
    Player* player = new Player();
    scene->Add(player, MOVING);
}

// ------------------------------------------------------------------------------

void LevelWin::Finalize()
{
    delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------

void LevelWin::Update()
{

    if (window->KeyDown(VK_ESCAPE))
    {
        // volta para a tela de abertura
        Engine::Next<Home>();
    }
    else if (window->KeyDown('D'))
    {
        // volta para a tela de abertura
        Engine::Next<LevelLose>();
    }
    else
    {
        // atualiza cena
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void LevelWin::Draw()
{
    // desenha cena
    backg->Draw(float(window->CenterX()), float(window->CenterY()), Layer::BACK);
    scene->Draw();
}

// ------------------------------------------------------------------------------