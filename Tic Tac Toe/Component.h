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
	static Window& window; ///< Refer�ncia para a janela gr�fica

	Entity* const entity; ///< Entidade a qual pertence o componente
	Scene* const& scene;  ///< Refer�ncia para a cena

	////////////////////////////////////////////////////////////
	/// \brief Vincula depend�ncias entre componentes derivados.
	///
	/// Este m�todo estabelece as depend�ncias necess�rias entre
	/// componentes de uma entidade, permitindo que um componente A 
	/// tenha acesso a m�todos e atributos privados de outro componente B.
	/// Deve ser chamado explicitamente no construtor da classe derivada 
	/// que necessita dessas depend�ncias.
	///
	/// O m�todo utiliza a fun��o \c typeid para verificar o tipo do componente
	/// e realizar o casting adequado para ajustar as refer�ncias e ponteiros
	/// �s depend�ncias necess�rias.
	///
	/// \param component Ponteiro para o componente derivado que precisa
	///        ter suas depend�ncias configuradas.
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
