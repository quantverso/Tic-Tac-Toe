#ifndef QUANTVERSO_SOUND_H
#define QUANTVERSO_SOUND_H

// ------------------------------------------------------------------------------------------------

#include "Component.h"
#include "SoundBuffer.h"
#include <unordered_map>
#include <list>
#include <optional>

// ------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Sound
/// \brief Gerencia a reprodução de sons associados a uma entidade.
///
/// A classe Sound é um componente do sistema de entidades que permite a reprodução,
/// adição e controle de sons. Cada instância de Sound pode gerenciar múltiplos sons
/// identificados por um ID único.
///
////////////////////////////////////////////////////////////
class Sound : public Component
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa o componente de som associando-o a uma entidade.
    /// \param entity Ponteiro para a entidade à qual o som pertence.
    ///
    ////////////////////////////////////////////////////////////
    Sound(Entity* entity);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um som a partir de um arquivo.
    ///
    /// Carrega um arquivo de som e associa-o a um ID específico.
    /// 
    /// \param id Identificador único para o som.
    /// \param fileName Nome do arquivo de som a ser carregado.
    ///
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, const char* file, unsigned channels = 1);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um som usando um buffer de som.
    ///
    /// Associa um buffer de som existente a um ID específico.
    /// 
    /// \param id Identificador único para o som.
    /// \param soundBuffer Referência a um buffer de som existente.
    ///
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, SoundBuffer* soundBuffer);

    ////////////////////////////////////////////////////////////
    /// \brief Reproduz o som associado a um ID.
    ///
    /// Inicia a reprodução do som identificado pelo ID fornecido.
    /// 
    /// \param id Identificador do som a ser reproduzido.
    ///
    ////////////////////////////////////////////////////////////
    void Play(unsigned id, bool loop = false);

    ////////////////////////////////////////////////////////////
    /// \brief Interrompe a reprodução de um som.
    ///
    /// Para a reprodução do som associado ao ID fornecido.
    /// 
    /// \param id Identificador do som a ser interrompido.
    ///
    ////////////////////////////////////////////////////////////
    void Stop(unsigned id);

    ////////////////////////////////////////////////////////////
    /// \brief Define o pitch de um som específico
    ///
    /// Este método ajusta o pitch de um som correpondente ao ID.
    /// O pitch é um multiplicador para a frequência do som.
    /// Um valor de pitch maior que 1.0 acelera o som, enquanto valores menores
    /// tornam o som mais grave.
    ///
    /// \param id Identificador único do som ao qual o pitch será aplicado
    /// \param pitch Valor do pitch, onde 1.0 é o valor padrão (sem alteração)
    ///
    ////////////////////////////////////////////////////////////
    void SetPitch(unsigned id, float pitch);

    ////////////////////////////////////////////////////////////
    /// \brief Verifica o estado de reprodução de um som.
    ///
    /// Retorna true se o som associado ao ID estiver sendo reproduzido.
    /// 
    /// \param id Identificador do som.
    /// 
    /// \return true se o som estiver tocando, false caso contrário.
    ///
    ////////////////////////////////////////////////////////////
    bool GetStatus(unsigned id);

    ////////////////////////////////////////////////////////////
    /// \brief Remove sons que já pararam de tocar.
    ///
    /// Percorre a lista de sons atualmente em reprodução e remove aqueles que já pararam,
    /// destruindo Sounds de objetos que foram destruídos enquanto o som estava em reprodução.
    ///
    ////////////////////////////////////////////////////////////
    static void Release();

private:
    using SoundBufferPtr = std::shared_ptr<SoundBuffer>;

    inline static std::list<SoundBufferPtr> s_Playing; ///< Armazena os sons que estão em reprodução.

    std::unordered_map<unsigned, SoundBufferPtr> m_Sounds; ///< Armazena os sons associados aos seus IDs.
};

// ------------------------------------------------------------------------------------------------
 
inline bool Sound::GetStatus(unsigned id)
{    
    if (auto it{ m_Sounds.find(id) }; it != m_Sounds.end())
        return it->second->GetStatus();

    return false;
}

// ------------------------------------------------------------------------------------------------

inline void Sound::Release()
{
    for (auto it{ s_Playing.begin() }; it != s_Playing.end(); )
    {
        if (!(*it)->GetStatus())
            it = s_Playing.erase(it);
        else
            it++;
    }
}

// ------------------------------------------------------------------------------------------------

#endif
