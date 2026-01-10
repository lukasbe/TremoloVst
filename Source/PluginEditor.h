#pragma once

#include "PluginProcessor.h"
#include "PotiLookAndFeel.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    juce::Slider rate;
    juce::Label rateLabel  {"RateLabel", "Rate"};
    PotiLookAndFeel rateLookAndFeel;
    juce::Slider depth;
    juce::Label depthLabel  {"DepthLabel", "Depth"};
    juce::TextButton bypass;

    juce::AudioProcessorValueTreeState::SliderAttachment rateAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment depthAttachment;
    juce::AudioProcessorValueTreeState::ButtonAttachment bypassAttachment;

    void initializeRate();
    void initializeDepth();
    void initializeBypass();
    juce::Image backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};