/*
  ==============================================================================

    Background.h
    Created: 12 Oct 2016 12:48:37am
    Author:  yuanshenli

  ==============================================================================
*/

#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"



class BackgroundComponent    : public Component
{
public:
    BackgroundComponent()
    {
    }
    
    ~BackgroundComponent()
    {
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll (Colours::black);
    }
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackgroundComponent)
};


#endif  // BACKGROUND_H_INCLUDED
