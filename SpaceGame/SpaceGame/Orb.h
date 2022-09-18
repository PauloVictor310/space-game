/**********************************************************************************
// Orb (Arquivo de Cabeçalho)
// 
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Ponto de mudança de direção para o jogador e fantasmas
//
**********************************************************************************/

#ifndef _PACMAN_Orb_H_
#define _PACMAN_Orb_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                          // tipos especúƒicos da engine
#include "Object.h"                         // interface de Object
#include "Player.h"

// ---------------------------------------------------------------------------------

class Orb : public Object
{
public:
    uint color;

    Orb(uint c);  // construtor
    ~Orb();                               // destrutor

    void Update() {};                       // atualização
    void Draw() {};                         // desenho
};

// ---------------------------------------------------------------------------------

#endif