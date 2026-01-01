//
// Created by Lukas Berger on 28.12.25.
//

#include "TremoloProcessor.h"

#include <algorithm>
#include <cmath>

void TremoloProcessor::prepare(const double sampleRate, const float rate, const float depth)
{
    _sampleRate = sampleRate;
    _phase = 0.0f;
    updatePhaseIncrement();
    setRate(rate);
    setDepth(depth);
}

void TremoloProcessor::process(float* output, const int sample)
{
    const float lfo = std::sin(_phase);
    float mod = 0.5f + 0.5f * lfo;
    mod = std::pow(mod, 3.0f);
    const float gain = std::sqrt((1.0f - _depth) + _depth * mod);
    output[sample] *= 0.5f;
    output[sample] *= gain;
    advancePhase();
}

void TremoloProcessor::advancePhase()
{
    _phase += _phaseIncrement;
    _phase = static_cast<float>(std::fmod(_phase, 2.0f * M_PI));
}

void TremoloProcessor::setRate(float rateHz)
{
    _rateHz = rateHz;
    updatePhaseIncrement();
}

void TremoloProcessor::setDepth(float depth)
{
    _depth = depth;
}

void TremoloProcessor::updatePhaseIncrement()
{
    _phaseIncrement = static_cast<float>(
        (2.0 * M_PI * _rateHz) / _sampleRate
    );
}
