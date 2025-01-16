#ifndef QUANTVERSO_ANIMATION_H
#define QUANTVERSO_ANIMATION_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Component.h"
#include "Clock.h"
#include <vector>
#include <unordered_map>

////////////////////////////////////////////////////////////
/// \class Animation
/// \brief Classe respons�vel por gerenciar anima��es para uma entidade.
/// 
/// A classe Animation permite a cria��o, adi��o e execu��o de anima��es
/// baseadas em uma sequ�ncia de ret�ngulos de textura (frames).
/// As anima��es podem ser cont�nuas (para movimentos de personagens por exemplo)
/// ou incont�nuas (para anima��es independentes de outras anima��es).
///
////////////////////////////////////////////////////////////
class Animation : public Component
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe Animation.
    /// 
    /// Este construtor carrega uma textura a partir de um arquivo e
    /// associa � entidade a qual a anima��o pertence.
    /// 
    /// \param entity Ponteiro para a entidade dona da anima��o.
    /// \param fileName Caminho para o arquivo de textura a ser carregado.
    /// 
    ////////////////////////////////////////////////////////////
    Animation(Entity* entity, const char* file);

    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe Animation usando uma textura existente.
    /// 
    /// Associa uma textura j� existente a uma anima��o da entidade.
    /// 
    /// \param entity Ponteiro para a entidade dona da anima��o.
    /// \param tileSet Refer�ncia para uma textura j� carregada.
    /// 
    ////////////////////////////////////////////////////////////
    Animation(Entity* entity, Texture* tileSet);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona uma nova anima��o � lista de anima��es.
    ///
    /// Associa um ID a uma sequ�ncia de quadros (IntRect) que definem a
    /// anima��o. A anima��o pode ser cont�nua ou n�o.
    /// 
    /// \param id ID �nico para a anima��o.
    /// \param sequence Vetor de coordenadas de ret�ngulos de textura que representam os frames.
    /// \param loop Define se a anima��o deve rodar em loop.
    /// \param continuous Define se a anima��o deve continuar do mesmo �ndice ao mudar de ID.
    /// 
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, std::vector<Rect> sequence, bool loop, bool continuous);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um quadro � lista de anima��es.
    ///
    /// Associa um ID a um quadro (IntRect) que define a anima��o.
    /// 
    /// \param id ID �nico para a anima��o.
    /// \param sequence Coordenadas do ret�ngulo da textura que representa o frame.
    /// 
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, Rect sequence);

    ////////////////////////////////////////////////////////////
    /// \brief Executa uma anima��o baseada no ID fornecido.
    /// 
    /// Controla o fluxo da anima��o, alterando os quadros com base no tempo de frame.
    ///
    /// \param id ID da anima��o a ser executada.
    /// \param frameTime Tempo entre os quadros, em milissegundos. O padr�o � 0.
    /// \return Retorna true se a anima��o n�o estiver em loop e chegar ao �ltimo quadro.
    /// 
    ////////////////////////////////////////////////////////////
    bool Run(unsigned id, float frameTime);

private:
    ////////////////////////////////////////////////////////////
    /// \struct RectCoords
    /// \brief Estrutura que armazena a sequ�ncia de frames e o estado de uma anima��o.
    /// 
    ////////////////////////////////////////////////////////////
    struct RectCoords
    {
        std::vector<Rect> sequence;     ///< Vetor de coodenadas de ret�ngulos que representam os quadros.
        bool              continuous{}; ///< Define se a anima��o � cont�nua.
        bool              loop{};       ///< Define se a anima��o est� em loop.
    };

    using RectMap = std::unordered_map<unsigned, RectCoords>; ///< Mapa de anima��es.

    RectMap     rectMap;     ///< Mapa de anima��es associadas a IDs.
    RectCoords* selected{};  ///< Ponteiro para a anima��o atualmente selecionada.
    int         index{};     ///< �ndice do quadro atual.
    unsigned    lastIndex{}; ///< �ltimo �ndice usado (para anima��es cont�nuas).
    unsigned    currentId{ std::numeric_limits<unsigned>::max() }; ///< ID da anima��o atual.

    Clock clock;         ///< Rel�gio para controle do tempo de execu��o.
    float elapsedTime{}; ///< Tempo decorrido desde o �ltimo frame.
};

// ---------------------------------------------------------------------------------------------------------------------

#endif
