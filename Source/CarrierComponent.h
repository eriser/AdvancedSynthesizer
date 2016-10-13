/*
  ==============================================================================

    CarrierComponent.h
    Created: 11 Oct 2016 7:58:36pm
    Author:  yuanshenli

  ==============================================================================
*/

#ifndef CARRIERCOMPONENT_H_INCLUDED
#define CARRIERCOMPONENT_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"

class CarrierComponent   : public Component
{
public:
    CarrierComponent()
    {
    }

    ~CarrierComponent()
    {
    }
    
    void paint (Graphics& g) override
    {
//        g.setOrigin(30,0);
	    g.setColour (Colours::lightseagreen);
        g.fillRoundedRectangle(0, 0, 30, 30, 5);
//	    g.drawLine (200, getHeight() / 2, 230, getHeight() / 2, 30);
//        g.drawLine (0, getHeight() / 2, getWidth(), getHeight() / 2, 30);
        g.setFont (14.0f);
        g.setColour (Colours::white);
        g.drawText ("C", getLocalBounds(), Justification::centred, true);
//      g.drawLine (0, 200, getWidth(), getHeight() / 2, 20);
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CarrierComponent)
};


#endif  // CARRIERCOMPONENT_H_INCLUDED
