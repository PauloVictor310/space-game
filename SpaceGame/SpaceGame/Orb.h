/**********************************************************************************
// Orb (Arquivo de Cabeçalho)
// 
// Criação:     18 Set 2022
//
// Compilador:  Visual C++ 2019
//
// Descrição:   Orbs do Etther
//
**********************************************************************************/

#ifndef _ETTHER_ORB_H_
#define _ETTHER_ORB_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                        // tipos especíƒicos da engine
#include "Object.h"                       // interface de Object
#include "Player.h"

// ---------------------------------------------------------------------------------

class Orb : public Object
{
public:
    uint color;

    Orb(uint c);                          // construtor
    ~Orb();                               // destrutor

    void Update() {};                     // atualização
    void Draw() {};                       // desenho
};

// ---------------------------------------------------------------------------------

#endif