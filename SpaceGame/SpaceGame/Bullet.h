/**********************************************************************************
// Bullet (Arquivo de Cabe�alho)
//
// Cria��o:     18 Set 2022
//
// Compilador:  Visual C++ 2019
//
// Descri��o:   Bullets do Etther
//
**********************************************************************************/

#ifndef _ETTHER_Bullet_H_
#define _ETTHER_Bullet_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                        // tipos espec��icos da engine
#include "Object.h"                       // interface de Object
#include "Player.h"
#include "Scene.h"

// ---------------------------------------------------------------------------------

class Bullet : public Object
{
private:
    Sprite* sprite = nullptr;

public:

    Bullet(int x, int y);                          // construtor
    ~Bullet();                               // destrutor

    float velX; // velocidade no eixo X
    float velY; // velocidade no eixo Y]

    void Update();                     // atualiza��o
    void Draw();                       // desenho
};

inline void Bullet::Draw()
{
    sprite->Draw(x, y, z);
}
// ---------------------------------------------------------------------------------

#endif