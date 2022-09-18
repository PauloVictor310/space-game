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

#include "Wall.h"
#include "Etther.h"

// ---------------------------------------------------------------------------------

Wall::Wall(float x1, float y1, float x2, float y2)
{
    // bbox da parede
    BBox(new Rect(x1, y1, x2, y2));

    // velocidades iniciais
    velX = 0.0f;
    velY = 0.0f;

    // tipo do objeto
    type = WALL;
}

// ---------------------------------------------------------------------------------

Wall::~Wall()
{

}

// ---------------------------------------------------------------------------------

void Wall::Update()
{

}

void Wall::Draw()
{

}

// ---------------------------------------------------------------------------------

void Wall::OnCollision(Object* obj)
{

}