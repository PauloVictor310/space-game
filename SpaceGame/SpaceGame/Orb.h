/**********************************************************************************
// Orb (Arquivo de Cabe�alho)
// 
// Cria��o:     01 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Ponto de mudan�a de dire��o para o jogador e fantasmas
//
**********************************************************************************/

#ifndef _PACMAN_Orb_H_
#define _PACMAN_Orb_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                          // tipos espec��icos da engine
#include "Object.h"                         // interface de Object
#include "Player.h"

// ---------------------------------------------------------------------------------

class Orb : public Object
{
public:
    uint color;

    Orb(uint c);  // construtor
    ~Orb();                               // destrutor

    void Update() {};                       // atualiza��o
    void Draw() {};                         // desenho
};

// ---------------------------------------------------------------------------------

#endif