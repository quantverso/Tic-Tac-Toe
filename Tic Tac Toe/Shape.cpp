#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Point.h"
#include "Polygon.h"

//--------------------------------------------------------------------------------------------------

Shape::Shape() :
    color{ Color::White }
{
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Rectangle* rect, const Circle* circle) const
{
    // Encontra o ponto mais pr�ximo ao c�rculo dentro do ret�ngulo
    float closestX{ std::max(float(rect->bounds.Left()), std::min(circle->position.x, float(rect->bounds.Right()))) };
    float closestY{ std::max(float(rect->bounds.Top()), std::min(circle->position.y, float(rect->bounds.Bottom()))) };

    // Calcula a dist�ncia entre o centro do c�rculo e o ponto mais pr�ximo
    float distanceX{ circle->position.x - closestX };
    float distanceY{ circle->position.y - closestY };

    // Se a dist�ncia for menor ou igual ao raio, h� colis�o
    return (distanceX * distanceX + distanceY * distanceY) <= (circle->Radius() * circle->Radius());
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Rectangle* rect, const Point* point) const
{
    if (point->position.x < rect->bounds.Left() || rect->bounds.Right() < point->position.x)
        return false;
    if (point->position.y < rect->bounds.Top() || rect->bounds.Bottom() < point->position.y)
        return false;
    return true;
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Rectangle* rect, const Polygon* polygon) const
{
	return false;
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Circle* circle, const Point* point) const
{
    // Calcula a dist�ncia entre o ponto e o centro do c�rculo
    float dx{ point->position.x - circle->position.x };
    float dy{ point->position.y - circle->position.y };

    // Se a dist�ncia for menor ou igual ao raio, h� colis�o
    return (dx * dx + dy * dy) <= (circle->Radius() * circle->Radius());
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Circle* circle, const Polygon* polygon) const
{
	return false;
}

//--------------------------------------------------------------------------------------------------

bool Shape::CheckCollision(const Point* point, const Polygon* polygon) const
{
    bool crossing{};
    const auto& vertices{ *polygon };

    for (size_t i{}, j{ 1 }; j < polygon->Size(); i++, j++)
    {
        // Condi��o para a interse��o
        if ((vertices[i].y < point->position.y && vertices[j].y >= point->position.y) ||
            (vertices[j].y < point->position.y && vertices[i].y >= point->position.y)) 
        {
            // Calcula a interse��o
            float intersectX
            {
                vertices[j].x -
                (vertices[j].y - point->position.y) *
                (vertices[j].x - vertices[i].x) /
                (vertices[j].y - vertices[i].y)
            };

            // Verifica se o ponto est� � esquerda da linha
            if (intersectX < point->position.x)
                crossing = !crossing;
        }
    }

    return crossing;
}

//--------------------------------------------------------------------------------------------------
