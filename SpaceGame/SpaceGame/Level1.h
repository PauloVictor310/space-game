/**********************************************************************************
// Level1 (Arquivo de Cabe�alho)
// 
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   N��el 1 do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_LEVEL1_H_
#define _ETTHER_LEVEL1_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Player.h"
#include <vector>
#include <ctime>

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
    Sprite* backg = nullptr;      // background
    
    Cannon* rightCannon = nullptr;
    Cannon* leftCannon = nullptr;

    bool viewBBox = false;         // habilita visualiza��o da bounding box
    bool ctrlKeyB = false;         // controle da tecla B

public:
    
    Scene* scene = nullptr;      // gerenciador de cena
    static Player* player;

    void Init();                   // inicializa jogo
    void Update();                 // atualiza l�gica do jogo
    void Draw();                   // desenha jogo
    void Finalize();               // finaliza jogo;

    clock_t start = clock();
};

// -----------------------------------------------------------------------------

#endif