#ifndef ENVELOPEGENERATOR_H_
#define ENVELOPEGENERATOR_H_

#include "globals.h"

class EnvelopeGenerator
{
public:
	EnvelopeGenerator() = default;
	EnvelopeGenerator(const EnvelopeGenerator&) = delete;

	virtual ~EnvelopeGenerator() = default;


	virtual double next_sample() { return 0.; }

	virtual void key_on() {}
	virtual void key_off() {}
};

class ConstantEnvelopeGenerator: public EnvelopeGenerator
{
protected:
	double _level;
public:
	ConstantEnvelopeGenerator(double level): _level(clamp(0., 1., level)) {}
	ConstantEnvelopeGenerator(const ConstantEnvelopeGenerator&) = delete;
	ConstantEnvelopeGenerator() = delete;

	virtual ~ConstantEnvelopeGenerator() = default;

	virtual double next_sample() { return _level; }
};

class ADSREnvelopeGenerator: public EnvelopeGenerator
{
protected:
	enum State
	{
		IDLE = 0,
		ATTACK = 1,
		DECAY = 2,
		SUSTAIN = 3,
		RELEASE = 4
	};

	double _attack_rate { 1. };
	double _decay_rate { 0.1 };
	double _sustain_level { 1.0 };
	double _sustain_rate { 0.5 };
	double _release_rate { 2.0 };

	State _state { IDLE };
	double _level { 0. };

public:
	ADSREnvelopeGenerator() = default;
	ADSREnvelopeGenerator(const ADSREnvelopeGenerator&) = delete;
	virtual ~ADSREnvelopeGenerator() = default;
	virtual void key_on() { _state = ATTACK; }
	virtual void key_off() { if (_state != IDLE) _state = RELEASE; }
	virtual double next_sample();
	void set_attack_time(double at) { _attack_rate = std::max(0., at); }
	void set_decay_rate(double dr) { _decay_rate = std::max(0., dr); }
	void set_sustain_level(double sl) { _sustain_level = clamp(0., 1., sl); }
	void set_sustain_rate(double sr) { _sustain_rate = std::max(0., sr); }
	void set_release_rate(double rr) { _release_rate = std::max(0., rr); }
};
#endif /* ENVELOPEGENERATOR_H_ */
