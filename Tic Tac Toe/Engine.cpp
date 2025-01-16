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

    if (Scene* old{ std::exchange(Engine::scene, scene) })
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

    while (true)
    {
        // Tempo decorrido desde o último frame
        deltaTime = clock.ElapsedTime();

#ifdef _DEBUG
        // Atualiza o título da janela
        cycles++;
        if (clock.Count() >= 1.f)
        {
            static const char* title{ window.Title() };

            std::stringstream text;
            text << std::fixed;
            text.precision(3);

            text << title << "    |    "
                << "FPS: " << cycles << "    |    "
                << "Frame Time: " << deltaTime * 1000 << " (ms)";

            window.Title(text.str().c_str());

            cycles = 0;
            clock.Reset();
        }
#endif
        scene->UpdateObjects();
        window.Clear();
        scene->Draw();
        window.Display();
        scene->DestroyObjects();
        scene->Update();

        window.WatchEvents();

        if (window.CheckEvent(Window::Quit))
        {
            delete scene;

            window.Close();
            break;
        }
    }
}

// ------------------------------------------------------------------------------------------------
