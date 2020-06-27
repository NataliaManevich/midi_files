
#ifndef SOUNDSOURCE_H_
#define SOUNDSOURCE_H_

#include "globals.h"

#include "WaveGenerator.h"
#include "EnvelopeGenerator.h"
#include "FMWaveGenerator.h"

class SoundSource
{
protected:
	std::shared_ptr<WaveGenerator> _wg { std::make_shared<WaveGenerator>() };
	std::shared_ptr<EnvelopeGenerator> _eg { std::make_shared<EnvelopeGenerator>() };
	std::shared_ptr<FMWaveGenerator> _fg { std::make_shared<FMWaveGenerator>() };
public:
	SoundSource() = default;
	SoundSource(const SoundSource&) = delete;
	virtual ~SoundSource() = default;

	virtual double next_sample() { return _wg->next_sample() * _eg->next_sample(); }

	virtual void set_envelope_generator(const std::shared_ptr<EnvelopeGenerator>& eg)
	{
		if (eg == nullptr)
			_eg = std::make_shared<EnvelopeGenerator>();
		else
			_eg = eg;
	}

	virtual void set_fmw_generator(const std::shared_ptr<FMWaveGenerator>& fg)
		{
			if (fg == nullptr)
				_fg = std::make_shared<FMWaveGenerator>();
			else
				_fg = fg;
		}

	virtual void set_wave_generator(const std::shared_ptr<WaveGenerator>& wg)
	{
		if (wg == nullptr)
			_wg = std::make_shared<WaveGenerator>();
		else
			_wg = wg;
	}
};

#endif /* SOUNDSOURCE_H_ */
