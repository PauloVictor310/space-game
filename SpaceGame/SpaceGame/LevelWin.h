/**********************************************************************************
// LevelWin (Arquivo de Cabe�alho)
//
// Cria��o:     18 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Tela de vit�ria do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_LEVELWIN_H_
#define _ETTHER_LEVELWIN_H_

// ------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Sprite.h"
#include "Scene.h"

// ------------------------------------------------------------------------------

class LevelWin : public Game
{
private:
    Sprite* backg = nullptr;       // background
    Scene* scene = nullptr;        // gerenciado de cena

public:

    void Init();                   // inicializa jogo
    void Update();                 // atualiza l�gica do jogo
    void Draw();                   // desenha jogo
    void Finalize();               // finaliza jogo
};

// -----------------------------------------------------------------------------

#endif
