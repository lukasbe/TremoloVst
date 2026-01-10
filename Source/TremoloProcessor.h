//
// Created by Lukas Berger on 28.12.25.
//

#ifndef TREMOLO_TREMOLOPROCESSOR_H
#define TREMOLO_TREMOLOPROCESSOR_H


class TremoloProcessor
{
public:
    void prepare(double sampleRate, float rate, float depth, bool bypass);
    void process(float* output, int sample);

    void setRate(float rateHz);
    void setDepth(float depth);
    void setBypass(bool bypass);


    [[nodiscard]] float getRate() const { return _rateHz; }
    [[nodiscard]] float getDepth() const { return _depth; }
    [[nodiscard]] float getBypass() const { return _bypass; }
private:
    void updatePhaseIncrement();
    void advancePhase();

    mutable float _phase = 0.0f;
    mutable float _phaseIncrement = 0.0f;

    double _sampleRate = 44100.0;
    float _rateHz = 4.0f;
    float _depth = 0.7f;
    bool _bypass = false;
};

#endif //TREMOLO_TREMOLOPROCESSOR_H