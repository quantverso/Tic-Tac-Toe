#ifndef QUANTVERSO_ENTITY_H
#define QUANTVERSO_ENTITY_H

//--------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Material.h"
#include "Transform.h"
#include "Collider.h"
#include "Animation.h"
#include "Sound.h"
#include "Texture.h"
#include "Text.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Point.h"
#include "Polygon.h"
#include <vector>
#include <list>
#include <unordered_map>
#include <memory>
#include <typeindex>

using ComponentsMap = std::unordered_map<std::type_index, std::unique_ptr<Component>>;

class Scene;

//--------------------------------------------------------------------------------------------------

class Entity
{
public:
    const std::string& id;      ///< Identifica��o �nica do objeto
    const std::string& tag;     ///< Tag para agrupar o objeto
    Scene* const&      scene;   ///< Referencia para a cena
    bool               visible; ///< Controla a visibilidade do objeto

    ////////////////////////////////////////////////////////////
    /// \brief Cosntrutor padr�o.
    /// 
    ////////////////////////////////////////////////////////////
    Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Destrutor virtual.
    /// 
    ////////////////////////////////////////////////////////////
    virtual ~Entity();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado a cada frame para desenhar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Draw();

    ////////////////////////////////////////////////////////////
    /// \brief Define a tag associada ao objeto.
    ///
    /// A tag � uma string que pode ser usada para agrupar ou identificar
    /// objetos, permitindo a categoriza��o de m�ltiplos objetos sob a mesma tag.
    /// Ao contr�rio do ID, que � �nico para cada objeto,
    /// a mesma tag pode ser compartilhada entre v�rios objetos.
    ///
    /// \param tag A string contendo a nova tag do objeto. Se for
    /// nullptr ou uma string vazia, a tag do objeto ser� removida
    /// ou resetada para o valor padr�o.
    ///
    ////////////////////////////////////////////////////////////
    void Tag(const char* tag);

    ////////////////////////////////////////////////////////////
    /// \brief Destr�i esta entidade.
    ///
    /// Este m�todo remove e destr�i a entidade do sistema. Coloca
    /// a entidade num vetor para destrui��o ao termino do processamento
    /// de todas entidades instanciadas, liberando os recursos alocados.
    /// Ap�s a destrui��o, a entidade n�o pode mais ser usada.
    ///
    ////////////////////////////////////////////////////////////
    void Destroy();

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um componente � entidade.
    ///
    /// Este m�todo cria e adiciona um novo componente do tipo `T` 
    /// � entidade, passando os argumentos fornecidos para o
    /// construtor do componente. A entidade � associada ao componente.
    ///
    /// \tparam Args Tipos dos argumentos a serem passados para o construtor do componente.
    /// 
    /// \return Um ponteiro para o componente rec�m-adicionado.
    ///
    ////////////////////////////////////////////////////////////
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);

    ////////////////////////////////////////////////////////////
    /// \brief Obt�m um componente da entidade atual.
    ///
    /// Este m�todo recupera um componente do tipo `T` associado � 
    /// entidade atual.
    ///
    /// \tparam T O tipo de componente a ser obtido.
    /// 
    /// \return Um ponteiro para o componente solicitado.
    ///
    ////////////////////////////////////////////////////////////
    template<typename T>
    T* GetComponent();

protected:
    static Window& window;    ///< Referencia para a janela gr�fica.
    static float&  deltaTime; ///< Tempo decorrido entre frames

private:
    friend class Component;
	friend class Scene;

	std::string                   id_;        ///< Nome do objeto na hash
	std::string                   tag_;       ///< Tag para agrupar o objeto
    Scene*                        scene_;     ///< Referencia interna para a cena
    ComponentsMap                 components; ///< Hash de components
	std::list<Entity*>*			  objects;    ///< Guarda objetos do tipo Entity
	std::list<Entity*>::iterator* current;    ///< Iterador para o objeto atual
	std::vector<Entity*>*		  destroy;	  ///< Vetor de objetos a serem destruidos (ao final do frame)

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza todos os componentes da classe.
    /// 
    /// M�todo para atualizar o estado dos componentes.
    /// � chamado logo ap�s o Update dos Objetos.
    /// 
    ////////////////////////////////////////////////////////////
    void UpdateComponents();

    ////////////////////////////////////////////////////////////
    /// \brief Desenha todos os componentes da entidade.
    /// 
    /// M�todo para desenhar os componentes do objeto.
    /// � chamado logo ap�s o Draw dos Objetos.
    /// 
    ////////////////////////////////////////////////////////////
    void DrawComponents();

    ////////////////////////////////////////////////////////////
    /// \brief Inicializa objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado uma vez no mesmo frame em que o objeto
    /// � instanciado, logo ap�s sua vari�vel `scene` ser inicializada.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Awake() {};

    ////////////////////////////////////////////////////////////
    /// \brief Inicializa objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado uma vez no pr�ximo frame ap�s a
    /// cria��o do objeto.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Start() {};

    ////////////////////////////////////////////////////////////
    /// \brief Atualiza objetos derivados desta classe.
    /// 
    /// M�todo virtual chamado a cada frame para atualizar objetos.
    /// Deve ser implementado pelas classes derivadas.
    /// 
    ////////////////////////////////////////////////////////////
    virtual void Update() {};

    ////////////////////////////////////////////////////////////
    /// \brief Lida com colis�es entre esta entidade e outra.
    ///
    /// Este m�todo virtual � chamado automaticamente quando h� uma
    /// colis�o entre esta entidade e outra entidade do jogo. Pode ser
    /// sobrescrito nas classes derivadas para implementar comportamentos
    /// espec�ficos de colis�o.
    /// 
    /// \param obj Uma refer�ncia para a entidade que colidiu com esta.
    ///
    ////////////////////////////////////////////////////////////
    virtual void OnCollision(Entity& obj) {};

public:	
	Material&  material;
    Transform& transform;
};

//--------------------------------------------------------------------------------------------------

inline void Entity::Tag(const char* tag)
{
    tag_ = tag;
}

// ------------------------------------------------------------------------------------------------

inline void Entity::Draw()
{    
    if (material.texture)
        window.Draw(
            material.texture.get(),
            &material,
            &transform,
            transform.angle.degrees,
            &transform.offset
        );
}

// ------------------------------------------------------------------------------------------------

inline void Entity::Destroy()
{
    destroy->push_back(this);
}

// ------------------------------------------------------------------------------------------------

template<typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    auto component{ std::make_unique<T>(this, std::forward<Args>(args)...) };
    T* componentPtr{ component.get() };
    components[typeid(T)] = std::move(component);
    return componentPtr;
}

// ------------------------------------------------------------------------------------------------

template<typename T>
T* Entity::GetComponent()
{
    auto it{ components.find(std::type_index(typeid(T))) };
    if (it != components.end())
        return static_cast<T*>(it->second.get());
    return nullptr;
}

// ------------------------------------------------------------------------------------------------

#endif
