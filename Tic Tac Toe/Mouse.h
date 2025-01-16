#ifndef QUANTVERSO_MOUSE_H
#define QUANTVERSO_MOUSE_H

// ------------------------------------------------------------------------------------------------

#include "Transformable.h"
#include <bitset>
#include <optional>

// ------------------------------------------------------------------------------------------------

class Mouse
{
public:
    enum MouseButton
    {
        Left     = SDL_BUTTON_LEFT,
        Middle   = SDL_BUTTON_MIDDLE,
        Right    = SDL_BUTTON_RIGHT,       
        XButton1 = SDL_BUTTON_X1,
        XButton2 = SDL_BUTTON_X2
    };

    struct MouseState
    {
        Vector2i position;
        bool isInViewport;
    };

    ////////////////////////////////////////////////////////////
    /// \brief Verifica se um botão do mouse está atualmente pressionado.
    ///
    /// Este método retorna true enquanto o botão do mouse especificado
    /// estiver pressionado.
    ///
    /// \param button O botão do mouse a ser verificado.
    /// \return true se o botão estiver pressionado, false caso contrário.
    /// 
    ////////////////////////////////////////////////////////////
    static bool ButtonPressed(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Retorna true uma vez quando o botão do mouse é pressionado.
    ///
    /// Este método detecta o evento de pressionamento do botão e retorna
    /// true apenas uma vez durante o ciclo de pressionamento. Subsequentemente,
    /// retornará false até que o botão seja liberado e pressionado novamente.
    ///
    /// \param button O botão do mouse a ser verificado.
    /// \return true uma vez se o botão foi pressionado, false caso contrário.
    /// 
    ////////////////////////////////////////////////////////////
    static bool ButtonDown(MouseButton button);

    ////////////////////////////////////////////////////////////
    /// \brief Obtém a posição atual do mouse em coordenadas globais.
    ///
    /// Este método retorna a posição do cursor do mouse na tela, em relação
    /// às coordenadas globais (geralmente a posição em relação à tela principal).
    ///
    /// \return A posição global do mouse como um vetor de coordenadas (x, y).
    /// 
    ////////////////////////////////////////////////////////////
    static const Vector2i& Position();
    static const MouseState& Position(const Rect& viewport);

    ////////////////////////////////////////////////////////////
    /// \brief Define a posição global do cursor do mouse.
    ///
    /// Este método move o cursor do mouse para uma posição específica
    /// em coordenadas globais (na tela inteira).
    ///
    /// \param x A nova coordenada x do cursor.
    /// \param y A nova coordenada y do cursor.
    /// 
    ////////////////////////////////////////////////////////////
    static void Position(float x, float y);

private:
    inline static std::bitset<XButton2 + 1> wasPressed;
    inline static MouseState                mouse;
};

// ------------------------------------------------------------------------------------------------

inline bool Mouse::ButtonPressed(MouseButton button)
{
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button) ? true : wasPressed[button] = false;
}

// ------------------------------------------------------------------------------------------------

inline bool Mouse::ButtonDown(MouseButton button)
{
    if (ButtonPressed(button) && !wasPressed[button])
        return wasPressed[button] = true;

    return false;
}

// ------------------------------------------------------------------------------------------------

inline const Vector2i& Mouse::Position()
{
    SDL_GetMouseState(&mouse.position.x, &mouse.position.y);
    return mouse.position;
}

// ------------------------------------------------------------------------------------------------

inline const Mouse::MouseState& Mouse::Position(const Rect& viewport)
{
    Position();
    mouse.position.x -= viewport.x;
    mouse.position.y -= viewport.y;
    mouse.isInViewport = (
        mouse.position.x >= 0 && mouse.position.x < viewport.w &&
        mouse.position.y >= 0 && mouse.position.y < viewport.h);
    return mouse;
}

// ------------------------------------------------------------------------------------------------

inline void Mouse::Position(float x, float y)
{
    SDL_WarpMouseInWindow(nullptr, int(x), int(y));
}

// ------------------------------------------------------------------------------------------------

#endif
