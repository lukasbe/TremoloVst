//
// Created by Lukas Berger on 28.12.25.
//

#include "VolumeProcessor.h"

void VolumeProcessor::prepare(const float volume)
{
    _volume = volume;
}

void VolumeProcessor::process(float* output, const int sample) const
{
    output[sample] = _volume * output[sample];
}
