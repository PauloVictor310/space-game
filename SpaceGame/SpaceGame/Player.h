/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     01 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Player do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_PLAYER_H_
#define _ETTHER_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec��icos da engine
#include "Object.h"                     // interface de Object
#include "Sprite.h"                     // interface de Sprites

// ---------------------------------------------------------------------------------
// Constantes Globais

// estados poss��eis para o jogador
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
    uint nextState = STOPED;            // pr�ximo estado do jogador
    uint currColor = BLUE;              // cor atual do jogador
    uint nextColor = BLUE;              // cor atual do jogador

    Player();                           // construtor
    ~Player();                          // destrutor

    void Stop();                        // p�ra jogador
    void Up();                          // muda dire��o para cima
    void Down();                        // muda dire��o para baixo
    void Left();                        // muda dire��o para esquerda
    void Right();                       // muda dire��o para direita

    void OnCollision(Object * obj);     // resolu��o da colis�o
    //void PivotCollision(Object * obj);  // revolve colis�o com piv�E
    void OrbCollision(Object* obj);     // revolve colis�o com orb�E
    void WallCollision(Object* obj);    // revolve colis�o com wallE
    
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------

#endif