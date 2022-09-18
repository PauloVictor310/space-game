/**********************************************************************************
// Cannon (Arquivo de Cabeçalho)
//
// Criação:     18 Set 2022
//
// Compilador:  Visual C++ 2019
//
// Descrição:   Canhões do jogo Etther
//
**********************************************************************************/

#ifndef _ETTHER_CANNON_H_
#define _ETTHER_CANNON_H_


// ---------------------------------------------------------------------------------

#include "Types.h"
#include "Object.h"

// ---------------------------------------------------------------------------------

class Cannon : public Object
{
public:
	Cannon(float x1, float x2, float y1, float y2);
	~Cannon();

	void Update();
	void Draw();
	void OnCollision(Object* obj);
};

// ---------------------------------------------------------------------------------

#endif