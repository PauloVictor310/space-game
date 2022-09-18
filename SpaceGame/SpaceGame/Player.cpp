/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     01 Jan 2013
// Atualização: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo Etther
//
**********************************************************************************/

#include "Etther.h"
#include "Player.h"
#include "Pivot.h"
#include "Orb.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    spriteL = new Sprite("Resources/spaceship_red_left.png");
    spriteR = new Sprite("Resources/spaceship_red_right.png");
    spriteU = new Sprite("Resources/spaceship_red_top.png");
    spriteD = new Sprite("Resources/spaceship_red_down.png");
    spriteBlueL = new Sprite("Resources/spaceship_blue_left.png");
    spriteBlueR = new Sprite("Resources/spaceship_blue_right.png");
    spriteBlueU = new Sprite("Resources/spaceship_blue_top.png");
    spriteBlueD = new Sprite("Resources/spaceship_blue_down.png");

    // imagem do pacman E48x48 (com borda transparente de 4 pixels)
    BBox(new Rect(-20, -20, 20, 20));
    MoveTo(480.0f, 450.0f);
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

void Player::OnCollision(Object * obj)
{
    if (obj->Type() == PIVOT)
        PivotCollision(obj);

    if (obj->Type() == ORB)
        OrbCollision(obj);
}

// ---------------------------------------------------------------------------------

void Player::OrbCollision(Object* obj) {
    Orb* o = (Orb*)obj;

    if (o->color == BLUE) {
        currColor = BLUE;
    }
    else if (o->color == RED) {
        currColor = RED;
    }
}

void Player::PivotCollision(Object * obj)
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

// ---------------------------------------------------------------------------------

void Player::Update()
{

    if (window->KeyDown(VK_LEFT))
    {
        nextState = LEFT;

        if (currState == RIGHT || currState == STOPED)
        {
            currState = LEFT;
            Left();
        }            
    }
    
    if (window->KeyDown(VK_RIGHT))
    {
        nextState = RIGHT;

        if (currState == LEFT || currState == STOPED)
        {
            currState = RIGHT;
            Right();
        }
    }
    
    if (window->KeyDown(VK_UP))
    {
        nextState = UP;

        if (currState == DOWN || currState == STOPED)
        {
            currState = UP;
            Up();
        }
    }
    
    if (window->KeyDown(VK_DOWN))
    {
        nextState = DOWN;

        if (currState == UP || currState == STOPED)
        {
            currState = DOWN;
            Down();
        }
    }

    // atualiza posição
    Translate(velX * gameTime, velY * gameTime);

    // mantém player dentro da tela
    if (x+20 < 0)
        MoveTo(window->Width()+20.f, Y());

    if (x-20 > window->Width())
        MoveTo(-20.0f, Y());

    if (Y()+20 < 0)
        MoveTo(x, window->Height()+20.0f);

    if (Y()-20 > window->Height())
        MoveTo(x, -20.0f);
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