#pragma once

#include "PluginProcessor.h"

class PitchCurveView : public juce::Component
{
public:
    PitchCurveView() = default;
    void paint(juce::Graphics& g) override;
};

class FixVocalNoteAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit FixVocalNoteAudioProcessorEditor(FixVocalNoteAudioProcessor&);
    ~FixVocalNoteAudioProcessorEditor() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    FixVocalNoteAudioProcessor& audioProcessor;
    PitchCurveView pitchCurveView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FixVocalNoteAudioProcessorEditor)
};
