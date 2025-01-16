#include "SoundBuffer.h"

// ------------------------------------------------------------------------------------------------

SoundBuffer::SoundBuffer() :
	channels{},
	it{}
{
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Load(const char* file, unsigned channels)
{
	this->channels = channels;

	// Carrega o buffer de som
	buffer = std::make_unique<sf::SoundBuffer>();
	buffer->loadFromFile(file);

	// Carrega os objetos de som
	sounds = std::make_unique<sf::Sound[]>(channels);
	for (unsigned i{}; i < channels; ++i)
	{
		sounds[i].setBuffer(*buffer);
	}
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Play(bool loop)
{
	it = (it + 1) % channels;
	if (loop)
		sounds[it].setLoop(true);
	sounds[it].play();
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Stop()
{
	for (unsigned i{}; i < channels; ++i)
	{
		sounds[i].stop();
		sounds[i].setLoop(false);
	}
}

// ------------------------------------------------------------------------------------------------

void SoundBuffer::Pitch(float pitch)
{
	for (unsigned i{}; i < channels; ++i)
	{
		sounds[i].setPitch(pitch);
	}
}

// ------------------------------------------------------------------------------------------------
