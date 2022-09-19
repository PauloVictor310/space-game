/**********************************************************************************
// Game (Arquivo de CabeÁalho)
//
// CriaÁ„o:     08 Dez 2012
// AtualizaÁ„o: 10 Ago 2021
// Compilador:  Visual C++ 2019
//
// DescriÁ„o:   Uma classe abstrata para representar um jogo.
//
//              Para criar um jogo o programador deve criar uma classe derivada
//              de Game e sobrescrever os mÈtodos Init, Update, Draw e Finalize.
//              Para rodar o jogo, deve-se passar o objeto Game para o mÈtodo
//              Start() de um objeto Engine.
//
**********************************************************************************/

#ifndef _PROGJOGOS_GAME_H_
#define _PROGJOGOS_GAME_H_

// ---------------------------------------------------------------------------------

#include "Window.h"

// ---------------------------------------------------------------------------------

class Game
{
    // Membros protegidos s„o privados para o mundo externo mas
    // p˙blicos para as classes derivadas, ou seja, as classes
    // derivadas de Game ser„o capazes de acessar estes membros.
protected:
    static Window* & window;                    // janela do jogo
    static float   & gameTime;                  // tempo do ˙ltimo quadro

public:
    Game();                                     // construtor
    virtual ~Game();                            // destrutor
    
    // MÈtodos que podem ser sobrescritos para implementar 
    // funcionalidade espec˙Éica para o jogo. Eles jÅEpossuem
    // uma implementaÁ„o padr„o.

    virtual void OnPause();                     // pausa do jogo

    // Estes mÈtodos s„o puramente virtuais, isto ÅE devem ser 
    // implementados em todas as classes derivas de Game.

    virtual void Init() = 0;                    // inicializaÁ„o do jogo
    virtual void Update() = 0;                  // atualizaÁ„o do jogo
    virtual void Draw() = 0;                    // desenho da cena
    virtual void Finalize() = 0;                // finalizaÁ„o do jogo
};

// ---------------------------------------------------------------------------------

#endif