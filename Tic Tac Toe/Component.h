#ifndef QUANTVERSO_COMPONENT_H
#define QUANTVERSO_COMPONENT_H

//--------------------------------------------------------------------------------------------------

#include "Engine.h"

//--------------------------------------------------------------------------------------------------

class Entity;
class Transform;
class Collider;

//--------------------------------------------------------------------------------------------------

class Component
{
public:
	bool visible; ///< Controla a visibilidade dos componentes

	Component(Entity*& entity);
	virtual ~Component() = default;

protected:
	static Window& window; ///< Referência para a janela gráfica

	Entity* const entity; ///< Entidade a qual pertence o componente
	Scene* const& scene;  ///< Referência para a cena

	////////////////////////////////////////////////////////////
	/// \brief Vincula dependências entre componentes derivados.
	///
	/// Este método estabelece as dependências necessárias entre
	/// componentes de uma entidade, permitindo que um componente A 
	/// tenha acesso a métodos e atributos privados de outro componente B.
	/// Deve ser chamado explicitamente no construtor da classe derivada 
	/// que necessita dessas dependências.
	///
	/// O método utiliza a função \c typeid para verificar o tipo do componente
	/// e realizar o casting adequado para ajustar as referências e ponteiros
	/// às dependências necessárias.
	///
	/// \param component Ponteiro para o componente derivado que precisa
	///        ter suas dependências configuradas.
	///
	////////////////////////////////////////////////////////////
	void BindDependencies(Transform* transform);
	void BindDependencies(Collider* collider);

private:
	friend class Entity;	

	virtual void Update() {};
	virtual void Draw() {};
};

//--------------------------------------------------------------------------------------------------

#endif
