#include "Rectangle.h"

//--------------------------------------------------------------------------------------------------

Rectangle::Rectangle(Fill fill) :
    Rect{ 0, 0, 100, 100 },
    fill{ bool(fill) },
    bounds{ this },
    size{ 100, 100 },
    offset{}
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
