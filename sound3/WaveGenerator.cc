
#include "WaveGenerator.h"

double WaveGenerator::next_sample()
{
	_period_counter += _freq / AUDIO_SAMPLING_FREQUENCY;
	while (_period_counter >= 1.)
		_period_counter -= 1.;
	return 0.;
}

double SquareWaveGenerator::next_sample()
{
	double result;

	if (_period_counter < 0.5)
		result = 1.;
	else
		result = -1.;

	WaveGenerator::next_sample();
	return result;
}

double SawtoothWaveGenerator::next_sample()
{
	double result;

	result = 1. - _period_counter * 2.;
	result = clamp(-1., 1., result);

	WaveGenerator::next_sample();
	return result;
}

double TriangleWaveGenerator::next_sample()
{
	double result;

	if (_period_counter < 0.25)
		result = _period_counter * 4;
	else if (_period_counter < 0.75)
		result = 1. - (_period_counter-0.25) * 4.;
	else
		result = -1. + (_period_counter-0.75) * 4.;

	result = clamp(-1., 1., result);

	WaveGenerator::next_sample();
	return result;
}

double SineWaveGenerator::next_sample()
{
	double result;

	result = sin(2. * Pi * _period_counter);

	WaveGenerator::next_sample();
	return result;
}
