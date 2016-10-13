/*
  ==============================================================================

    KeysRelease.h
    Created: 12 Oct 2016 12:48:55am
    Author:  yuanshenli

  ==============================================================================
*/

#ifndef KEYSRELEASE_H_INCLUDED
#define KEYSRELEASE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class KeysReleasedComponent   : public Component
{
public:
//    KeysReleasedComponent(int value)
//    {
//        myValue = value;
//    }
    
    KeysReleasedComponent()
    {
    }
    
    ~KeysReleasedComponent()
    {
    }
    
    void paint (Graphics& g) override
    {
	    g.setColour (Colours::white);
        g.drawRoundedRectangle(0, 0, 50, 50, 10.0, 2.0);
    }
    
private:
    int myValue = 0;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeysReleasedComponent)
};


#endif  // KEYSRELEASE_H_INCLUDED
