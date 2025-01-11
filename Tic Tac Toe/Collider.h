#ifndef QUANTVERSO_COLLIDER_H
#define QUANTVERSO_COLLIDER_H

// ---------------------------------------------------------------------------------------------------------------------

#include "Component.h"
#include <vector>
#include <unordered_set>
#include <memory>

class Entity;
class Shape;

// ---------------------------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Collider
/// \brief Responsável por gerenciar colisores e detectar colisões entre objetos.
///
/// A classe Collider mantém e gerencia os objetos com delimitadores de colisão, permitindo
/// a verificação de colisões entre diferentes tipos de objetos (estáticos ou móveis) e a
/// interação entre suas formas geométricas.
/// 
////////////////////////////////////////////////////////////
class Collider : public Component
{
public:
    ////////////////////////////////////////////////////////////
    /// \enum Type
    /// \brief Define o tipo de colisor: Ativo ou Passivo.
    ///
    /// O enum Type classifica os tipos de colisores em ativos ou passivos.
    /// - Um **colisor ativo** deve ser utilizado em objetos dinâmicos que
    ///   causam colisões com outros objetos.
    /// - Um **colisor passivo** é apropriado para objetos estáticos que
    ///   não iniciam colisões, mas podem ser atingidos por colisores ativos.
    ///
    /// Esses tipos ajudam a otimizar o comportamento da simulação de colisão,
    /// diferenciando entre objetos que interagem ativamente e os que permanecem
    /// inertes no cenário.
    ///
    ////////////////////////////////////////////////////////////
    enum Type
    {
        Active,  ///< Colisor ativo: usado em objetos móveis que causam colisão.
        Passive  ///< Colisor passivo: usado em objetos estáticos que não causam colisão.
    };

    ////////////////////////////////////////////////////////////
    /// \brief Construtor da classe `Collider`.
    ///
    /// Inicializa o colisor com a entidade associada e define o tipo (estático ou móvel).
    ///
    /// \param entity Ponteiro para a entidade associada.
    /// \param type Tipo do colisor (Static ou Moving).
    /// 
    ////////////////////////////////////////////////////////////
    Collider(Entity* entity, Type type);

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor da classe `Collider`.
    ///
    /// Libera recursos associados ao colisor.
    /// 
    ////////////////////////////////////////////////////////////
    ~Collider();
    
    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um delimitador de colisão.
    ///
    /// \tparam T A forma geométrica a ser adicionada ao colisor.
    /// 
    /// \return Um ponteiro para a forma recém-adicionada.
    /// 
    ////////////////////////////////////////////////////////////
    template <typename T, typename... Args>
    T* Add(Args&&... args);

    template <typename T>
    T* Add(std::initializer_list<SDL_Point> list);

private:
    friend class Component;

    Type                                type;      ///< Tipo de colisor (Active, Passive)
    std::unordered_set<Collider*>       collided;  ///< Armazena colisores que colidiram com este
    std::vector<std::unique_ptr<Shape>> boundings; ///< Vetor de delimitadores de colisão
    std::list<Collider*>*               colliders; ///< Lista com todos colisores instanciados
    bool                                standard;  ///< Indica se o delimitador de colisão é padrão    

    ////////////////////////////////////////////////////////////
    /// \brief Lida com colisões a entidade deste colisor e outra.
    ///
    /// Este método virtual é chamado quando há uma colisão entre
    /// a entidade deste colisor e outra entidade do jogo.
    /// 
    /// \param obj Uma referência para a entidade colidida.
    ///
    ////////////////////////////////////////////////////////////
    void (Entity::* OnCollision)(Entity&);

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza o estado do colisor.
    ///
    /// Executa operações necessárias para atualizar a lógica de colisão e interações.
    ///
    ////////////////////////////////////////////////////////////
    void Update();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha os delimitadores de colisão.
    ///
    /// Se `visible` for true, desenha visualmente os colisores.
    /// 
    ////////////////////////////////////////////////////////////
    void Draw();

    ////////////////////////////////////////////////////////////
    /// \brief Posiciona os delimitadores de colisão.
    ///
    /// Este metodo posiciona todos os delimitadores de colisão
    /// com base nos valores informados em x e y.
    /// 
    /// \param x Posição no eixo x para os delimitadores.
    /// \param y Posição no eixo y para os delimitadores.
    /// 
    ////////////////////////////////////////////////////////////
    void Position(float x, float y);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um delimitador de colisão.
    ///
    /// \param geometry Forma geométrica do delimitador (Rectangle, Circle, etc.).
    /// \param offsetX Deslocamento horizontal opcional.
    /// \param offsetY Deslocamento vertical opcional.
    /// 
    ////////////////////////////////////////////////////////////
    Shape* Add(std::unique_ptr<Shape> shape);

    ////////////////////////////////////////////////////////////
    /// \brief Verifica se há colisão entre dois conjuntos de delimitadores.
    ///
    /// Este método percorre dois conjuntos de delimitadores (`Bounding`),
    /// comparando cada delimitador de um conjunto com cada delimitador do outro.
    /// Para cada par de delimitadores, chama internamente o método `CheckCollision()`,
    /// que realiza a verificação real da colisão entre dois delimitadores.
    ///
    /// \param boundings Um par de vetores contendo os delimitadores de colisão:
    /// - O primeiro vetor representa os delimitadores do primeiro objeto.
    /// - O segundo vetor representa os delimitadores do segundo objeto.
    ///
    /// \return Retorna `true` se qualquer par de delimitadores de objetos distintos
    /// estiver colidindo, caso contrário, retorna `false`.
    /// 
    ////////////////////////////////////////////////////////////
    bool IsColliding(const Collider* other);
};

// ---------------------------------------------------------------------------------------------------------------------

template<typename T, typename ...Args>
inline T* Collider::Add(Args && ...args)
{
    return dynamic_cast<T*>(Add(std::make_unique<T>(std::forward<Args>(args)...)));
}

// ---------------------------------------------------------------------------------------------------------------------

template<typename T>
inline T* Collider::Add(std::initializer_list<SDL_Point> list)
{
    return dynamic_cast<T*>(Add(std::make_unique<T>(list)));
}

// ---------------------------------------------------------------------------------------------------------------------

#endif
