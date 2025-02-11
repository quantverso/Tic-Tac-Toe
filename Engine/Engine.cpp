#include "Engine.h"
#include "Scene.h"
#include "Clock.h"
#include <sstream>

// ------------------------------------------------------------------------------------------------

void Engine::Run(Scene* scene)
{
    if (!window.IsOpen())
        window.Create();

    scene->Start();

    if (Scene* old{ std::exchange(s_Scene, scene) })
    {
        delete old;
        return;
    }
    
    Loop();
}

// ------------------------------------------------------------------------------------------------

void Engine::Loop()
{
    Clock    clock;
    unsigned cycles{};

    while (window.IsOpen())
    {
        // Tempo decorrido desde o último frame
        deltaTime = clock.ElapsedTime();

#ifdef _DEBUG
        // Atualiza o título da janela
        cycles++;
        if (clock.Count() >= 1.f)
        {
            static const char* title{ window.GetTitle() };

            std::stringstream text;
            text << std::fixed;
            text.precision(3);

            text << title << "    |    "
                << "FPS: " << cycles << "    |    "
                << "Frame Time: " << deltaTime * 1000 << " (ms)";

            window.SetTitle(text.str().c_str());

            cycles = 0;
            clock.Reset();
        }
#endif
        s_Scene->UpdateObjects();

        window.Clear();
        SDL_RenderSetViewport(window.GetRenderer(), &s_Scene->GetViewport());
        s_Scene->Draw();
        window.Display();

        s_Scene->RemoveObjects();
        s_Scene->Update();
        
        window.PollEvents();

        if (window.IsEventTriggered(Window::Quit))
        {
            delete s_Scene;
            window.Close();
        }
    }
}

// ------------------------------------------------------------------------------------------------
