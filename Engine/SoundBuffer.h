#ifndef QUANTVERSO_SOUNDBUFFER_H
#define QUANTVERSO_SOUNDBUFFER_H

//--------------------------------------------------------------------------------------------------

#include <SDL.h>
#include <SFML/Audio.hpp>
#include <memory>

// ------------------------------------------------------------------------------------------------

class SoundBuffer
{
public:
	SoundBuffer();

	void Load(const char* file, unsigned channels = 1);
	void Play(bool loop = false);
	void Stop();	
	void SetPitch(float pitch);

	bool GetStatus();

private:
	std::unique_ptr<sf::SoundBuffer> m_Buffer;
	std::unique_ptr<sf::Sound[]>	 m_Sounds;
	unsigned						 m_Channels;
	unsigned						 m_Index;
};

// ------------------------------------------------------------------------------------------------

inline bool SoundBuffer::GetStatus()
{
	return m_Sounds[m_Index].getStatus() == sf::Sound::Playing;
}

// ------------------------------------------------------------------------------------------------

#endif
