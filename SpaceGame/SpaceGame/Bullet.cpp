/**********************************************************************************
// Bullet (C�digo Fonte)
//
// Cria��o:     18 Set 2022
//
// Compilador:  Visual C++ 2019
//
// Descri��o:   Bullets do Etther
//
**********************************************************************************/

#include "Etther.h"
#include "Scene.h"
#include "Level1.h"
#include "Bullet.h"

// ---------------------------------------------------------------------------------

Bullet::Bullet(int vx, int vy)
{
    velX = vx;
    velY = vy;
    sprite = new Sprite("Resources/blue_bullet.png");

    BBox(new Circle(5));
    type = BULLET;
}

// ---------------------------------------------------------------------------------

Bullet::~Bullet()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Bullet::Update() {
    // m��sil se move apenas no eixo y
    Translate(velX * gameTime, velY * gameTime);

    
}