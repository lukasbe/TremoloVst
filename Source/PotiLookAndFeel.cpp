//
// Created by Lukas Berger on 10.01.26.
//

#include "PotiLookAndFeel.h"

void PotiLookAndFeel::drawRotarySlider (juce::Graphics& g,
                                       int x, int y, int width, int height,
                                       float sliderPosProportional,
                                       float rotaryStartAngle,
                                       float rotaryEndAngle,
                                       juce::Slider& slider)
{
    auto bounds = juce::Rectangle<float> (x, y, width, height);
    auto center = bounds.getCentre();
    float radius = juce::jmin (width / 2.0f, height / 2.0f) - 4.0f;

    // 🍋 Clip to knob circle
    juce::Path clip;
    clip.addEllipse (center.x - radius,
                     center.y - radius,
                     radius * 2.0f,
                     radius * 2.0f);

    g.saveState();
    g.reduceClipRegion (clip);

    drawLemonSlice (g, center, radius * 0.98f, 10);

    g.restoreState();

    // --- Your existing knob overlay ---
    g.setColour (juce::Colours::darkgrey.darker());
    g.drawEllipse (center.x - radius,
                   center.y - radius,
                   radius * 2.0f,
                   radius * 2.0f,
                   2.0f);

    // Pointer
    auto angle = rotaryStartAngle
               + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    juce::Path p;
    p.addRectangle (-radius * 0.05f,
                    -radius * 0.9f,
                    radius * 0.1f,
                    radius * 0.7f);

    g.setColour (juce::Colours::black);
    g.saveState();
    g.addTransform (juce::AffineTransform::rotation (angle)
                       .translated (center.x, center.y));
    g.fillPath (p);
    g.restoreState();
}



void PotiLookAndFeel::drawLemonSlice (juce::Graphics& g,
                            juce::Point<float> center,
                            float radius,
                            int numSegments)
{
    // Outer rind
    g.setColour (juce::Colour (0xfff1c40f));
    g.fillEllipse (center.x - radius,
                   center.y - radius,
                   radius * 2.0f,
                   radius * 2.0f);

    // Inner flesh (radial gradient)
    juce::ColourGradient fleshGrad (
        juce::Colour (0xfffff6a0), center.x, center.y,
        juce::Colour (0xfff7d046), center.x, center.y + radius,
        true
    );
    fleshGrad.addColour (0.7, juce::Colour (0xcca704));

    g.setGradientFill (fleshGrad);
    g.fillEllipse (center.x - radius * 0.88f,
                   center.y - radius * 0.88f,
                   radius * 1.76f,
                   radius * 1.76f);

    // Segment membranes
    g.setColour (juce::Colours::white.withAlpha (0.5f));
    for (int i = 0; i < numSegments; ++i)
    {
        float angle = juce::MathConstants<float>::twoPi * i / numSegments;

        g.drawLine (center.x,
                    center.y,
                    center.x + std::cos (angle) * radius * 0.88f,
                    center.y + std::sin (angle) * radius * 0.88f,
                    1.2f);
    }

    g.setColour (juce::Colours::white.withAlpha (0.15f));
    g.fillEllipse (center.x - radius * 0.6f,
                   center.y - radius * 0.9f,
                   radius * 1.2f,
                   radius * 0.6f);

    g.setColour (juce::Colours::black.withAlpha (0.2f));
    g.drawEllipse (center.x - radius,
                   center.y - radius,
                   radius * 2.0f,
                   radius * 2.0f,
                   3.0f);


    // Central pith
    g.setColour (juce::Colours::white.withAlpha (0.6f));
    g.fillEllipse (center.x - radius * 0.08f,
                   center.y - radius * 0.08f,
                   radius * 0.16f,
                   radius * 0.16f);
}