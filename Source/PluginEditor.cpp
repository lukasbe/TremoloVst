#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor& p)
    : AudioProcessorEditor(&p), processorRef(p),
      rateAttachment(processorRef.getState(), "rate", rate),
      depthAttachment(processorRef.getState(), "depth", depth),
      bypassAttachment(processorRef.getState(), "bypass", bypass)

{
    juce::ignoreUnused(processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    initializeRate();
    initializeDepth();
    initializeBypass();
    backgroundImage = juce::ImageCache::getFromMemory(
        BinaryData::background_png,
        BinaryData::background_pngSize
    );
    setSize(400, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void AudioPluginAudioProcessorEditor::initializeRate()
{
    rate.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    rate.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    rate.setRange(1.0, 5, .01);
    rate.setLookAndFeel(&rateLookAndFeel);
    rate.setPopupDisplayEnabled(true, true, this);
    rate.setRotaryParameters(juce::MathConstants<float>::pi * 1.25f,
                             juce::MathConstants<float>::pi * 2.75f,
                             true);
    rateLabel.setJustificationType(juce::Justification::centred);
    rateLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    rateLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black.withAlpha(.8f));
    rateLabel.setFont(juce::Font(juce::FontOptions(18.0f, juce::Font::bold)));
    addAndMakeVisible(rate);
    addAndMakeVisible(rateLabel);
}

void AudioPluginAudioProcessorEditor::initializeDepth()
{
    depth.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    depth.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    depth.setLookAndFeel(&rateLookAndFeel);
    depth.setPopupDisplayEnabled(true, true, this);
    depth.setRange(0, 1.0, .01);
    depthLabel.setJustificationType(juce::Justification::centred);
    depthLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    depthLabel.setColour(juce::Label::backgroundColourId, juce::Colours::black.withAlpha(.8f));
    depthLabel.setFont(juce::Font(juce::FontOptions(18.0f, juce::Font::bold)));
    addAndMakeVisible(depth);
    addAndMakeVisible(depthLabel);
}

void AudioPluginAudioProcessorEditor::initializeBypass()
{
    bypass.setButtonText("Bypass");
    bypass.setToggleState(false, juce::NotificationType::dontSendNotification);
    bypass.setClickingTogglesState(true);
    bypass.setColour(juce::TextButton::buttonColourId, juce::Colours::black);

    bypass.onClick = [this]
    {
        bypass.setButtonText(bypass.getToggleState() ? "Tremoloooo!" : "Bypass");
    };
    addAndMakeVisible(bypass);
}


//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    if (backgroundImage.isValid())
    {
        g.drawImageWithin(
            backgroundImage,
            0, 0,
            getWidth(), getHeight(),
            juce::RectanglePlacement::stretchToFit
        );
    }
}

void AudioPluginAudioProcessorEditor::resized()
{
    int labelPadding = 8;
    rate.setBounds(getWidth() / 4 - 40, getHeight() / 4 - 80, 80, 80);
    rateLabel.setBounds(getWidth() / 4 - 40 - (labelPadding / 2), getHeight() / 4 - (labelPadding / 2),
                        80 + labelPadding, 10 + labelPadding);
    depth.setBounds(static_cast<int>(getWidth() * (3 / 4.0) - 40), getHeight() / 4 - 80, 80, 80);
    depthLabel.setBounds(static_cast<int>(getWidth() * (3 / 4.0) - 40) - (labelPadding / 2),
                         getHeight() / 4 - (labelPadding / 2), 80 + labelPadding, 10 + labelPadding);
    bypass.setBounds(getWidth() / 2 - 150, getHeight() / 2 + 80, 300, 160);
}
