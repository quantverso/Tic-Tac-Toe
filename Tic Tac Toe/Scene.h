#ifndef QUANTVERSO_SCENE_H
#define QUANTVERSO_SCENE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"
#include "Texture.h"
#include "Music.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Point.h"
#include "Polygon.h"
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>

class Entity;
class Collider;

using ObjectsMap = std::unordered_map<std::string, Entity*>;

// ------------------------------------------------------------------------------------------------

class Scene
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Construtor padr�o.
	/// 
	////////////////////////////////////////////////////////////
	Scene();

	////////////////////////////////////////////////////////////
	/// \brief Destrutor virtual.
	/// 
	////////////////////////////////////////////////////////////
	virtual ~Scene();

	////////////////////////////////////////////////////////////
	/// \brief Inicializa objetos derivados desta classe.
	/// 
	/// � obrigat�rio implement�-lo nas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Start() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Atualiza objetos derivados desta classe.
	/// 
	/// M�todo virtual chamado a cada frame para atualizar objetos.
	/// Pode ser implementado pelas classes derivadas.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Update() {};

	////////////////////////////////////////////////////////////
	/// \brief Desenha todo cont�udo da cena.
	/// 
	/// Chama o m�todo Draw() da cena, Draw() das entidades e
	/// DrawOver() da cena nesta ordem.
	/// 
	////////////////////////////////////////////////////////////
	virtual void Draw();

	////////////////////////////////////////////////////////////
	/// \brief Atualiza entidades da cena.
	/// 
	/// Chama o m�todo Update() para cada objeto registrado,
	/// atualizando seu estado.
	/// 
	////////////////////////////////////////////////////////////
	void UpdateObjects();

	////////////////////////////////////////////////////////////
	/// \brief Destr�i entidades solicitadas.
	///
	/// Este m�todo � respons�vel por deletar entidades cujo
	/// m�todo Destroy() foi invocado no frame atual.
	///
	////////////////////////////////////////////////////////////
	void DestroyObjects();

	////////////////////////////////////////////////////////////
	/// \brief Instancia um objeto na cena.
	///
	/// Se o ID (�nico) for informado, o objeto ser� adicionado
	/// � tabela hash e poder� ser recuperado posteriormente
	/// usando o m�todo FindObject(). O objeto ser� destru�do
	/// automaticamente quando o destrutor da cena for chamado.
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade 
	/// a ser instanciada. Se n�o fornecida ou n�o for �nica,
	/// o objeto n�o ser� registrado na tabela hash.
	/// 
	/// \return Um ponteiro para o objeto do tipo `T`.
	///
	////////////////////////////////////////////////////////////
	template <typename T, typename... Args>
	T* CreateObject(const char* id = nullptr, Args&&... args);

	////////////////////////////////////////////////////////////
	/// \brief Adiciona um objeto existente � cena.
	///
	/// Se o ID (�nico) for informado, o objeto ser� adicionado
	/// � tabela hash e poder� ser recuperado posteriormente
	/// usando o m�todo FindObject(). O objeto n�o ser� destru�do
	/// pela cena (precisa ser destru�do manualmente).
	///
	/// \tparam T O tipo de objeto a ser instanciado.
	/// 
	/// \param id (Opcional) A chave que identifica a entidade 
	/// a ser instanciada. Se n�o fornecida ou n�o for �nica,
	/// o objeto n�o ser� registrado na tabela hash.
	///
	////////////////////////////////////////////////////////////
	void AddObject(Entity* obj, const char* id);

	////////////////////////////////////////////////////////////
	/// \brief Encontra um objeto registrado pelo nome e retorna o tipo espec�fico.
	///
	/// Este m�todo gen�rico busca um objeto pelo seu id (chave) na
	/// tabela de objetos. Se o objeto for encontrado,
	/// retorna um ponteiro para o tipo derivado.
	///
	/// \tparam T O tipo de entidade esperado.
	/// 
	/// \param id A chave que identifica a entidade a ser buscada.
	/// 
	/// \return Um ponteiro para o tipo `T` se a entidade for encontrada e
	/// corresponder ao tipo; caso contr�rio, retorna `nullptr`.
	///
	////////////////////////////////////////////////////////////
	template<typename T>
	T* FindObject(const std::string& id);

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de uma textura.
	///
	/// \param texture Refer�ncia para o objeto `Texture` que ser� utilizado
	/// para definir a textura do background.
	///
	///////////////////////////////////////////////////////////
	void SetBackground(const Texture* texture);

	///////////////////////////////////////////////////////////
	/// \brief Define a �rea da viewport.
	///
	/// \param x Coordenada X inicial da viewport.
	/// \param y Coordenada Y inicial da viewport.
	/// \param width Largura da viewport.
	/// \param height Altura da viewport.
	///
	///////////////////////////////////////////////////////////
	void SetViewport(int x, int y, int width, int height);

	///////////////////////////////////////////////////////////
	/// \brief Obt�m o ret�ngulo da �rea da viewport.
	///
	/// \return Refer�ncia constante para o ret�ngulo da viewport.
	///
	///////////////////////////////////////////////////////////
	const Rect& GetViewport() const;

	///////////////////////////////////////////////////////////
	/// \brief Obt�m as dimens�es da viewport.
	///
	/// \return Refer�ncia constante para as dimens�es da viewport.
	///
	///////////////////////////////////////////////////////////
	const ::Size& Size() const;

protected:
	static Window& window;
	static float&  deltaTime;

	bool visible;

	///////////////////////////////////////////////////////////
	/// \brief Define o background a partir de um arquivo.
	///
	/// Este m�todo carrega uma textura a partir de um arquivo especificado e a 
	/// define para o background.
	///
	/// \param file Caminho para o arquivo de textura que ser� carregado e 
	/// utilizado para definir a textura do sprite.
	/// 
	///////////////////////////////////////////////////////////
	void SetBackground(const char* file);	

	////////////////////////////////////////////////////////////
	/// \brief Desenha o conte�do adicional sobre a cena.
	///
	/// Este m�todo virtual � chamado ap�s todos os elementos principais
	/// da cena, entidades e componentes serem desenhados, ideal para
	/// renderizar objetos que devem aparecer sobre outros elementos,
	/// como HUDs, textos, notifica��es ou efeitos visuais que ficam em primeiro plano.
	///
	////////////////////////////////////////////////////////////
	virtual void DrawOver() {};

private:
	friend class Component;

	// Vari�veis da cena
	std::shared_ptr<Texture>	 texture;	  ///< Textura carregada na cena
	::Size						 size;
	Rect						 viewport;

	// Vari�veis de entidade				  
	ObjectsMap					 objHash;	  ///< Hash de objetos
	std::list<Entity*>           objects;	  ///< Guarda objetos do tipo Entity	
	std::list<Entity*>::iterator current;	  ///< Iterador para o objeto atual	
	std::vector<Entity*>         created;	  ///< Vetor de objetos a serem inicializados (pr�ximo frame)
	std::vector<Entity*>         destroy;	  ///< Vetor de objetos a serem destruidos (ao final do frame)
	std::unordered_set<Entity*>  destroyable; ///< Objetos que ser�o destru�dos pela cena
	bool                         sortObj;	  ///< Controla a atualiza��o da profundidade dos objetos

	// Vari�veis de componente		    
	std::list<Collider*>		 colliders;	  ///< Lista com todos colisores instanciados
};

// ------------------------------------------------------------------------------------------------

template <typename T, typename... Args>
T* Scene::CreateObject(const char* id, Args&&... args)
{
	T* obj{ new T{ std::forward<Args>(args)... } };
	AddObject(obj, id);
	destroyable.insert(obj);
	return obj;
}

// ------------------------------------------------------------------------------------------------

template<typename T>
T* Scene::FindObject(const std::string& id)
{
	auto it = objHash.find(id);
	if (it != objHash.end())
		return dynamic_cast<T*>(it->second);

	return nullptr;
}

// ------------------------------------------------------------------------------------------------

inline const Rect& Scene::GetViewport() const
{
	return viewport;
}

// ------------------------------------------------------------------------------------------------

inline const Size& Scene::Size() const
{
	return size;
};

// ------------------------------------------------------------------------------------------------

#endif
