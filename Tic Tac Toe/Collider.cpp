#include "Collider.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"
#include "Point.h"

// ---------------------------------------------------------------------------------------------------------------------

Collider::Collider(Entity* entity, Type type) :
    Component{ entity },
    type{ type },
    standard{},
    OnCollision{}
{
    // Atribui o próprio endereço ao ponteiro no componente transform
    BindDependencies(this);    

    // Coloca o endereço deste colisor na lista de colisores
    colliders->push_back(this);

    //Cria um delimitador de colisão padrão
    Add(std::make_unique<Rectangle>());
    standard = true;
    
}

// ---------------------------------------------------------------------------------------------------------------------

Collider::~Collider()
{
    colliders->remove(this);
}

// ---------------------------------------------------------------------------------------------------------------------

void Collider::Draw()
{
    for (const auto& b : boundings)
    {
        window.Draw(b.get());
    }
}


//--------------------------------------------------------------------------------------------------

void Collider::Position(float x, float y)
{
    for (const auto& b : boundings)
    {
        b->Position(x, y);
    }
}

// ---------------------------------------------------------------------------------------------------------------------

Shape* Collider::Add(std::unique_ptr<Shape> shape)
{
    // Remove delimitador de colisão padrão
    if (standard)
    {
        boundings.clear();
        standard = false;
    }

    // Transfere a propriedade do shape para boundings
    boundings.push_back(std::move(shape));

    auto b{ boundings.back().get()};

    // Cor do desenho geométrico do delimitador
    b->Color(Color::Magenta);

    // Define a posição do delimitador de colisão
    b->Position(float(entity->transform.bounds.Left()), float(entity->transform.bounds.Top()));

    // Ajustes de formas simples
    if (auto circle{ dynamic_cast<Circle*>(b) })
    {
        circle->Radius(entity->transform.Size().width / 2);
        circle->Position(entity->transform.Position().x + circle->Radius(), entity->transform.Position().y + circle->Radius());
    }
    else
    {
        b->Position(float(entity->transform.bounds.Left()), float(entity->transform.bounds.Top()));
        if (auto rect{ dynamic_cast<Rectangle*>(b) })
            rect->Size(entity->transform.Size().width, entity->transform.Size().height);
    }

    return b;
}

// ---------------------------------------------------------------------------------------------------------------------

void Collider::Update()
{
    if (type == Active)
    {
        for (const auto& other : *colliders) // Percorre os colisores existentes
        {
            if (other != this && // Se o colisor for diferente deste
                collided.find(other) == collided.end()) // e não colidiu com este
            {
                if (this->IsColliding(other))
                {
                    // Chama os métodos de colisão dos objetos envolvidos
                    (this->entity->*OnCollision)(*other->entity);
                    (other->entity->*OnCollision)(*this->entity);

                    // Marca o colisor atual como colidido no set do outro colisor
                    other->collided.insert(this);
                }
            }
        }
        collided.clear();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

inline bool Collider::IsColliding(const Collider* other)
{
    for (const auto& first : this->boundings)
    {
        for (const auto& second : other->boundings)
        {
            if (first->CheckCollision(second.get()))
                return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------
