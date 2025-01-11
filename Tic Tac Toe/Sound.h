#ifndef QUANTVERSO_SOUND_H
#define QUANTVERSO_SOUND_H

// ------------------------------------------------------------------------------------------------

#include "Component.h"
#include "SoundBuffer.h"
#include <unordered_map>
#include <list>

using SoundBufferPtr = std::shared_ptr<SoundBuffer>;

// ------------------------------------------------------------------------------------------------

////////////////////////////////////////////////////////////
/// \class Sound
/// \brief Gerencia a reprodu��o de sons associados a uma entidade.
///
/// A classe Sound � um componente do sistema de entidades que permite
/// a reprodu��o, adi��o e controle de sons. Cada inst�ncia de Sound
/// pode gerenciar m�ltiplos sons identificados por um ID �nico.
///
////////////////////////////////////////////////////////////
class Sound : public Component
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Construtor.
    ///
    /// Inicializa o componente de som associando-o a uma entidade.
    /// \param entity Ponteiro para a entidade � qual o som pertence.
    ///
    ////////////////////////////////////////////////////////////
    Sound(Entity* entity);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um som a partir de um arquivo.
    ///
    /// Carrega um arquivo de som e associa-o a um ID espec�fico.
    /// \param id Identificador �nico para o som.
    /// \param fileName Nome do arquivo de som a ser carregado.
    ///
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, const char* file, unsigned channels = 1);

    ////////////////////////////////////////////////////////////
    /// \brief Adiciona um som usando um buffer de som.
    ///
    /// Associa um buffer de som existente a um ID espec�fico.
    /// \param id Identificador �nico para o som.
    /// \param soundBuffer Refer�ncia a um buffer de som existente.
    ///
    ////////////////////////////////////////////////////////////
    void Add(unsigned id, const SoundBuffer* soundBuffer);

    ////////////////////////////////////////////////////////////
    /// \brief Reproduz o som associado a um ID.
    ///
    /// Inicia a reprodu��o do som identificado pelo ID fornecido.
    /// \param id Identificador do som a ser reproduzido.
    ///
    ////////////////////////////////////////////////////////////
    void Play(unsigned id, bool loop = false);

    ////////////////////////////////////////////////////////////
    /// \brief Interrompe a reprodu��o de um som.
    ///
    /// Para a reprodu��o do som associado ao ID fornecido.
    /// \param id Identificador do som a ser interrompido.
    ///
    ////////////////////////////////////////////////////////////
    void Stop(unsigned id);

    ////////////////////////////////////////////////////////////
    /// \brief Verifica o estado de reprodu��o de um som.
    ///
    /// Retorna true se o som associado ao ID estiver sendo reproduzido.
    /// \param id Identificador do som.
    /// \return true se o som estiver tocando, false caso contr�rio.
    ///
    ////////////////////////////////////////////////////////////
    bool Status(unsigned id);

    ////////////////////////////////////////////////////////////
    /// \brief Define o pitch de um som espec�fico
    ///
    /// Este m�todo ajusta o pitch de um som correpondente ao ID.
    /// O pitch � um multiplicador para a frequ�ncia do som. Um
    /// valor de pitch maior que 1.0 acelera o som, enquanto
    /// valores menores tornam o som mais grave.
    ///
    /// \param id Identificador �nico do som ao qual o pitch ser� aplicado
    /// \param pitch Valor do pitch, onde 1.0 � o valor padr�o (sem altera��o)
    ///
    ////////////////////////////////////////////////////////////
    void Pitch(unsigned id, float pitch);

    ////////////////////////////////////////////////////////////
    /// \brief Remove sons que j� pararam de tocar.
    ///
    /// Percorre a lista de sons atualmente em reprodu��o e remove
    /// aqueles que j� pararam, destruindo Sounds de objetos que
    /// foram destru�dos enquanto o som estava em reprodu��o.
    ///
    ////////////////////////////////////////////////////////////
    static void Release();

private:
    inline static std::list<SoundBufferPtr> playing; ///< Armazena os sons que est�o em reprodu��o.

    std::unordered_map<unsigned, SoundBufferPtr> sounds; ///< Armazena os sons associados aos seus IDs.
};

// ------------------------------------------------------------------------------------------------

inline bool Sound::Status(unsigned id)
{
    auto it{ sounds.find(id) };
    if (it != sounds.end())
        return it->second->Status();
}

// ------------------------------------------------------------------------------------------------

inline void Sound::Release()
{
    for (auto it{ playing.begin() }; it != playing.end(); )
    {
        if (!(*it)->Status())
            it = playing.erase(it);
        else
            ++it;
    }
}

// ------------------------------------------------------------------------------------------------

#endif
