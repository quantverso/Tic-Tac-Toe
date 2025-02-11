#ifndef QUANTVERSO_ENGINE_H
#define QUANTVERSO_ENGINE_H

// ------------------------------------------------------------------------------------------------

#include "Window.h"

class Scene;

// ------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// class Engine
/// \brief Classe responsável pelo gerenciamento, atualização e
/// renderização do cena, janela e tempo do jogo.
/// 
////////////////////////////////////////////////////////////
class Engine
{
public:
    inline static Window window;    ///< Janela gráfica 
    inline static float  deltaTime; ///< Tempo decorrido do último frame

    ////////////////////////////////////////////////////////////
    /// \brief Carrega uma cena na Engine.
    /// 
    /// Este método inicia o loop da Engine com a cena fornecida quando chamado pela primeira vez.
    /// Caso já exista uma cena anterior, ela será destruída e substituída pela nova cena.
    /// 
    /// \param scene Ponteiro para o objeto da cena do jogo a ser carregada.
    /// 
    /// \note Este método invoca `Loop()` para iniciar o loop principal de execução do jogo,
    /// quando chamado pela primeira vez.
    /// 
    /// \warning Após o método ser executado, se uma cena anterior existia,
    /// ela será deletada da memória e substituída pela cena atual.
    /// 
    ////////////////////////////////////////////////////////////
    static void Run(Scene* scene);

private:
    inline static Scene* s_Scene; ///< Cena atual

    ////////////////////////////////////////////////////////////
    /// \brief Laço principal do jogo.
    /// 
    /// O laço roda enquanto a janela gráfica estiver aberta.
    /// 
    ////////////////////////////////////////////////////////////
    static void Loop();
};

// ------------------------------------------------------------------------------------------------

#endif
