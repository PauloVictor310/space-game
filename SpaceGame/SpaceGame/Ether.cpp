/**********************************************************************************
// Etther (C�digo Fonte)
// 
// Cria��o:     01 Jan 2013
// Atualiza��o: 25 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Uso da classe Scene para gerenciar objetos e tratar colis�o
//
**********************************************************************************/

#include "Engine.h"
#include "Resources.h"
#include "Home.h"

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura a janela do jogo
    engine->window->Mode(WINDOWED);
    engine->window->Size(960, 720);
    engine->window->Color(25, 25, 25);
    engine->window->Title("Etther");
    engine->window->Icon(IDI_ICON);

    // configura dispositivo gr�fico
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new Home());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

