/**********************************************************************************
// Orb (Arquivo de Cabe�alho)
// 
// Cria��o:     18 Set 2022
//
// Compilador:  Visual C++ 2019
//
// Descri��o:   Orbs do Etther
//
**********************************************************************************/

#ifndef _ETTHER_ORB_H_
#define _ETTHER_ORB_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                        // tipos espec�icos da engine
#include "Object.h"                       // interface de Object
#include "Player.h"

// ---------------------------------------------------------------------------------

class Orb : public Object
{
public:
    uint color;

    Orb(uint c);                          // construtor
    ~Orb();                               // destrutor

    void Update() {};                     // atualiza��o
    void Draw() {};                       // desenho
};

// ---------------------------------------------------------------------------------

#endif