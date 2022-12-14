/**********************************************************************************
// Level3 (Arquivo de Cabe?alho)
//
// Cria??o:     18 Jan 2013
// Atualiza??o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri??o:   N??el 3 do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_LEVEl3_H_
#define _ETTHER_LEVEL3_H_

// ------------------------------------------------------------------------------
// Inclus?es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Cannon.h"
#include "Player.h"
#include <ctime>

// ------------------------------------------------------------------------------

class Level3 : public Game
{
private:
    Sprite* backg = nullptr;       // background
    Scene* scene = nullptr;        // gerenciado de cena

    Cannon* bottomLeftCannon = nullptr;
    Cannon* bottomRightCannon = nullptr;
    Cannon* topLeftCannon = nullptr;

    bool hasMissile = true;
    bool ctrlKeyE = false;         // controle da tecla E

    bool viewBBox = false;         // habilita visualiza??o da bounding box
    bool ctrlKeyB = false;         // controle da tecla B

public:
    static Player* player;

    void Init();                   // inicializa jogo
    void Update();                 // atualiza l?gica do jogo
    void Draw();                   // desenha jogo
    void Finalize();               // finaliza jogo

    clock_t start = clock();
};

// -----------------------------------------------------------------------------

#endif