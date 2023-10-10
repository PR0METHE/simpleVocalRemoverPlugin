/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "VocalRemover.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class GuiComponent  : public juce::Component,
                      public juce::Button::Listener,
                      public juce::Slider::Listener
{
public:
    //==============================================================================
    GuiComponent ();
    ~GuiComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void toggleButtonState();
    int getButtonState();

    VocalRemover vocalRemover;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

    // Binary resources:
    static const char* switchOff_png;
    static const int switchOff_pngSize;
    static const char* switchOn_png;
    static const int switchOn_pngSize;


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int buttonValue = 0;
    float highCutFreq = 20000.f;
    float lowCutFreq = 50.f;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::ImageButton> powerButton;
    std::unique_ptr<juce::Label> powerLabel;
    std::unique_ptr<juce::Slider> hpfSlider;
    std::unique_ptr<juce::Slider> lpfSlider;
    std::unique_ptr<juce::Label> lowcutLabel;
    std::unique_ptr<juce::Label> highcutLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GuiComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

