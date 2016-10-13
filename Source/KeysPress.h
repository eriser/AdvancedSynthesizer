/*
  ==============================================================================

    KeysPress.h
    Created: 12 Oct 2016 12:49:06am
    Author:  yuanshenli

  ==============================================================================
*/

#ifndef KEYSPRESS_H_INCLUDED
#define KEYSPRESS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class KeysPressedComponent   : public Component
{
public:
    KeysPressedComponent()
    {
    }

    ~KeysPressedComponent()
    {
    }
    
    void paint (Graphics& g) override
    {
	    g.setColour (Colours::red);
        g.drawRoundedRectangle(0, 0, 50, 50, 10.0, 2.0);
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeysPressedComponent)
};




#endif  // KEYSPRESS_H_INCLUDED
