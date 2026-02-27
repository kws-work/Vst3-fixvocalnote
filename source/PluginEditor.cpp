#include "PluginEditor.h"

namespace
{
float midiToY(float midiNote, juce::Rectangle<int> area)
{
    constexpr float low = 36.0f;
    constexpr float high = 84.0f;
    const auto normalized = juce::jlimit(0.0f, 1.0f, (midiNote - low) / (high - low));
    return area.getBottom() - normalized * static_cast<float>(area.getHeight());
}
}

void PitchCurveView::paint(juce::Graphics& g)
{
    const auto area = getLocalBounds().reduced(10);

    g.fillAll(juce::Colour::fromRGB(20, 22, 28));

    g.setColour(juce::Colour::fromRGB(45, 49, 60));
    for (int note = 36; note <= 84; note += 2)
    {
        const auto y = midiToY(static_cast<float>(note), area);
        g.drawHorizontalLine(static_cast<int>(y), static_cast<float>(area.getX()), static_cast<float>(area.getRight()));
    }

    juce::Path pitchPath;
    const int totalPoints = 240;
    for (int i = 0; i < totalPoints; ++i)
    {
        const auto x = static_cast<float>(area.getX()) + (static_cast<float>(i) / static_cast<float>(totalPoints - 1)) * area.getWidth();
        const auto base = 60.0f + 6.0f * std::sin(i * 0.07f);
        const auto vibrato = 0.9f * std::sin(i * 0.42f);
        const auto y = midiToY(base + vibrato, area);

        if (i == 0)
            pitchPath.startNewSubPath(x, y);
        else
            pitchPath.lineTo(x, y);
    }

    g.setColour(juce::Colour::fromRGB(255, 146, 0));
    g.strokePath(pitchPath, juce::PathStrokeType(2.3f));

    g.setColour(juce::Colours::white.withAlpha(0.8f));
    g.setFont(14.0f);
    g.drawText("Pitch Curve (Mock) - ARA2 ready UI scaffold", area.removeFromTop(22), juce::Justification::left);
}

FixVocalNoteAudioProcessorEditor::FixVocalNoteAudioProcessorEditor(FixVocalNoteAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    addAndMakeVisible(pitchCurveView);
    setSize(1000, 540);
}

void FixVocalNoteAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour::fromRGB(15, 16, 20));
}

void FixVocalNoteAudioProcessorEditor::resized()
{
    pitchCurveView.setBounds(getLocalBounds().reduced(14));
}
