//
// Created by Lukas Berger on 10.01.26.
//

#ifndef TREMOLO_POTILOOKANDFEEL_H
#define TREMOLO_POTILOOKANDFEEL_H

#include <juce_gui_basics/juce_gui_basics.h>

class PotiLookAndFeel : public juce::LookAndFeel_V4
{
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                          juce::Slider& slider) override;
    void drawLemonSlice(juce::Graphics& g, juce::Point<float> center, float radius, int numSegments);
};


#endif //TREMOLO_POTILOOKANDFEEL_H
