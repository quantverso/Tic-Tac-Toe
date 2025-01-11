#include "Sound.h"

// ------------------------------------------------------------------------------------------------

Sound::Sound(Entity* entity) :
	Component{ entity }
{
}

// ------------------------------------------------------------------------------------------------

void Sound::Add(unsigned id, const char* file, unsigned channels)
{
	auto sound{ std::make_shared<SoundBuffer>() };
	sound->Load(file, channels);
	sounds[id] = sound;
}

// ------------------------------------------------------------------------------------------------

void Sound::Add(unsigned id, const SoundBuffer* soundBuffer)
{
	sounds[id] = SoundBufferPtr(const_cast<SoundBuffer*>(soundBuffer), [](SoundBuffer*) {});
}

// ------------------------------------------------------------------------------------------------

void Sound::Play(unsigned id, bool loop)
{
	auto it{ sounds.find(id) };
	if (it != sounds.end())
	{
		it->second->Play(loop);
		playing.push_back(it->second);
	}
}

// ------------------------------------------------------------------------------------------------

void Sound::Stop(unsigned id)
{
	auto it{ sounds.find(id) };
	if (it != sounds.end())
		it->second->Stop();
}

// ------------------------------------------------------------------------------------------------


void Sound::Pitch(unsigned id, float pitch)
{
	auto it{ sounds.find(id) };
	if (it != sounds.end())
		it->second->Pitch(pitch);
}

// ------------------------------------------------------------------------------------------------
