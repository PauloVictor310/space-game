/**********************************************************************************
// Level4 (Arquivo de Cabe�alho)
//
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   N�vel 4 do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_LEVEl4_H_
#define _ETTHER_LEVEL4_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "Player.h"

// ------------------------------------------------------------------------------

class Level4 : public Game
{
private:
    Sprite* backg = nullptr;       // background
    Scene* scene = nullptr;        // gerenciado de cena

    bool viewBBox = false;         // habilita visualiza��o da bounding box
    bool ctrlKeyB = false;         // controle da tecla B

public:
    static Player* player;

    void Init();                   // inicializa jogo
    void Update();                 // atualiza l�gica do jogo
    void Draw();                   // desenha jogo
    void Finalize();               // finaliza jogo
};

// -----------------------------------------------------------------------------

#endif
