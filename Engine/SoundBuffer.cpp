#include "SoundBuffer.h"

// ------------------------------------------------------------------------------------------------

SoundBuffer::SoundBuffer() :
	m_Channels{},
	m_Index{}
{
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Load(const char* file, unsigned channels)
{
	m_Channels = channels;

	// Carrega o buffer de som
	m_Buffer = std::make_unique<sf::SoundBuffer>();
	m_Buffer->loadFromFile(file);

	// Carrega os objetos de som
	m_Sounds = std::make_unique<sf::Sound[]>(channels);
	for (unsigned i{}; i < channels; i++)
		m_Sounds[i].setBuffer(*m_Buffer);
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Play(bool loop)
{
	m_Index = (m_Index + 1) % m_Channels;
	if (loop)
		m_Sounds[m_Index].setLoop(true);
	m_Sounds[m_Index].play();
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Stop()
{
	for (unsigned i{}; i < m_Channels; i++)
	{
		m_Sounds[i].stop();
		m_Sounds[i].setLoop(false);
	}
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::SetPitch(float pitch)
{
	for (unsigned i{}; i < m_Channels; i++)
		m_Sounds[i].setPitch(pitch);
}

// ------------------------------------------------------------------------------------------------
