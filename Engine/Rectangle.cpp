#include "Rectangle.h"

//--------------------------------------------------------------------------------------------------

Rectangle::Rectangle(Fill fill) :
    Rect{ 0, 0, 100, 100 },
    bounds{ this },
    m_Fill{ fill },
    m_Size{ 100, 100 },
    m_Offset{}
{
	Refresh();
}

//--------------------------------------------------------------------------------------------------

bool Rectangle::CheckCollision(const Rectangle* other) const
{
    if (this->bounds.Right() < other->bounds.Left() || other->bounds.Right() < this->bounds.Left())
        return false;

    if (this->bounds.Bottom() < other->bounds.Top() || other->bounds.Bottom() < this->bounds.Top())
        return false;

    return true;
}

//--------------------------------------------------------------------------------------------------
