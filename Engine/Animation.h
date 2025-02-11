#ifndef QUANTVERSO_ANIMATION_H
#define QUANTVERSO_ANIMATION_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Component.h"
#include "Clock.h"
#include <vector>
#include <unordered_map>

////////////////////////////////////////////////////////////
/// \class Animation
/// 
/// \brief Classe responsável por gerenciar animações para uma entidade.
/// 
/// A classe Animation permite a criação, adição e execução de animações
/// baseadas em uma sequência de retângulos de textura (frames).
/// As animações podem ser contínuas (para movimentos de personagens por exemplo)
/// ou incontínuas (para animações independentes de outras animações).
///
////////////////////////////////////////////////////////////
class Animation : public Component
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe Animation.
    /// 
    /// Este construtor carrega uma textura a partir de um arquivo e
    /// associa à entidade a qual a animação pertence.
    /// 
    /// \param entity Ponteiro para a entidade proprietária da animação.
    /// \param fileName Caminho para o arquivo de textura a ser carregado.
    /// 
    ////////////////////////////////////////////////////////////
    Animation(Entity* entity, const char* file);

    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe Animation usando uma textura existente.
    /// 
    /// Associa uma textura já existente a uma animação da entidade.
    /// 
    /// \param entity Ponteiro para a entidade proprietária da animação.
    /// \param tileSet Referência para uma textura já carregada.
    /// 
    ////////////////////////////////////////////////////////////
    Animation(Entity* entity, Texture* tileSet);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona uma nova animação à lista de animações.
    ///
    /// Associa um ID a uma sequência de quadros (IntRect) que definem a
    /// animação. A animação pode ser contínua ou não.
    /// 
    /// \param id ID único para a animação.
    /// \param sequence Vetor de coordenadas de retângulos de textura que representam os quadros da animação.
    /// \param loop Define se a animação deve rodar em loop.
    /// \param continuous Define se a animação deve continuar do mesmo quadro (index) ao mudar de ID.
    /// 
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, std::vector<Rect> sequence, bool loop, bool continuous);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um quadro à lista de animações.
    ///
    /// Associa um ID a um quadro (IntRect) que define a animação.
    /// 
    /// \param id ID único para a animação.
    /// \param sequence Coordenadas do retângulo da textura que representa o frame.
    /// 
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, Rect rect);

    ////////////////////////////////////////////////////////////
    /// \brief Executa uma animação baseada no ID fornecido.
    /// 
    /// Controla o fluxo da animação, alterando os quadros com base no tempo de frame.
    ///
    /// \param id ID da animação a ser executada.
    /// \param frameTime Tempo entre os quadros, em milissegundos. O padrão é 0.
    /// 
    /// \return Retorna false se a animação não estiver em loop e chegar ao último quadro.
    /// 
    ////////////////////////////////////////////////////////////
    bool Run(unsigned id, float frameTime);

private:
    ////////////////////////////////////////////////////////////
    /// \struct RectCoords
    /// 
    /// \brief Vetor de coordenadas de retângulos que representam os quadros (Rect).
    /// 
    /// Esta estrutura armazena a sequência de áreas de um TileSet que serão os quadros
    /// da animação e configurações de reprodução da animação.
    /// 
    ////////////////////////////////////////////////////////////
    struct RectVector : std::vector<Rect>
    {
        bool continuous; ///< Define se a animação é contínua.
        bool loop;       ///< Define se a animação está em loop.

        RectVector(std::vector<Rect>&& sequence, bool continuous, bool loop) :
            std::vector<Rect>{ std::move(sequence) },
            continuous{ continuous },
            loop{ loop }
        {
        }
    };

    std::unordered_map<unsigned, RectVector> m_RectMap; ///< Mapa de animações associadas a IDs.
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
