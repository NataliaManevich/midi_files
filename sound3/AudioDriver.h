#ifndef AUDIODRIVER_H_
#define AUDIODRIVER_H_

#include "globals.h"
#include "SoundSource.h"

class AudioDriver
{
protected:
	SDL_AudioDeviceID _id;
	SDL_AudioSpec _spec {};
	SDL_AudioSpec _obtained_spec {};

	std::shared_ptr<SoundSource> _source { std::make_shared<SoundSource>() };
	short _master_volume { 0 };

public:
	AudioDriver();
	~AudioDriver();

	void pause() { SDL_PauseAudioDevice(_id, 1); }
	void unpause() { SDL_PauseAudioDevice(_id, 0); }

	void callback(short * buffer, int samples);

	void set_sound_source(const std::shared_ptr<SoundSource>& ss)
	{
		if (ss == nullptr)
			_source = std::make_shared<SoundSource>();
		else
			_source = ss;
	}

	void set_master_volume(short vol) { _master_volume = clamp(0, 32000, int(vol)); }
};




#endif /* AUDIODRIVER_H_ */
