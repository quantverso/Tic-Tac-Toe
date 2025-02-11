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
	m_Sounds[id] = sound;
}

// ------------------------------------------------------------------------------------------------

void Sound::Add(unsigned id, SoundBuffer* soundBuffer)
{
	m_Sounds[id] = std::shared_ptr<SoundBuffer>(soundBuffer, [](SoundBuffer*) {});
}

// ------------------------------------------------------------------------------------------------

void Sound::Play(unsigned id, bool loop)
{
	if (auto it{ m_Sounds.find(id) }; it != m_Sounds.end())
	{
		it->second->Play(loop);
		s_Playing.push_back(it->second);
	}
}

// ------------------------------------------------------------------------------------------------

void Sound::Stop(unsigned id)
{
	if (auto it{ m_Sounds.find(id) }; it != m_Sounds.end())
		it->second->Stop();
}

// ------------------------------------------------------------------------------------------------


void Sound::SetPitch(unsigned id, float pitch)
{
	if (auto it{ m_Sounds.find(id) }; it != m_Sounds.end())
		it->second->SetPitch(pitch);
}

// ------------------------------------------------------------------------------------------------
