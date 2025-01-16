#ifndef QUANTVERSO_ANIMATION_H
#define QUANTVERSO_ANIMATION_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Component.h"
#include "Clock.h"
#include <vector>
#include <unordered_map>

////////////////////////////////////////////////////////////
/// \class Animation
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
    /// \param entity Ponteiro para a entidade dona da animação.
    /// \param fileName Caminho para o arquivo de textura a ser carregado.
    /// 
    ////////////////////////////////////////////////////////////
    Animation(Entity* entity, const char* file);

    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe Animation usando uma textura existente.
    /// 
    /// Associa uma textura já existente a uma animação da entidade.
    /// 
    /// \param entity Ponteiro para a entidade dona da animação.
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
    /// \param sequence Vetor de coordenadas de retângulos de textura que representam os frames.
    /// \param loop Define se a animação deve rodar em loop.
    /// \param continuous Define se a animação deve continuar do mesmo índice ao mudar de ID.
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
    void Add(unsigned id, Rect sequence);

    ////////////////////////////////////////////////////////////
    /// \brief Executa uma animação baseada no ID fornecido.
    /// 
    /// Controla o fluxo da animação, alterando os quadros com base no tempo de frame.
    ///
    /// \param id ID da animação a ser executada.
    /// \param frameTime Tempo entre os quadros, em milissegundos. O padrão é 0.
    /// \return Retorna true se a animação não estiver em loop e chegar ao último quadro.
    /// 
    ////////////////////////////////////////////////////////////
    bool Run(unsigned id, float frameTime);

private:
    ////////////////////////////////////////////////////////////
    /// \struct RectCoords
    /// \brief Estrutura que armazena a sequência de frames e o estado de uma animação.
    /// 
    ////////////////////////////////////////////////////////////
    struct RectCoords
    {
        std::vector<Rect> sequence;     ///< Vetor de coodenadas de retângulos que representam os quadros.
        bool              continuous{}; ///< Define se a animação é contínua.
        bool              loop{};       ///< Define se a animação está em loop.
    };

    using RectMap = std::unordered_map<unsigned, RectCoords>; ///< Mapa de animações.

    RectMap     rectMap;     ///< Mapa de animações associadas a IDs.
    RectCoords* selected{};  ///< Ponteiro para a animação atualmente selecionada.
    int         index{};     ///< Índice do quadro atual.
    unsigned    lastIndex{}; ///< Último índice usado (para animações contínuas).
    unsigned    currentId{ std::numeric_limits<unsigned>::max() }; ///< ID da animação atual.

    Clock clock;         ///< Relógio para controle do tempo de execução.
    float elapsedTime{}; ///< Tempo decorrido desde o último frame.
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
