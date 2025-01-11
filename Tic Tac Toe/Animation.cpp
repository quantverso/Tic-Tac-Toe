#include "Animation.h"
#include "Entity.h"

// ---------------------------------------------------------------------------------------------------------------------

Animation::Animation(Entity* entity, const char* file) :
    Component{ entity }
{
    entity->material.Add(file);
}

// ---------------------------------------------------------------------------------------------------------------------

Animation::Animation(Entity* entity, Texture* texture) :
    Component{ entity }
{
    entity->material.Add(texture);
}

// ---------------------------------------------------------------------------------------------------------------------

void Animation::Add(unsigned id, std::vector<Rect> sequence, bool loop, bool continuous)
{
    rectMap[id] = { sequence, continuous, loop };
    entity->material.Rect(*sequence.begin());
    entity->transform.Size(float(sequence.begin()->w), float(sequence.begin()->h));
}

// ---------------------------------------------------------------------------------------------------------------------

void Animation::Add(unsigned id, Rect sequence)
{
    Add(id, std::vector<Rect>{ sequence }, false, false);
}

// ---------------------------------------------------------------------------------------------------------------------

bool Animation::Run(unsigned id, float frameTime)
{
    elapsedTime += clock.ElapsedTime();

    if (currentId != id)
    {
        auto sequence{ rectMap.find(id) };

        if (sequence != rectMap.end())
        {
            selected = &sequence->second;
            currentId = id;

            // Se for só um quadro, definição ocorre somente uma vez
            if (selected->sequence.size() == 1)
            {
                entity->material.Rect(selected->sequence[0]);
                index = -1;
                return false;
            }

            // Reinicia o índice dependendo da continuidade da animação
            if (!selected->continuous || selected->sequence.size() <= lastIndex)
                index = 0;
            else
                index = lastIndex;

            auto& rect{ selected->sequence[index % selected->sequence.size()] };
            entity->material.Rect(rect);
            entity->transform.Size(float(rect.w), float(rect.h));
        }
        else
        {
            std::cerr << "ID da animacao invalido!\n";
            return true;
        }
    }

    if (index >= 0)
    {
        if (elapsedTime * 1000 >= frameTime)
        {
            if (index >= selected->sequence.size())
            {
                if (selected->loop) // Reseta o indíce se estiver em loop
                    index = 0;
                else
                    return true; // Retorna true se não estiver em loop e chegar ao último quadro
            }

            if (index < selected->sequence.size())
            {
                entity->material.Rect(selected->sequence[index++]);

                // Salva o último índice se a animação for contínua
                if (selected->continuous)
                    lastIndex = index;

                elapsedTime = 0;
            }
        }
    }

    return false;
}

// ---------------------------------------------------------------------------------------------------------------------
