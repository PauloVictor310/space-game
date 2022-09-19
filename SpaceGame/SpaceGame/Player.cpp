/**********************************************************************************
// Player (C?digo Fonte)
//
// Cria??o:     01 Jan 2013
// Atualiza??o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri??o:   Player do jogo Etther
//
**********************************************************************************/

#include "Etther.h"
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"
#include "Wall.h"

// ---------------------------------------------------------------------------------

Player::Player(float initX, float initY, uint color)
{
    spriteL = new Sprite("Resources/spaceship_red_left.png");
    spriteR = new Sprite("Resources/spaceship_red_right.png");
    spriteU = new Sprite("Resources/spaceship_red_top.png");
    spriteD = new Sprite("Resources/spaceship_red_down.png");
    spriteBlueL = new Sprite("Resources/spaceship_blue_left.png");
    spriteBlueR = new Sprite("Resources/spaceship_blue_right.png");
    spriteBlueU = new Sprite("Resources/spaceship_blue_top.png");
    spriteBlueD = new Sprite("Resources/spaceship_blue_down.png");

    Player::initX = initX;
    Player::initY = initY;
    Player::currColor = color;
    Player::nextColor = color;

    // imagem do pacman ?E48x48 (com borda transparente de 4 pixels)
    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(initX , initY);
    type = PLAYER;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete spriteL;
    delete spriteR;
    delete spriteU;
    delete spriteD;
    delete spriteBlueL;
    delete spriteBlueR;
    delete spriteBlueU;
    delete spriteBlueD;
}

// ---------------------------------------------------------------------------------

void Player::Stop()
{
    velX = 0;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Up()
{
    velX = 0;
    velY = -200.0f;
}

// ---------------------------------------------------------------------------------

void Player::Down()
{
    velX = 0;
    velY = 200.0f;
}

// ---------------------------------------------------------------------------------

void Player::Left()
{
    velX = -200.0f;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::Right()
{
    velX = 200.0f;
    velY = 0;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    //if (obj->Type() == PIVOT)
        //PivotCollision(obj);

    if (obj->Type() == ORB)
        OrbCollision(obj);

    if (obj->Type() == WALL)
        WallCollision(obj);

    if (obj->Type() == BULLET)
        BulletCollision();
}

// ---------------------------------------------------------------------------------

void Player::BulletCollision() {
    nextLevel = LEVELOSE;
}

void Player::OrbCollision(Object* obj) {
    Orb* o = (Orb*)obj;

    if (o->color == BLUE) {
        currColor = BLUE;
    }
    else if (o->color == RED) {
        currColor = RED;
    }
}

void Player::WallCollision(Object* obj) {
    Wall* wall = (Wall*)obj;
    Player* player = (Player*)obj;

    if (wall->color == BLUE && currColor == RED) {
        if (currState == LEFT) {
            Translate(4, 0);
            Stop();
        }
        else if (currState == UP) {
            Translate(0, 4);
            Stop();
        }
        else if (currState == RIGHT) {
            Translate(-4, 0);
            Stop();
        }
        else if (currState == DOWN) {
            Translate(0, -4);
            Stop();
        }
    }
    else if (wall->color == RED && currColor == BLUE) {
        if (currState == LEFT) {
            Translate(4, 0);
            Stop();
        }
        else if (currState == UP) {
            Translate(0, 4);
            Stop();
        }
        else if (currState == RIGHT) {
            Translate(-4, 0);
            Stop();
        }
        else if (currState == DOWN) {
            Translate(0, -4);
            Stop();
        }
    }
}

/*void Player::PivotCollision(Object* obj)
{
    Pivot * p = (Pivot*)obj;

    switch (currState)
    {
    case STOPED:
        // -----------------------
        // CurrentState == STOPED
        // -----------------------

        switch (nextState)
        {
        case LEFT:
            if (p->left)
            {
                currState = LEFT;
                Left();
            }
            break;
        case RIGHT:
            if (p->right)
            {
                currState = RIGHT;
                Right();
            }

            break;
        case UP:
            if (p->up)
            {
                currState = UP;
                Up();
            }
            break;
        case DOWN:
            if (p->down)
            {
                currState = DOWN;
                Down();
            }
            break;
        }
        break;

    case LEFT:
        // -----------------------
        // CurrentState == LEFT
        // -----------------------

        if (x < p->X())
        {
            if (!p->left)
            {
                MoveTo(p->X(), Y());
                currState = STOPED;
                Stop();
            }
        }

        switch (nextState)
        {
        case LEFT:
            if (x < p->X())
            {
                if (!p->left)
                {
                    MoveTo(p->X(), Y());
                    currState = STOPED;
                    Stop();
                }
            }
            break;
        case RIGHT:
            currState = RIGHT;
            Right();

            break;
        case UP:
            if (x < p->X())
            {
                if (p->up)
                {
                    MoveTo(p->X(), Y());
                    currState = UP;
                    Up();
                }
            }
            break;
        case DOWN:
            if (x < p->X())
            {
                if (p->down)
                {
                    MoveTo(p->X(), Y());
                    currState = DOWN;
                    Down();
                }
            }
            break;
        }
        break;

    case RIGHT:
        // -----------------------
        // CurrentState == RIGHT
        // -----------------------

        if (x > p->X())
        {
            if (!p->right)
            {
                MoveTo(p->X(), Y());
                currState = STOPED;
                Stop();
            }
        }

        switch (nextState)
        {
        case LEFT:
            currState = LEFT;
            Left();
            break;
        case RIGHT:
            if (x > p->X())
            {
                if (!p->right)
                {
                    MoveTo(p->X(), Y());
                    currState = STOPED;
                    Stop();
                }
            }

            break;
        case UP:
            if (x > p->X())
            {
                if (p->up)
                {
                    MoveTo(p->X(), Y());
                    currState = UP;
                    Up();
                }
            }
            break;
        case DOWN:
            if (x > p->X())
            {
                if (p->down)
                {
                    MoveTo(p->X(), Y());
                    currState = DOWN;
                    Down();
                }
            }
            break;
        }
        break;

    case UP:
        // -----------------------
        // CurrentState == UP
        // -----------------------

        if (y < p->Y())
        {
            if (!p->up)
            {
                MoveTo(x, p->Y());
                currState = STOPED;
                Stop();
            }
        }

        switch (nextState)
        {
        case LEFT:
            if (y < p->Y())
            {
                if (p->left)
                {
                    MoveTo(x, p->Y());
                    currState = LEFT;
                    Left();
                }
            }
            break;
        case RIGHT:
            if (y < p->Y())
            {
                if (p->right)
                {
                    MoveTo(x, p->Y());
                    currState = RIGHT;
                    Right();
                }
            }
            break;
        case UP:
            if (y < p->Y())
            {
                if (!p->up)
                {
                    MoveTo(x, p->Y());
                    currState = STOPED;
                    Stop();
                }
            }
            break;
        case DOWN:
            currState = DOWN;
            Down();
            break;
        }
        break;

    case DOWN:
        // -----------------------
        // CurrentState == DOWN
        // -----------------------

        if (y > p->Y())
        {
            if (!p->down)
            {
                MoveTo(x, p->Y());
                currState = STOPED;
                Stop();
            }
        }

        switch (nextState)
        {
        case LEFT:
            if (y > p->Y())
            {
                if (p->left)
                {
                    MoveTo(x, p->Y());
                    currState = LEFT;
                    Left();
                }
            }
            break;
        case RIGHT:
            if (y > p->Y())
            {
                if (p->right)
                {
                    MoveTo(x, p->Y());
                    currState = RIGHT;
                    Right();
                }
            }
            break;
        case UP:
            currState = UP;
            Up();
            break;
        case DOWN:
            if (y > p->Y())
            {
                if (!p->down)
                {
                    MoveTo(x, p->Y());
                    currState = STOPED;
                    Stop();
                }
            }
            break;
        }
        break;
    }
}
*/

// ---------------------------------------------------------------------------------

void Player::Update()
{

    if (window->KeyDown(VK_LEFT))
    {
        currState = LEFT;
        nextState = LEFT;
        Left();
    }

    if (window->KeyDown(VK_RIGHT))
    {
        currState = RIGHT;
        nextState = RIGHT;
        Right();
    }

    if (window->KeyDown(VK_UP))
    {
        currState = UP;
        nextState = UP;
        Up();
    }

    if (window->KeyDown(VK_DOWN))
    {
        currState = DOWN;
        nextState = DOWN;
        Down();
    }

    if (window->KeyDown('P'))
    {
        //currState = STOPED;
        Stop();
    }

    // atualiza posi??o
    Translate(velX * gameTime, velY * gameTime);

    // ---------------------------------------------------------------------------------
    // Movimenta??o do n?vel 1
    if (currLevel == LEVEL1) {
        //n?o pode ir para a esquerda
        if (X() - 20 < 0)
            MoveTo(20.0f, Y());

        //direita (muda para o n?vel 2)
        if (X() - 20 > window->Width()) {
            nextLevel = LEVEL2;
        }

        //cima (muda para o n?vel 4) (NAO FIZ)
        if (Y() + 20 < 0) {
            MoveTo(X(), window->Height() + 20.0f);
            nextLevel = LEVEL4;
        }

        //n?o pode ir para baixo
        if (Y() + 20 > window->Height())
            MoveTo(X(), window->Height() - 20.0f);
    }
    // ---------------------------------------------------------------------------------
    // Movimenta??o do n?vel 2
    if (currLevel == LEVEL2) {
        //esquerda (muda para o n?vel 1)
        if (X() - 20 < 0) {
            nextLevel = LEVEL1;
        }

        //n?o pode ir para a direita
        if (X() + 20 > window->Width())
            MoveTo(window->Width() - 20.0f, Y());

        //cima (muda para o n?vel 3)
        if (Y() + 20 < 0) {
            nextLevel = LEVEL3;
        }

        //n?o pode ir para baixo
        if (Y() + 20 > window->Height())
            MoveTo(X(), window->Height() - 20.0f);
    }
    // ---------------------------------------------------------------------------------
    // Movimenta??o do n?vel 3
    if (currLevel == LEVEL3) {
        //esquerda (muda para o n?vel 4) (NAO FIZ)
        if (X() - 20 < 0) {
            nextLevel = LEVEL4;
        }

        //n?o pode ir para a direita
        if (X() + 20 > window->Width())
            MoveTo(window->Width() - 20.0f, Y());

        //n?o pode ir para cima
        if (Y() - 20 < 0)
            MoveTo(X(), window->Height() - 20.0f);

        //baixo (muda para o n?vel 2)
        if (Y() + 20 > window->Height())
            nextLevel = LEVEL2;
    }
    // ---------------------------------------------------------------------------------
    // Movimenta??o do n?vel 4
    if (currLevel == LEVEL4) {
        //n?o pode ir para a esquerda
        if (X() - 20 < 0)
            MoveTo(20.0f, Y());

        //direita (muda para o n?vel 3)
        if (X() - 20 > window->Width()) {
            nextLevel = LEVEL3;
        }

        //n?o pode ir para cima
        if (Y() + 20 < 0) {
            MoveTo(X(), window->Height() + 20.0f);
        }

        //baixo (muda para o n?vel 1)
        if (Y() + 20 > window->Height())
            nextLevel = LEVEL1;
    }
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    if (currColor == BLUE) {
        switch (currState)
        {
        case LEFT:  spriteBlueL->Draw(x, y, Layer::UPPER); break;
        case RIGHT: spriteBlueR->Draw(x, y, Layer::UPPER); break;
        case UP:    spriteBlueU->Draw(x, y, Layer::UPPER); break;
        case DOWN:  spriteBlueD->Draw(x, y, Layer::UPPER); break;
        default:
            switch (nextState)
            {
            case LEFT:  spriteBlueL->Draw(x, y, Layer::UPPER); break;
            case RIGHT: spriteBlueR->Draw(x, y, Layer::UPPER); break;
            case UP:    spriteBlueU->Draw(x, y, Layer::UPPER); break;
            case DOWN:  spriteBlueD->Draw(x, y, Layer::UPPER); break;
            default:    spriteBlueL->Draw(x, y, Layer::UPPER);
            }
        }
    }
    else if (currColor == RED) {
        switch (currState)
        {
        case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
        case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
        case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
        case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
        default:
            switch (nextState)
            {
            case LEFT:  spriteL->Draw(x, y, Layer::UPPER); break;
            case RIGHT: spriteR->Draw(x, y, Layer::UPPER); break;
            case UP:    spriteU->Draw(x, y, Layer::UPPER); break;
            case DOWN:  spriteD->Draw(x, y, Layer::UPPER); break;
            default:    spriteL->Draw(x, y, Layer::UPPER);
            }
        }
    }

}

// ---------------------------------------------------------------------------------