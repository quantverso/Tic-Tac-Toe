#include "Collider.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Polygon.h"
#include "Point.h"

// ---------------------------------------------------------------------------------------------------------------------

Collider::Collider(Entity* entity, Type type) :
    Component{ entity },
    m_Type{ type },
    m_Standard{}
{
    // Atribui os endereços aos membros de dependências externas
    entity->transform.m_Collider = this;
    entity->transform.m_PositionCollider = &Collider::Position;

    // Entra na lista de colisores
    GetSceneColliders().push_back(this);

    //Cria um delimitador de colisão padrão
    Add(std::make_unique<Rectangle>());
    m_Standard = true;   
}

// ---------------------------------------------------------------------------------------------------------------------

Collider::~Collider()
{
    GetSceneColliders().remove(this);
}

// ---------------------------------------------------------------------------------------------------------------------

void Collider::Draw()
{
    for (const auto& b : m_Boundings)
        Engine::window.Draw(b.get());
}


//--------------------------------------------------------------------------------------------------

void Collider::Position(float x, float y)
{
    for (const auto& b : m_Boundings)
        b->Position(x, y);
}

// ---------------------------------------------------------------------------------------------------------------------

Shape* Collider::Add(std::unique_ptr<Shape> shape)
{
    // Remove delimitador de colisão padrão
    if (m_Standard)
    {
        m_Boundings.clear();
        m_Standard = false;
    }

    // Transfere a propriedade do shape para boundings
    m_Boundings.push_back(std::move(shape));

    auto b{ m_Boundings.back().get()};

    // Cor do desenho geométrico do delimitador
    b->SetColor(Color::Magenta);

    // Define a posição do delimitador de colisão
    b->Position(float(entity->transform.bounds.Left()), float(entity->transform.bounds.Top()));

    // Ajustes de formas simples
    if (auto circle{ dynamic_cast<Circle*>(b) })
    {
        circle->SetRadius(entity->transform.GetSize().width / 2);
        circle->Position(entity->transform.Position().x + circle->GetRadius(), entity->transform.Position().y + circle->GetRadius());
    }
    else
    {
        b->Position(float(entity->transform.bounds.Left()), float(entity->transform.bounds.Top()));
        if (auto rect{ dynamic_cast<Rectangle*>(b) })
            rect->SetSize(entity->transform.GetSize().width, entity->transform.GetSize().height);
    }

    return b;
}

// ---------------------------------------------------------------------------------------------------------------------

void Collider::Update()
{
    if (m_Type == Active)
    {
        for (const auto& other : GetSceneColliders()) // Percorre os colisores existentes
        {
            // Se o colisor for diferente deste e não colidiu com este
            if (other != this && m_Collided.find(other) == m_Collided.end())
            {
                if (this->IsColliding(other))
                {
                    // Chama os métodos de colisão dos objetos envolvidos
                    this->entity->OnCollision(*other->entity);
                    other->entity->OnCollision(*this->entity);

                    // Marca o colisor atual como colidido no set do outro colisor
                    other->m_Collided.insert(this);
                }
            }
        }
        m_Collided.clear();
    }
}

// ---------------------------------------------------------------------------------------------------------------------

inline bool Collider::IsColliding(const Collider* other)
{
    for (const auto& first : this->m_Boundings)
    {
        for (const auto& second : other->m_Boundings)
        {
            if (first->CheckCollision(second.get()))
                return true;
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------
