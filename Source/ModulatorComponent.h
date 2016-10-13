/*
  ==============================================================================

    ModulatorComponent.h
    Created: 11 Oct 2016 8:53:27pm
    Author:  yuanshenli

  ==============================================================================
*/

#ifndef MODULATORCOMPONENT_H_INCLUDED
#define MODULATORCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"



class ModulatorComponent    : public Component
{
public:
    ModulatorComponent()
    {
    }

    ~ModulatorComponent()
    {
    }

    void paint (Graphics& g) override
    {
	    g.setColour (Colours::lightsalmon);
        g.fillRoundedRectangle(0, 0, 30, 30, 5);
//	    g.drawLine (100, getHeight() / 2, 130, getHeight() / 2, 30);
        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("M", getLocalBounds(), Justification::centred, true);
    }

private:
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ModulatorComponent)
};


#endif  // MODULATORCOMPONENT_H_INCLUDED
