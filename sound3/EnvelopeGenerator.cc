#include "EnvelopeGenerator.h"
#include <iostream>


double ADSREnvelopeGenerator:: next_sample(){
	switch (_state) {
		case IDLE:
			_level = 0;
			break;
		case ATTACK:
			_level += _attack_rate;
			if (_level >= 1)
			{
				_level = 1;
				_state = DECAY;
			}
			break;
		case DECAY:
			_level -= _decay_rate;
			if (_level <= _sustain_level)
			{
				_level = _sustain_level;
				_state = SUSTAIN;
			}
			break;
		case SUSTAIN:
			_level -= _sustain_rate;
			if (_level <= 0){
				_level = 0;
			_state = IDLE;
			}
			break;
		case RELEASE:
			_level -= _release_rate;
			if (_level <= 0){
				_level = 0;
			_state = IDLE;
			}
			break;
		default:
			throw std::runtime_error("WTF");
		}
		return _level;
}
