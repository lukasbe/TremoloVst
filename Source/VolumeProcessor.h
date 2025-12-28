//
// Created by Lukas Berger on 28.12.25.
//

#ifndef TREMOLO_VOLUMEPROCESSOR_H
#define TREMOLO_VOLUMEPROCESSOR_H


class VolumeProcessor
{
    public:
        void prepare(float volume);
        void process(float* output, int sample) const;

        [[nodiscard]] float getVolume() const { return _volume; }
        void setVolume(const float volume) { _volume = volume; }
    private:
        float _volume = 7.0f;
};


#endif //TREMOLO_VOLUMEPROCESSOR_H