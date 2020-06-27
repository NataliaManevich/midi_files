#ifndef FMWAVEGENERATOR_H_
#define FMWAVEGENERATOR_H_

#include "WaveGenerator.h"
#include "EnvelopeGenerator.h"

struct FMInstrument
{
	int al;
	bool fb;
	double multi[4];
	double be[4];
	struct { double at, dr, sl, sr, rr, dt; } op[4];
};

class FMWaveGenerator: public WaveGenerator
{
protected:
	std::shared_ptr<ADSREnvelopeGenerator> _eg[4];
	double _multiplier[4];
	double _beta[4];
	double _detune[4];
	int _algorithm;
	bool _feedback;

	double _feedback_value { 0. };

public:
	FMWaveGenerator();
	FMWaveGenerator(const FMWaveGenerator&) = delete;
	virtual ~FMWaveGenerator() = default;

	void set_AL(int algo) { if (algo >= 0 and algo <= 7) _algorithm = algo; }
	int AL() const { return _algorithm; }

	void set_FB(bool fb) { _feedback = fb; }
	bool FB() const { return _feedback; }

	void set_ML(int op, double ml) { if (op >= 0 and op <= 3) _multiplier[op] = ml; }
	double ML(int op) const {
		if (op >= 0 and op <= 3) return _multiplier[op]; else return 0.; }

	void set_level(int op, double l) {
		if (op >= 0 and op <= 3) _beta[op] = clamp(0., 1., l); }
	double level(int op) {
		if (op >= 0 and op <= 3) return _beta[op]; else return 0.; }

	void setup(const FMInstrument& inst);

	virtual double next_sample();

	virtual void key_on();
	virtual void key_off();
};

#endif /* FMWAVEGENERATOR_H_ */
