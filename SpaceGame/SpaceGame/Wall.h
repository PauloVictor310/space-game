/**********************************************************************************
// Wall (Arquivo de Cabeçalho)
//
// Criação:     18 Set 2022
//
// Compilador:  Visual C++ 2019
//
// Descrição:   Parede do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_WALL_H_
#define _ETTHER_WALL_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"                                  // tipos específicos da engine
#include "Object.h"                                 // interface de Object
#include "Sprite.h"                                 // interface de Sprites

// ---------------------------------------------------------------------------------

class Wall : public Object
{
public:
    float velX;                                     // velocidade horizontal
    float velY;                                     // velocidade vertical

    Wall(float x1, float y1, float x2, float y2);   // construtor
    ~Wall();                                        // destrutor

    void Update();                                  // atualização do objeto
    void Draw();                                    // desenho do objeto
    void OnCollision(Object* obj);                  // tratamento de colisão
};

// ---------------------------------------------------------------------------------

#endif