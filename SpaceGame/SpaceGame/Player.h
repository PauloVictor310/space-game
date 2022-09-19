/**********************************************************************************
// Player (Arquivo de CabeÁalho)
// 
// CriaÁ„o:     01 Jan 2013
// AtualizaÁ„o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// DescriÁ„o:   Player do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_PLAYER_H_
#define _ETTHER_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclusıes

#include "Types.h"                      // tipos espec˙üicos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss˙ìeis para o jogador
enum PLAYERSTATE {STOPED, UP, DOWN, LEFT, RIGHT};
enum PLAYERCOLOR { BLUE, RED };

// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    Sprite * spriteL = nullptr;         // sprite do player indo para esquerda
    Sprite * spriteR = nullptr;         // sprite do player indo para direita
    Sprite * spriteU = nullptr;         // sprite do player indo para cima
    Sprite * spriteD = nullptr;         // sprite do player indo para baixo
    Sprite* spriteBlueL = nullptr;      // sprite do player azul indo para esquerda
    Sprite* spriteBlueR = nullptr;      // sprite do player azul indo para direita
    Sprite* spriteBlueU = nullptr;      // sprite do player azul indo para cima
    Sprite* spriteBlueD = nullptr;      // sprite do player azul indo para baixo
    float velX = 0;                     // velocidade horizontal do player
    float velY = 0;                     // velocidade vertical do player

public:
    uint currState = STOPED;            // estado atual do jogador
    uint nextState = STOPED;            // prÛximo estado do jogador
    uint currColor = BLUE;              // cor atual do jogador
    uint nextColor = BLUE;              // cor atual do jogador

    Player();                           // construtor
    ~Player();                          // destrutor

    void Stop();                        // p·ra jogador
    void Up();                          // muda direÁ„o para cima
    void Down();                        // muda direÁ„o para baixo
    void Left();                        // muda direÁ„o para esquerda
    void Right();                       // muda direÁ„o para direita

    void OnCollision(Object * obj);     // resoluÁ„o da colis„o
    //void PivotCollision(Object * obj);  // revolve colis„o com pivÅE
    void OrbCollision(Object* obj);     // revolve colis„o com orbÅE
    void WallCollision(Object* obj);    // revolve colis„o com wallE
    
    void Update();                      // atualizaÁ„o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif