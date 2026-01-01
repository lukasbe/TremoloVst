#pragma once

#include "PluginProcessor.h"

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
    juce::Slider depth;
    juce::Label depthLabel  {"DepthLabel", "Depth"};
    juce::Slider volume;
    juce::Label volumeLabel  {"VolumeLabel", "Volume"};
    juce::TextButton bypass;

    juce::AudioProcessorValueTreeState::SliderAttachment volumeAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment rateAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment depthAttachment;

    void initializeVolume();
    void initializeRate();
    void initializeDepth();
    void initializeBypass();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};