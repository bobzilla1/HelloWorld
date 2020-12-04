/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	addAndMakeVisible(comp);
	comp.addMouseListener(this, false);

	addAndMakeVisible(ownedArrayComp);

	//setSize is usually the last thing we want to call
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
	comp.removeMouseListener(this);
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

	comp.setBounds(30, 30, 100, 100);

	// Here is where we get it positioned
	// However big our MainComponent is, we will go from the right edge to 
	// where our set bounds exists, and we'll make this first start at the bottom.
	// And we want the width from our component's left edge to the rest of it.
	ownedArrayComp.setBounds(comp.getX(),
							comp.getBottom() + 5,
							getWidth() - comp.getX(),
							getHeight() - comp.getBottom());

}
