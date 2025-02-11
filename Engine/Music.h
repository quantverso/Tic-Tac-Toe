#ifndef QUANTVERSO_MUSIC_H
#define QUANTVERSO_MUSIC_H

//--------------------------------------------------------------------------------------------------

#include <SFML/Audio.hpp>
#include <memory>

// ------------------------------------------------------------------------------------------------

class Music
{
public:
	void Load(const char* file);
	void Play(bool loop);
	void Stop();
	void SetVolume(float volume);

private:
	std::unique_ptr<sf::Music> m_Music;
};

// ------------------------------------------------------------------------------------------------

#endif
