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
	bool Status();
	void Pitch(float pitch);

private:
	std::unique_ptr<sf::SoundBuffer> buffer;
	std::unique_ptr<sf::Sound[]>	 sounds;
	unsigned						 channels;
	unsigned						 it;
};

// ------------------------------------------------------------------------------------------------

inline bool SoundBuffer::Status()
{
	return sounds[it].getStatus() == sf::Sound::Playing;
}

// ------------------------------------------------------------------------------------------------

#endif
