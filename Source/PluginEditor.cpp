#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p),
      volumeAttachment(processorRef.getState(), "volume", volume),
      rateAttachment(processorRef.getState(), "rate", rate),
      depthAttachment(processorRef.getState(), "depth", depth)
{
    juce::ignoreUnused(processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    initializeVolume();
    initializeRate();
    initializeDepth();
    initializeBypass();
    setSize(400, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

void AudioPluginAudioProcessorEditor::initializeVolume()
{
    volume.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 50);
    volume.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    volume.setRange(1.0, 10.0, 1.0);
    volumeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(volume);
    addAndMakeVisible(volumeLabel);
}

void AudioPluginAudioProcessorEditor::initializeRate()
{
    volume.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 50);
    rate.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    rate.setRange(1.0, 5, .01);
    rateLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(rate);
    addAndMakeVisible(rateLabel);
}

void AudioPluginAudioProcessorEditor::initializeDepth()
{
    volume.setTextBoxStyle(juce::Slider::TextBoxAbove, false, 50, 50);
    depth.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    depth.setRange(0, 1.0, .01);
    depthLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(depth);
    addAndMakeVisible(depthLabel);
}

void AudioPluginAudioProcessorEditor::initializeBypass()
{
    bypass.setButtonText("Bypass");
    bypass.setToggleState(false, juce::NotificationType::dontSendNotification);
    bypass.setClickingTogglesState(true);

    bypass.onClick = [this]()
    {
        const bool isActive = bypass.getToggleState();
        bypass.setButtonText(isActive ? "Tremoloooo!" : "Bypass");
    };
    addAndMakeVisible(bypass);
}


//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    volume.setBounds(getWidth() / 2 - 50, getHeight() / 4 - 50, 100, 100);
    volumeLabel.setBounds(getWidth() / 2 - 50, getHeight() / 4 + 45, 100, 10);
    rate.setBounds(getWidth() / 4 - 50, getHeight() / 4 - 100, 100, 100);
    rateLabel.setBounds(getWidth() / 4 - 50, getHeight() / 4, 100, 10);
    depth.setBounds(static_cast<int>(getWidth() * (3 / 4.0) - 50), getHeight() / 4 - 100, 100, 100);
    depthLabel.setBounds(static_cast<int>(getWidth() * (3 / 4.0) - 50), getHeight() / 4, 100, 10);
    bypass.setBounds(getWidth() / 2 - 150, getHeight() / 2 + 80, 300, 160);
}
