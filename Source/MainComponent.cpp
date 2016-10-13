// Music 256a / CS 476a | fall 2016
// CCRMA, Stanford University
//
// Author: Shenli Yuan (shenliy@stanford.edu)
// Description: Simple JUCE sine wave synthesizer

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "Sine.h"
#include "Smooth.h"
#include "CarrierComponent.h"
#include "ModulatorComponent.h"
#include "KeysPress.h"
#include "KeysRelease.h"
#include <thread>
#include "FaustReverb.h"
#include "Background.h"


const int MAX_SINE_WAVE = 2;

class MainContentComponent :
    public AudioAppComponent,
    private Slider::Listener,
    //private ToggleButton::Listener,
    private Button::Listener
{
public:
    MainContentComponent() : onOff (0), samplingRate(0.0)
    {
        keys.push_back(KeyPress('w'));
        keys.push_back(KeyPress('s'));
        keys.push_back(KeyPress('a'));
        keys.push_back(KeyPress('d'));
        keys.push_back(KeyPress(juce::KeyPress::upKey));
        keys.push_back(KeyPress(juce::KeyPress::downKey));
        keys.push_back(KeyPress(juce::KeyPress::leftKey));
        keys.push_back(KeyPress(juce::KeyPress::rightKey));
        keys.push_back(KeyPress(juce::KeyPress::spaceKey));
        
        for (int i = 0; i < 9; i++){
            keysPress.emplace_back(new KeysPressedComponent());
            keysRelease.emplace_back(new KeysReleasedComponent());
        }
        
        nSines = 2;
        
        
        addAndMakeVisible(background);
        
        // configuring frequency slider and adding it to the main window
        addAndMakeVisible(frequencySlider[0]);
        frequencySlider[0].setRange (50.0, 5000.0);
        frequencySlider[0].setSkewFactorFromMidPoint (500.0);
        frequencySlider[0].setValue(1000); // will also set the default frequency of the sine osc
        frequencySlider[0].addListener (this);
        
        // configuring frequency label box and adding it to the main window
        addAndMakeVisible(frequencyLabel[0]);
        frequencyLabel[0].setText ("Carrier Frequency", dontSendNotification);
        frequencyLabel[0].attachToComponent (&frequencySlider[0], true);
        
        
        // configuring gain slider and adding it to the main window
        addAndMakeVisible(gainSlider[0]);
        gainSlider[0].setRange (0.0, 1.0);
        gainSlider[0].setValue(0.5); // will alsi set the default gain of the sine osc
        gainSlider[0].addListener (this);
        
        
        // configuring gain label and adding it to the main window
        addAndMakeVisible(gainLabel[0]);
        gainLabel[0].setText ("Gain", dontSendNotification);
        gainLabel[0].attachToComponent (&gainSlider[0], true);
        
        
        // configuring frequency slider and adding it to the main window
        addAndMakeVisible(frequencySlider[1]);
        frequencySlider[1].setRange (50.0, 5000.0);
        frequencySlider[1].setSkewFactorFromMidPoint (500.0);
        frequencySlider[1].setValue(1000); // will also set the default frequency of the sine osc
        frequencySlider[1].addListener (this);
        
        // configuring frequency label box and adding it to the main window
        addAndMakeVisible(frequencyLabel[1]);
        frequencyLabel[1].setText ("Modulator Frequency", dontSendNotification);
        frequencyLabel[1].attachToComponent (&frequencySlider[1], true);
        
        
        // configuring gain slider and adding it to the main window
        addAndMakeVisible(gainSlider[1]);
        gainSlider[1].setRange (0.0, 500);
        gainSlider[1].setValue(250); // will alsi set the default gain of the sine osc
        gainSlider[1].addListener (this);
        
        
        // configuring gain label and adding it to the main window
        addAndMakeVisible(gainLabel[1]);
        gainLabel[1].setText ("Index", dontSendNotification);
        gainLabel[1].attachToComponent (&gainSlider[1], true);
        
        // configuring on/off button and adding it to the main window
        addAndMakeVisible(onOffButton);
        onOffButton.addListener(this);
        
        // configuring on/off label and adding it to the main window
        onOffLabel.setColour(juce::Label::textColourId, Colours::white);
        onOffLabel.setText ("[SPACE KEY]On/Off", dontSendNotification);
        addAndMakeVisible(onOffLabel);
        onOffLabel.attachToComponent (&onOffButton, true);
        
        // carrier & modulator components
        addAndMakeVisible (carrier);
        addAndMakeVisible (modulator);
        
        // labels
        for (int i =0; i < 8; i++) {
            keyLabel[i].setColour(juce::Label::textColourId, Colours::white);
        }
        keyLabel[0].setText ("W", dontSendNotification);
        keyLabel[1].setText ("S", dontSendNotification);
        keyLabel[2].setText ("A", dontSendNotification);
        keyLabel[3].setText ("D", dontSendNotification);
        keyLabel[4].setText ("^", dontSendNotification);
        keyLabel[5].setText ("v", dontSendNotification);
        keyLabel[6].setText ("<", dontSendNotification);
        keyLabel[7].setText (">", dontSendNotification);
        for (int i =0; i < 8; i++) {
            addAndMakeVisible(keyLabel[i]);
        }
        
        /*
        addAndMakeVisible(carrierLabel[0]);
        carrierLabel[0].setText ("Carrier", dontSendNotification);
        addAndMakeVisible(carrierLabel[1]);
        carrierLabel[1].setText ("Gain", dontSendNotification);
        addAndMakeVisible(modulatorLabel[0]);
        modulatorLabel[0].setText ("Modulator", dontSendNotification);
        addAndMakeVisible(modulatorLabel[1]);
        modulatorLabel[1].setText ("Index", dontSendNotification);
        */
        
        setSize (800, 400);
        
        nChans = 2;
        setAudioChannels (0, nChans); // no inputs, one output
        audioBuffer = new float*[nChans];
        
        for (int i = 0; i < MAX_SINE_WAVE; i++) {
            frequencySlider[i].setVisible(false);
            gainSlider[i].setVisible(false);
        }
        
        for (int i = 0; i < 9; i++){
            addAndMakeVisible(*keysPress[i]);
            addAndMakeVisible(*keysRelease[i]);
        }
        
//        addAndMakeVisible(keySpaceP);
//        addAndMakeVisible(keySpaceR);
        
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        // placing the UI elements in the main window
        // getWidth has to be used in case the window is resized by the user
        const int sliderLeft = 80;
        carrierLabel[0].setBounds(250, 0, 100, 200);
        modulatorLabel[0].setBounds(500, 0, 100, 200);
        for (int i = 0; i < MAX_SINE_WAVE; i++){
            frequencySlider[i].setBounds (sliderLeft, 10 + 60 * i, getWidth() - sliderLeft - 160, 20);
            gainSlider[i].setBounds (sliderLeft, 40 + 60 * i, getWidth() - sliderLeft - 160, 20);
        }
        onOffButton.setBounds (400, 0, 40, 20);
        
        carrier.setBounds (carrier.getX(), carrier.getY(), 30, 30);
        modulator.setBounds (modulator.getX() + 100, modulator.getY(), 30, 30);
        background.setBounds (0,0,800,400);
        
        keysRelease[0]->setBounds(wKey[0], wKey[1], wKey[2], wKey[3]);    //W
        keysRelease[4]->setBounds(wKey[0] + 400, wKey[1], wKey[2], wKey[3]);    //Up
        keysRelease[1]->setBounds(wKey[0], wKey[1] - 55, wKey[2], wKey[3]);    //S
        keysRelease[5]->setBounds(wKey[0] + 400, wKey[1] - 55, wKey[2], wKey[3]);    //Down
        keysRelease[2]->setBounds(wKey[0] - 55, wKey[1] - 55, wKey[2], wKey[3]);    //A
        keysRelease[6]->setBounds(wKey[0] + 400 - 55, wKey[1] - 55, wKey[2], wKey[3]);    //Left
        keysRelease[3]->setBounds(wKey[0] + 55, wKey[1] - 55, wKey[2], wKey[3]);    //D
        keysRelease[7]->setBounds(wKey[0] + 400 + 55, wKey[1] - 55, wKey[2], wKey[3]);    //Right
        
        keysPress[0]->setBounds(wKey[0], wKey[1], wKey[2], wKey[3]);    //W
        keysPress[4]->setBounds(wKey[0] + 400, wKey[1], wKey[2], wKey[3]);    //Up
        keysPress[1]->setBounds(wKey[0], wKey[1] - 55, wKey[2], wKey[3]);    //S
        keysPress[5]->setBounds(wKey[0] + 400, wKey[1] - 55, wKey[2], wKey[3]);    //Down
        keysPress[2]->setBounds(wKey[0] - 55, wKey[1] - 55, wKey[2], wKey[3]);    //A
        keysPress[6]->setBounds(wKey[0] + 400 - 55, wKey[1] - 55, wKey[2], wKey[3]);    //Left
        keysPress[3]->setBounds(wKey[0] + 55, wKey[1] - 55, wKey[2], wKey[3]);    //D
        keysPress[7]->setBounds(wKey[0] + 400 + 55, wKey[1] - 55, wKey[2], wKey[3]);    //Right
        
        keyLabel[0].setBounds(wKey[0] + 12, wKey[1] + 3, wKey[2], wKey[3]);    //W
        keyLabel[4].setBounds(wKey[0] + 12 + 400, wKey[1] + 3, wKey[2], wKey[3]);    //Up
        keyLabel[1].setBounds(wKey[0] + 12, wKey[1] + 3 + 55, wKey[2], wKey[3]);    //S
        keyLabel[5].setBounds(wKey[0] + 12 + 400, wKey[1] + 3 + 55, wKey[2], wKey[3]);    //Down
        keyLabel[2].setBounds(wKey[0] + 12 - 55, wKey[1] + 3 + 55, wKey[2], wKey[3]);    //A
        keyLabel[6].setBounds(wKey[0] + 12 + 400 - 55, wKey[1] + 3 + 55, wKey[2], wKey[3]);    //Left
        keyLabel[3].setBounds(wKey[0] + 12 + 55, wKey[1] + 3 + 55, wKey[2], wKey[3]);    //D
        keyLabel[7].setBounds(wKey[0] + 12 + 400 + 55, wKey[1] + 3 + 55, wKey[2], wKey[3]);    //Right
        
        keysRelease[8]->setBounds(400, 400, 50, 50);
        keysPress[8]->setBounds(400, 400, 50, 50);
        
        for(int i = 0; i < 9 ; i++) {
            keysPress[i]->setVisible(false);
        }
        
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if (samplingRate > 0.0){
            for (int i = 0; i < MAX_SINE_WAVE; i++){
                if (slider == &frequencySlider[i]){
                    sine[i].setFrequency(frequencySlider[i].getValue());
                    
                }
                else if (slider == &gainSlider[i]){
                    gain[i] = gainSlider[i].getValue();
                    
                }
            }
        }
        carrierLeft = frequencySlider[0].getValue()/14;
        carrierTop = 150 - gainSlider[0].getValue() * 125;
        modulatorLeft = frequencySlider[1].getValue()/14 + 400;
        modulatorTop = 150 - gainSlider[1].getValue()/4;
        
        carrier.setTopLeftPosition(carrierLeft, carrierTop);
        modulator.setTopLeftPosition(modulatorLeft, modulatorTop);
        
        keysRelease[0]->setTopLeftPosition(wKey[0], wKey[1]);    //W
        keysRelease[4]->setTopLeftPosition(wKey[0] + 400, wKey[1]);    //Up
        keysRelease[1]->setTopLeftPosition(wKey[0], wKey[1] + 55);    //S
        keysRelease[5]->setTopLeftPosition(wKey[0] + 400, wKey[1] + 55);    //Down
        keysRelease[2]->setTopLeftPosition(wKey[0] - 55, wKey[1] + 55);    //A
        keysRelease[6]->setTopLeftPosition(wKey[0] + 400 - 55, wKey[1] + 55);    //Left
        keysRelease[3]->setTopLeftPosition(wKey[0] + 55, wKey[1] + 55);    //D
        keysRelease[7]->setTopLeftPosition(wKey[0] + 400 + 55, wKey[1] + 55);    //Right
        keysPress[0]->setTopLeftPosition(wKey[0], wKey[1]);    //W
        keysPress[4]->setTopLeftPosition(wKey[0] + 400, wKey[1]);    //Up
        keysPress[1]->setTopLeftPosition(wKey[0], wKey[1] + 55);    //S
        keysPress[5]->setTopLeftPosition(wKey[0] + 400, wKey[1] + 55);    //Down
        keysPress[2]->setTopLeftPosition(wKey[0] - 55, wKey[1] + 55);    //A
        keysPress[6]->setTopLeftPosition(wKey[0] + 400 - 55, wKey[1] + 55);    //Left
        keysPress[3]->setTopLeftPosition(wKey[0] + 55, wKey[1] + 55);    //D
        keysPress[7]->setTopLeftPosition(wKey[0] + 400 + 55, wKey[1] + 55);    //Right
    }
    
    void buttonClicked (Button* button) override
    {
        // turns audio on or off
        if (button == &onOffButton){
            if(onOffButton.getToggleState()){
                onOff = 1;
            }
            else{
                onOff = 0;
            }
        }
    }
    
    static void refreshKeys(const KeyPress & key, Slider & slider, const float value, const std::shared_ptr<KeysReleasedComponent> & releaseKey, const std::shared_ptr<KeysPressedComponent> & pressKey) {
        while(key.isCurrentlyDown()) {
            const MessageManagerLock lock;
            slider.setValue(slider.getValue() + value);
//            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            
        }
        const MessageManagerLock lock;
        releaseKey->setVisible(true);
        pressKey->setVisible(false);
    }
    
    bool keyPressed (const KeyPress &key) override
    {
        //for (int i = 0; i < NumChord; i++) {
        if(key == keys[8]){
            if(onOff == 1){
                onOff = 0;
                onOffButton.setToggleState(false, dontSendNotification);
            }
            else{
                onOff = 1;
                onOffButton.setToggleState(true, dontSendNotification);
            }
            
        }
        if(keys[2].isCurrentlyDown()){
            keysRelease[2]->setVisible(false);
            keysPress[2]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[2]), std::ref(frequencySlider[0]), - 0.4, std::ref(keysRelease[2]), std::ref(keysPress[2]));
            t.detach();
        }
        if(keys[3].isCurrentlyDown()){
            keysRelease[3]->setVisible(false);
            keysPress[3]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[3]), std::ref(frequencySlider[0]), + 0.4, std::ref(keysRelease[3]), std::ref(keysPress[3]));
            t.detach();
        }
        if(keys[6].isCurrentlyDown()){
            keysRelease[6]->setVisible(false);
            keysPress[6]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[6]), std::ref(frequencySlider[1]), - 0.4, std::ref(keysRelease[6]), std::ref(keysPress[6]));
            t.detach();
        }
        if(keys[7].isCurrentlyDown()){
            keysRelease[7]->setVisible(false);
            keysPress[7]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[7]), std::ref(frequencySlider[1]), + 0.4, std::ref(keysRelease[7]), std::ref(keysPress[7]));
            t.detach();
        }
        if(keys[0].isCurrentlyDown()){
            keysRelease[0]->setVisible(false);
            keysPress[0]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[0]), std::ref(gainSlider[0]), + 0.0002, std::ref(keysRelease[0]), std::ref(keysPress[0]));
            t.detach();
        }
        if(keys[1].isCurrentlyDown()){
            keysRelease[1]->setVisible(false);
            keysPress[1]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[1]), std::ref(gainSlider[0]), - 0.0002, std::ref(keysRelease[1]), std::ref(keysPress[1]));
            t.detach();
        }
        if(keys[4].isCurrentlyDown()){
            keysRelease[4]->setVisible(false);
            keysPress[4]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[4]), std::ref(gainSlider[1]), + 0.1, std::ref(keysRelease[4]), std::ref(keysPress[4]));
            t.detach();
        }
        if(keys[5].isCurrentlyDown()){
            keysRelease[5]->setVisible(false);
            keysPress[5]->setVisible(true);
            auto t = std::thread(refreshKeys, std::ref(keys[5]), std::ref(gainSlider[1]), - 0.1, std::ref(keysRelease[5]), std::ref(keysPress[5]));
            t.detach();
        }
        
        return true;
    }

    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        sine[0].setSamplingRate(sampleRate);
        sine[0].setFrequency(frequencySlider[0].getValue());
        sine[1].setSamplingRate(sampleRate);
        sine[1].setFrequency(frequencySlider[1].getValue());
        for(int i=0; i<4; i++){
            smooth[i].setSmooth(0.999);
        }
        reverb.init(sampleRate);
        reverb.buildUserInterface(&reverbControl);
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        /*
        const float level = gainSlider[0].getValue(); // gain is updated every block
        // getting the audio output buffer to be filled
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        // computing one block
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            sine[0].setFrequency(smooth[0].tick(frequencySlider[0].getValue()) + sine[1].tick()*smooth[3].tick(gainSlider[1].getValue())); // modulating freq of the carrier
            buffer[sample] = sine[0].tick() * smooth[1].tick(level) * smooth[2].tick(onOff); // computing sample
        }
        */
        
        const float level = gainSlider[0].getValue(); // gain is updated every block
        // getting the audio output buffer to be filled
        //float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        for(int i=0; i<nChans; i++){
            audioBuffer[i] = bufferToFill.buffer->getWritePointer (i, bufferToFill.startSample);
        }
        
        // computing one block
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            sine[0].setFrequency(smooth[0].tick(frequencySlider[0].getValue()) + sine[1].tick()*smooth[3].tick(gainSlider[1].getValue())); // modulating freq of the carrier
            audioBuffer[0][sample] = sine[0].tick() * smooth[1].tick(level) * smooth[2].tick(onOff); // computing sample
        }
        reverb.compute(bufferToFill.numSamples,audioBuffer,audioBuffer);
    }
    
    
private:
    // UI Elements
    Slider frequencySlider[MAX_SINE_WAVE]; //Carrier, Modulator
    Slider gainSlider[MAX_SINE_WAVE];      //Gain Index
    ToggleButton onOffButton;
    CarrierComponent carrier;
    ModulatorComponent modulator;
    BackgroundComponent background;
    reverb reverb;
    MapUI reverbControl;
//    KeysPressedComponent keySpaceP;
//    KeysReleasedComponent keySpaceR;
    float** audioBuffer;

    Label frequencyLabel[MAX_SINE_WAVE], gainLabel[MAX_SINE_WAVE], onOffLabel, carrierLabel[2], modulatorLabel[2], keyLabel[9];
    
    Smooth smooth[4];

    Sine sine[MAX_SINE_WAVE]; // the sine wave oscillator
    
    // Global Variables
    float gain[MAX_SINE_WAVE] = {0.0};
    int onOff, samplingRate, nChans, nSines, carrierLeft, carrierTop, modulatorLeft, modulatorTop;
    int wKey[4] = {200, 200, 50, 50}; //Bounds
    std::vector<KeyPress> keys;
    std::vector<std::shared_ptr<KeysPressedComponent>> keysPress;
    std::vector<std::shared_ptr<KeysReleasedComponent>> keysRelease;
//    Image keyboard(keys.png);
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
